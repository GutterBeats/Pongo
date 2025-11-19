//
// Created by Anthony Lesch on 11/6/25.
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <SDL3_mixer/SDL_mixer.h>

struct AudioEngine;

using AudioPtr = std::shared_ptr<MIX_Audio>;

class AudioSystem
{
    explicit AudioSystem(AudioEngine* engine);
    ~AudioSystem();

public:
    static AudioSystem& GetInstance();

    static bool Initialize();
    static void Shutdown();

    void PlayMusic(const std::string& path);
    void PauseMusic() const;
    void ResumeMusic() const;
    void StopMusic() const;
    void PlaySFX(const std::string& path);

    [[nodiscard]] float GetMusicVolume() const;
    [[nodiscard]] float GetSFXVolume() const;

    void SetMusicVolume(float volume) const;
    void SetSFXVolume(float volume) const;

private:

    AudioEngine* m_Engine;
    std::unordered_map<std::string, AudioPtr> m_Files;

    AudioPtr GetOrAdd(const std::string& path);
};
