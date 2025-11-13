//
// Created by Anthony Lesch on 11/2/25.
//

#include <utility>

#include "Game.h"

#include "Assets.h"
#include "AudioSystem.h"
#include "ResourceManager.h"
#include "Window.h"

static Game* s_GameInstance;

Game::Game(GameProps gameProps)
    : m_Properties(std::move(gameProps))
{
    s_GameInstance = this;
}

Game& Game::GetInstance()
{
    return *s_GameInstance;
}

void Game::Initialize()
{

    m_Window = std::make_unique<Window>(m_Properties.Title.c_str(), m_Properties.Width, m_Properties.Height);

    SDL_GetCurrentRenderOutputSize(m_Window->GetRenderer(), &m_Properties.Width, &m_Properties.Height);

    ResourceManager::Init(m_Window->GetRenderer());
    if (!AudioSystem::Initialize()) {
        return;
    }

    m_IsRunning = true;
    m_LastTickTime = SDL_GetTicks();
}

void Game::Update()
{
    AudioSystem::Tick();

    const uint64_t currentTime = SDL_GetTicks();
    float deltaTime = static_cast<float>(currentTime - m_LastTickTime) / 1000.0f;

    if (deltaTime > 0.1f) {
        deltaTime = 0.1f;
    }

    m_Window->BeginFrame();

    m_Window->EndFrame();

    m_LastTickTime = currentTime;
}

void Game::OnEvent(const SDL_Event& event)
{
    switch (event.type) {
        case SDL_EVENT_QUIT:
            m_IsRunning = false;
            break;
        case SDL_EVENT_KEY_DOWN: {
            switch (event.key.key) {
                case SDLK_ESCAPE: {
                    SDL_Event quit { SDL_EVENT_QUIT };
                    SDL_PushEvent(&quit);
                    break;
                }
                default: {
                    SDL_Log("Key Pressed: %s", SDL_GetKeyName(SDL_SCANCODE_TO_KEYCODE(event.key.scancode)));
                    break;
                }
            }
        } break;
        default:
            break;
    }
}

void Game::Shutdown()
{
    AudioSystem::Shutdown();
    ResourceManager::Destroy();

    m_Window.reset();

    SDL_Quit();
}
