//
// Created by Anthony Lesch on 11/2/25.
//

#pragma once

#include <memory>
#include <string>

#include "Window.h"

#include "SDL3/SDL.h"

struct GameProps
{
    int Width;
    int Height;
    std::string Title;
};

class Game final
{
    GameProps m_Properties;
    bool m_IsRunning = false;
    uint64_t m_LastTickTime = 0;

    std::unique_ptr<Window> m_Window;

public:
    explicit Game(GameProps gameProps);

    void Initialize();
    void Update();
    void OnEvent(const SDL_Event& event);
    void Shutdown();

    [[nodiscard]] bool IsRunning() const { return m_IsRunning; }
};
