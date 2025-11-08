//
// Created by Anthony Lesch on 11/2/25.
//

#include <utility>

#include "Game.h"
#include "Assets.h"
#include "AudioSystem.h"
#include "ResourceManager.h"

static Game* s_GameInstance;

Game::Game(GameProps gameProps)
    : m_Properties(std::move(gameProps))
{
    s_GameInstance = this;
    m_Layers = std::vector<std::unique_ptr<Layer>>();
}

Game& Game::GetInstance()
{
    return *s_GameInstance;
}

void Game::Initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        std::string error = "Failed to initialize SDL: ";
        error.append(SDL_GetError());

        throw std::runtime_error(error);
    }

    const bool created = SDL_CreateWindowAndRenderer(
        m_Properties.Title.c_str(),
        m_Properties.Width,
        m_Properties.Height,
        SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_KEYBOARD_GRABBED,
        &m_Window,
        &m_Renderer
    );

    if (!created || !m_Window || !m_Renderer) {
        std::string error = "Failed to create window and renderer: ";
        error.append(SDL_GetError());

        throw std::runtime_error(error);
    }

    ResourceManager::Init(m_Renderer);
    if (!AudioSystem::Initialize()) {
        return;
    }

    m_AudioSystem = &AudioSystem::GetInstance();

    m_IsRunning = true;
    m_LastTickTime = SDL_GetTicks();
}

void Game::Update()
{
    AudioSystem::Tick();

    SDL_SetRenderDrawColor(m_Renderer, 0xDE, 0x54, 0x1E, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_Renderer);

    const uint64_t currentTime = SDL_GetTicks();
    float deltaTime = static_cast<float>(currentTime - m_LastTickTime) / 1000.0f;

    if (deltaTime > 0.1f) {
        deltaTime = 0.1f;
    }

    for (const auto& layer : m_Layers) {
        layer->Update(deltaTime);
        layer->Draw(m_Renderer);
    }

    SDL_RenderPresent(m_Renderer);

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

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    m_Renderer = nullptr;
    m_Window = nullptr;
    m_AudioSystem = nullptr;

    SDL_Quit();
}
