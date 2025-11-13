//
// Created by Anthony Lesch on 11/6/25.
//

#pragma once

#include <string>
#include <unordered_map>

struct AudioEngine;
struct AudioFile;

class AudioSystem
{
    explicit AudioSystem(AudioEngine* engine);
    ~AudioSystem();

public:
    static AudioSystem& GetInstance();

    static bool Initialize();
    static void Shutdown();
    static void Tick();

    void PlayMusic(const std::string& path);
    void PauseMusic() const;
    void ResumeMusic() const;
    void StopMusic() const;
    void PlaySFX(const std::string& path);

    [[nodiscard]] float GetMusicVolume() const;
    [[nodiscard]] float GetSFXVolume() const;

    void SetMusicVolume(float volume);
    void SetSFXVolume(float volume);

private:

    AudioEngine* m_Engine;

    float m_MusicVolume = 1.f;
    float m_SFXVolume = 1.f;

    std::unordered_map<std::string, AudioFile*> m_Files;
};
