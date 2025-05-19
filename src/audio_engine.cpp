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
        debug("Sound already loaded: %s", name.c_str());
        return false;
    }

    mp3dec_ex_t mp3;
    if (mp3dec_ex_open(&mp3, path.c_str(), MP3D_SEEK_TO_SAMPLE)) {
        debug("Failed to load MP3 file: %s", path.c_str());
        return false;
    }

    size_t totalSamples = mp3.samples; // total PCM samples (not bytes)
    std::vector<mp3d_sample_t> pcmData(totalSamples);

    mp3dec_ex_read(&mp3, pcmData.data(), totalSamples);
    if (mp3.info.hz == 0 || mp3.info.channels == 0) {
        debug(
            "MP3 has invalid metadata: %d Hz, %d channels", mp3.info.hz,
            mp3.info.channels
        );
        mp3dec_ex_close(&mp3);
        return false;
    }

    if (mp3.info.channels != 1 && mp3.info.channels != 2) {
        debug("Invalid channel count: %d", mp3.info.channels);
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
        debug("alBufferData error: %x", error);
        mp3dec_ex_close(&mp3);
        return false;
    }
    debug("Loaded sound: %s", name.c_str());
    mp3dec_ex_close(&mp3);
    return true;
}

bool AudioEngine::play_sound(const std::string &name) {
    auto it = _sources.find(name);
    if (it != _sources.end()) {
        alSourcePlay(it->second);
        debug("Playing sound: %s", name.c_str());
        return true;
    }
    else {
        debug("Sound not found: %s", name.c_str());
        return false;
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
        debug("Enqueued sound: %s", name.c_str());
    }
    else {
        debug("Sound not found: %s", name.c_str());
    }
}

void AudioEngine::play_queue() {
    while (!_queue.empty()) {
        auto p = _queue.front();
        alSourcePlay(p.second);
        debug("Playing queued sound: %s", p.first.c_str());
        _queue.pop();
    }
}

void AudioEngine::Deleter::operator()(AudioEngine *audio_engine) {
    if (audio_engine) {
        audio_engine->destroy();
        debug("AudioEngine deleted");
    }
}

AudioEngine::AudioEngine() {
    _device = alcOpenDevice(nullptr);
    if (!_device) {
        debug("Failed to open audio device");
        return;
    }

    _context = alcCreateContext(_device, nullptr);
    if (!_context) {
        debug("Failed to create audio context");
        alcCloseDevice(_device);
        return;
    }

    if (!alcMakeContextCurrent(_context)) {
        debug("Failed to make context current");
    }
    debug("AudioEngine created");
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
