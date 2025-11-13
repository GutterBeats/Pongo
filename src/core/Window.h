//
// Created by Anthony Lesch on 11/11/25.
//

#pragma once

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

class Window final
{
    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;

public:
    explicit Window(const char* title, int width, int height);
    ~Window();

    void BeginFrame() const;
    void EndFrame() const;

    [[nodiscard]] SDL_Renderer* GetRenderer() const { return m_Renderer; }
};
