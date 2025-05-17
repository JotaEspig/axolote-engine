/**
 * @file audio_engine.hpp
 * @brief Audio engine header file
 **/
#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <AL/al.h>
#include <AL/alc.h>

#include "utils.hpp"

namespace axolote {

/**
 * @brief Audio engine class (works like a singleton)
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * It's a singleton class that manages the audio engine. It's basically a
 * wrapper to OpenAL
 **/
class AXOLOTE_EXPORT AudioEngine {
public:
    /**
     * @brief Creates a AudioEngine object
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return shared pointer to AudioEngine object
     **/
    template <typename... Args>
    static std::shared_ptr<AudioEngine> create(Args &&...args);

    bool load_mp3(const std::string &name, const std::string &path);
    bool play_sound(const std::string &name);
    bool is_playing(const std::string &name);

private:
    struct Deleter {
        void operator()(AudioEngine *audio_engine);
    };

    static AXOLOTE_EXPORT std::shared_ptr<AudioEngine> _instance;
    ALCdevice *_device = nullptr;
    ALCcontext *_context = nullptr;
    std::unordered_map<std::string, ALuint> _buffers;
    std::unordered_map<std::string, ALuint> _sources;

    AudioEngine();

    void destroy();
};

template <typename... Args>
std::shared_ptr<AudioEngine> AudioEngine::create(Args &&...args) {
    if (AudioEngine::_instance) {
        return AudioEngine::_instance;
    }

    AudioEngine::_instance = std::shared_ptr<AudioEngine>(
        new AudioEngine(std::forward<Args>(args)...), Deleter()
    );
    return AudioEngine::_instance;
}

} // namespace axolote
