//
// Created by Anthony Lesch on 11/6/25.
//

#include "AudioSystem.h"

#include <ranges>

#include "Utils.h"
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#include "SDL3/SDL_log.h"

static AudioSystem* s_instance;

struct AudioEngine
{
    FMOD::System* System = nullptr;
    FMOD::ChannelGroup* SFXChannelGroup = nullptr;
    FMOD::ChannelGroup* MusicChannelGroup = nullptr;
};

struct AudioFile
{
    FMOD::Sound* Sound = nullptr;
    FMOD::Channel* Channel = nullptr;
    bool IsMusic = false;
};

AudioSystem::AudioSystem(AudioEngine* engine)
    : m_Engine(engine)
{
}

AudioSystem::~AudioSystem()
{
    m_Engine->SFXChannelGroup->release();
    m_Engine->MusicChannelGroup->release();
    m_Engine->System->release();

    delete m_Engine;

    m_Files.clear();
}

AudioSystem& AudioSystem::GetInstance()
{
    return *s_instance;
}

bool AudioSystem::Initialize()
{
    auto* engine = new AudioEngine();

    FMOD_RESULT result = FMOD::System_Create(&engine->System);
    if (result != FMOD_OK) {
        SDL_Log("FMOD Error! (%d) %s\n", result, FMOD_ErrorString(result));
        return false;
    }

    result = engine->System->init(512, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK) {
        SDL_Log("FMOD Error! (%d) %s\n", result, FMOD_ErrorString(result));
        return false;
    }

    result = engine->System->createChannelGroup("SFX_Channels", &engine->SFXChannelGroup);
    if (result != FMOD_OK) {
        SDL_Log("FMOD Error! (%d) %s\n", result, FMOD_ErrorString(result));
        return false;
    }

    result = engine->System->createChannelGroup("Music_Channels", &engine->MusicChannelGroup);
    if (result != FMOD_OK) {
        SDL_Log("FMOD Error! (%d) %s\n", result, FMOD_ErrorString(result));
        return false;
    }

    s_instance = new AudioSystem(engine);
    engine->SFXChannelGroup->setVolume(s_instance->m_SFXVolume);
    engine->MusicChannelGroup->setVolume(s_instance->m_MusicVolume);

    return true;
}

void AudioSystem::Shutdown()
{
    delete s_instance;
}

void AudioSystem::Tick()
{
    s_instance->m_Engine->System->update();
}

void AudioSystem::PlayMusic(const std::string& path)
{
    if (m_Files.contains(path)) {
        const AudioFile* soundFile = m_Files[path];
        bool isPlaying;

        if (const FMOD_RESULT result = soundFile->Channel->isPlaying(&isPlaying); result != FMOD_OK) {
            SDL_Log("Error getting play status for music: (%d) %s\n", result, FMOD_ErrorString(result));
            return;
        }

        if (!isPlaying) {
            m_Engine->MusicChannelGroup->setPaused(true);
        }
    }

    auto* soundFile = new AudioFile();
    soundFile->IsMusic = true;

    FMOD_RESULT result = m_Engine->System->createStream(path.c_str(), FMOD_2D | FMOD_LOOP_NORMAL, nullptr, &soundFile->Sound);

    if (result != FMOD_OK) {
        SDL_Log("Unable to create Stream (%d) %s\n", result, FMOD_ErrorString(result));
        delete soundFile;

        return;
    }

    result = m_Engine->System->playSound(soundFile->Sound, m_Engine->MusicChannelGroup, false, &soundFile->Channel);
    if (result != FMOD_OK) {
        SDL_Log("Unable to play sound! (%d) %s", result, FMOD_ErrorString(result));
        delete soundFile->Sound;
        delete soundFile;

        return;
    }

    m_Files[path] = soundFile;
}

void AudioSystem::PauseMusic() const
{
    m_Engine->MusicChannelGroup->setPaused(true);
}

void AudioSystem::ResumeMusic() const
{
    m_Engine->MusicChannelGroup->setPaused(false);
}

void AudioSystem::StopMusic() const
{
    m_Engine->MusicChannelGroup->stop();
}

void AudioSystem::PlaySFX(const std::string& path)
{
    if (m_Files.contains(path)) {
        const AudioFile* existingSound = m_Files[path];
        if (existingSound->IsMusic) {
            SDL_Log("Invalid SFX requested. Sound is music.");
            return;
        }

        m_Engine->System->playSound(existingSound->Sound, m_Engine->SFXChannelGroup, false, nullptr);

        return;
    }

    auto* soundFile = new AudioFile();
    const FMOD_RESULT result = m_Engine->System->createSound(path.c_str(), FMOD_2D, nullptr, &soundFile->Sound);

    if (result != FMOD_OK) {
        SDL_Log("Unable to play sfx (%d) %s", result, FMOD_ErrorString(result));
        delete soundFile;
        return;
    }

    m_Files[path] = soundFile;
    m_Engine->System->playSound(soundFile->Sound, m_Engine->SFXChannelGroup, false, nullptr);
}

float AudioSystem::GetMusicVolume() const
{
    return m_MusicVolume;
}

float AudioSystem::GetSFXVolume() const
{
    return m_SFXVolume;
}

void AudioSystem::SetMusicVolume(const float volume)
{
    m_MusicVolume = Utils::Clamp(volume, 0.f, 1.f);
    SDL_Log("Setting music volume to %f", m_MusicVolume);

    m_Engine->MusicChannelGroup->setVolume(m_MusicVolume);
}

void AudioSystem::SetSFXVolume(const float volume)
{
    m_SFXVolume = Utils::Clamp(volume, 0.f, 1.f);
    SDL_Log("Setting SFX volume to %f", m_SFXVolume);

    m_Engine->SFXChannelGroup->setVolume(m_SFXVolume);
}
