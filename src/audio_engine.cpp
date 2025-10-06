#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#define MINIMP3_IMPLEMENTATION
#include "minimp3_ex.h"
#include <al.h>

#include "axolote/audio_engine.hpp"
#include "axolote/utils.hpp"

namespace axolote {

std::shared_ptr<AudioEngine> AudioEngine::_instance = nullptr;

bool AudioEngine::load_mp3(const std::string &name, const std::string &path) {
    bool already_exists = (_buffers.find(name) != _buffers.end())
                          && (_sources.find(name) != _sources.end());
    if (already_exists) {
        debug(DebugType::WARNING, "Sound already loaded: %s", name.c_str());
        return false;
    }

    mp3dec_ex_t mp3;
    if (mp3dec_ex_open(&mp3, path.c_str(), MP3D_SEEK_TO_SAMPLE)) {
        debug(DebugType::ERROR, "Failed to load MP3 file: %s", path.c_str());
        return false;
    }

    size_t totalSamples = mp3.samples; // total PCM samples (not bytes)
    std::vector<mp3d_sample_t> pcmData(totalSamples);

    mp3dec_ex_read(&mp3, pcmData.data(), totalSamples);
    if (mp3.info.hz == 0 || mp3.info.channels == 0) {
        debug(
            DebugType::ERROR, "MP3 has invalid metadata: %d Hz, %d channels",
            mp3.info.hz, mp3.info.channels
        );
        mp3dec_ex_close(&mp3);
        return false;
    }

    if (mp3.info.channels != 1 && mp3.info.channels != 2) {
        debug(DebugType::ERROR, "Invalid channel count: %d", mp3.info.channels);
        mp3dec_ex_close(&mp3);
        return false;
    }

    ALenum format
        = (mp3.info.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;

    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(
        buffer, format, pcmData.data(), totalSamples * sizeof(mp3d_sample_t),
        mp3.info.hz
    );
    _buffers[name] = buffer;

    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    _sources[name] = source;

    ALenum error = alGetError();
    if (error != AL_NO_ERROR) {
        debug(DebugType::ERROR, "alBufferData error: %x", error);
        mp3dec_ex_close(&mp3);
        return false;
    }
    debug(DebugType::INFO, "Loaded sound: %s", name.c_str());
    mp3dec_ex_close(&mp3);
    return true;
}

bool AudioEngine::play_sound(const std::string &name) {
    auto it = _sources.find(name);
    if (it != _sources.end()) {
        alSourcePlay(it->second);
        debug(DebugType::INFO, "Playing sound: %s", name.c_str());
        return true;
    }
    else {
        debug(DebugType::ERROR, "Sound not found: %s", name.c_str());
        return false;
    }
}

void AudioEngine::stop_sound(const std::string &name) {
    auto it = _sources.find(name);
    if (it != _sources.end()) {
        alSourceStop(it->second);
        debug(DebugType::INFO, "Stopped sound: %s", name.c_str());
    }
    else {
        debug(DebugType::ERROR, "Sound not found: %s", name.c_str());
    }
}

bool AudioEngine::is_playing(const std::string &name) {
    auto it = _sources.find(name);
    if (it == _sources.end())
        return false;

    ALint state;
    alGetSourcei(it->second, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

void AudioEngine::enqueue(const std::string &name) {
    auto it = _sources.find(name);
    if (it != _sources.end()) {
        ALuint source = it->second;
        _queue.push(std::make_pair(name, source));
        debug(DebugType::INFO, "Enqueued sound: %s", name.c_str());
    }
    else {
        debug(DebugType::WARNING, "Sound not found: %s", name.c_str());
    }
}

void AudioEngine::play_queue() {
    while (!_queue.empty()) {
        auto p = _queue.front();
        alSourcePlay(p.second);
        debug(DebugType::INFO, "Playing queued sound: %s", p.first.c_str());
        _queue.pop();
    }
}

void AudioEngine::set_global_volume(float volume) {
    if (volume < 0.0f || volume > 1.0f) {
        debug(DebugType::WARNING, "Volume must be between 0.0 and 1.0");
        return;
    }
    if (volume == _global_volume) {
        return;
    }

    _global_volume = volume;
    alListenerf(AL_GAIN, _global_volume);
    debug(DebugType::INFO, "Global volume set to: %.2f", _global_volume);
}

float AudioEngine::get_global_volume() {
    return _global_volume;
}

void AudioEngine::set_local_volume(const std::string &name, float volume) {
    if (volume < 0.0f || volume > 1.0f) {
        debug(DebugType::WARNING, "Volume must be between 0.0 and 1.0");
        return;
    }
    if (volume == get_local_volume(name)) {
        return;
    }

    auto it = _sources.find(name);
    if (it != _sources.end()) {
        ALuint source = it->second;
        alSourcef(source, AL_GAIN, volume);
        _local_volumes[name] = volume;
        debug(
            DebugType::INFO, "Local volume for %s set to: %.2f", name.c_str(),
            volume
        );
    }
    else {
        debug(DebugType::WARNING, "Sound not found: %s", name.c_str());
    }
}

float AudioEngine::get_local_volume(const std::string &name) {
    auto it = _local_volumes.find(name);
    if (it != _local_volumes.end()) {
        return it->second;
    }
    else {
        debug(DebugType::WARNING, "Sound not found: %s", name.c_str());
    }
    return 1.0f; // Default volume
}

void AudioEngine::Deleter::operator()(AudioEngine *audio_engine) {
    if (audio_engine) {
        audio_engine->destroy();
        debug(DebugType::INFO, "AudioEngine deleted");
    }
}

AudioEngine::AudioEngine() {
    _device = alcOpenDevice(nullptr);
    if (!_device) {
        debug(DebugType::FATAL, "Failed to open audio device");
        throw std::runtime_error("Failed to open audio device");
    }

    _context = alcCreateContext(_device, nullptr);
    if (!_context) {
        debug(DebugType::FATAL, "Failed to create audio context");
        alcCloseDevice(_device);
        throw std::runtime_error("Failed to create audio context");
    }

    if (!alcMakeContextCurrent(_context)) {
        debug(DebugType::FATAL, "Failed to make context current");
        alcDestroyContext(_context);
        alcCloseDevice(_device);
        throw std::runtime_error("Failed to make context current");
    }
    debug(DebugType::INFO, "AudioEngine created");
}

void AudioEngine::destroy() {
    for (auto &[name, source] : _sources)
        alDeleteSources(1, &source);
    for (auto &[name, buffer] : _buffers)
        alDeleteBuffers(1, &buffer);

    if (_context) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(_context);
    }
    if (_device) {
        alcCloseDevice(_device);
    }
}

} // namespace axolote
