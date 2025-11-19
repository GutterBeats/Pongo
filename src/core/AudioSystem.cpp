//
// Created by Anthony Lesch on 11/6/25.
//

#include "AudioSystem.h"

#include <ranges>
#include <SDL3/SDL_log.h>

#include "Utils.h"

static AudioSystem* s_instance;

struct AudioEngine
{
    MIX_Mixer* Mixer;
    MIX_Track* MusicTrack;
    MIX_Track* SfxTrack;
    SDL_PropertiesID MusicPropsID;
    SDL_PropertiesID SfxPropsID;
};

AudioSystem::AudioSystem(AudioEngine* engine)
    : m_Engine(engine)
{
}

AudioSystem::~AudioSystem()
{
    MIX_DestroyTrack(m_Engine->MusicTrack);
    MIX_DestroyTrack(m_Engine->SfxTrack);
    MIX_DestroyMixer(m_Engine->Mixer);

    MIX_Quit();

    delete m_Engine;

    m_Files.clear();
}

AudioSystem& AudioSystem::GetInstance()
{
    return *s_instance;
}

bool AudioSystem::Initialize()
{
    if (!MIX_Init()) {
        SDL_Log("Unable to initialize SDL_MIXER library! %s", SDL_GetError());
        return false;
    }

    MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (!mixer) {
        SDL_Log("Unable to create sound mixer!: %s", SDL_GetError());
        return false;
    }

    MIX_Track* musicTrack = MIX_CreateTrack(mixer);
    const SDL_PropertiesID musicID = MIX_GetTrackProperties(musicTrack);

    if (!musicTrack || !musicID) {
        SDL_Log("Unable to create music track!: %s", SDL_GetError());
        MIX_DestroyMixer(mixer);

        return false;
    }

    if (!SDL_SetNumberProperty(musicID, MIX_PROP_PLAY_LOOPS_NUMBER, -1)) {
        SDL_Log("Unable to set loop for music!: %s", SDL_GetError());
    }

    MIX_Track* sfxTrack = MIX_CreateTrack(mixer);
    const SDL_PropertiesID sfxID = MIX_GetTrackProperties(sfxTrack);

    if (!sfxTrack || !sfxID) {
        SDL_Log("Unable to create sfx track!: %s", SDL_GetError());
        MIX_DestroyMixer(mixer);

        return false;
    }

    if (!SDL_SetNumberProperty(sfxID, MIX_PROP_PLAY_LOOPS_NUMBER, 0)) {
        SDL_Log("Unable to set loop for music!: %s", SDL_GetError());
    }

    auto* engine = new AudioEngine();
    engine->Mixer = mixer;
    engine->MusicTrack = musicTrack;
    engine->SfxTrack = sfxTrack;
    engine->MusicPropsID = musicID;
    engine->SfxPropsID = sfxID;

    s_instance = new AudioSystem(engine);

    return true;
}

void AudioSystem::Shutdown()
{
    delete s_instance;
}

void AudioSystem::PlayMusic(const std::string& path)
{
    const AudioPtr music = GetOrAdd(path);
    if (music == nullptr) return;

    StopMusic();

    if (!MIX_SetTrackAudio(m_Engine->MusicTrack, music.get())) {
        SDL_Log("Unable to set track audio!: %s", SDL_GetError());
        return;
    }

    MIX_PlayTrack(m_Engine->MusicTrack, m_Engine->MusicPropsID);
}

void AudioSystem::PauseMusic() const
{
    MIX_PauseTrack(m_Engine->MusicTrack);
}

void AudioSystem::ResumeMusic() const
{
    MIX_ResumeTrack(m_Engine->MusicTrack);
}

void AudioSystem::StopMusic() const
{
    MIX_StopTrack(m_Engine->MusicTrack, 63);
}

void AudioSystem::PlaySFX(const std::string& path)
{
    const AudioPtr audio = GetOrAdd(path);
    if (audio == nullptr) return;

    if (!MIX_SetTrackAudio(m_Engine->SfxTrack, audio.get())) {
        SDL_Log("Unable to set track audio!: %s", SDL_GetError());
        return;
    }

    MIX_PlayTrack(m_Engine->SfxTrack, m_Engine->SfxPropsID);
}

float AudioSystem::GetMusicVolume() const
{
    return MIX_GetTrackGain(m_Engine->MusicTrack);
}

float AudioSystem::GetSFXVolume() const
{
    return MIX_GetTrackGain(m_Engine->SfxTrack);
}

void AudioSystem::SetMusicVolume(const float volume) const
{
    MIX_SetTrackGain(m_Engine->MusicTrack, Utils::Clamp(volume, 0.f, 1.f));
}

void AudioSystem::SetSFXVolume(const float volume) const
{
    MIX_SetTrackGain(m_Engine->SfxTrack, Utils::Clamp(volume, 0.f, 1.f));
}

AudioPtr AudioSystem::GetOrAdd(const std::string& path)
{
    if (!m_Files.contains(path)) {
        MIX_Audio* audio = MIX_LoadAudio(m_Engine->Mixer, path.c_str(), true);
        if (!audio) {
            SDL_Log("Unable to load audio file!: %s", SDL_GetError());
            return nullptr;
        }

        m_Files[path] = AudioPtr(audio, MIX_DestroyAudio);
    }

    return m_Files[path];
}
