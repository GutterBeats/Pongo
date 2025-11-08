//
// Created by Anthony Lesch on 11/2/25.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Layer.h"

#include "SDL3/SDL.h"

struct GameProps
{
    uint16_t Width;
    uint16_t Height;
    std::string Title;
};

class Game final
{
    GameProps m_Properties;
    bool m_IsRunning = false;
    uint64_t m_LastTickTime = 0;

    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;
    class AudioSystem* m_AudioSystem = nullptr;

    std::vector<std::unique_ptr<Layer>> m_Layers;

public:
    explicit Game(GameProps gameProps);

    static Game& GetInstance();

    void Initialize();
    void Update();
    void OnEvent(const SDL_Event& event);
    void Shutdown();

    [[nodiscard]] bool IsRunning() const { return m_IsRunning; }
};
