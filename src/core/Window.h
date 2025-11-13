//
// Created by Anthony Lesch on 11/11/25.
//

#pragma once

#include "ResourceManager.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

class Window final
{
    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;

    int m_Width;
    int m_Height;

public:
    explicit Window(const char* title, int width, int height);
    ~Window();

    void BeginFrame() const;
    void EndFrame() const;

    void RenderTexture(const TexturePtr& texture, const SDL_FRect* sourceRect, const SDL_FRect* destRect) const;

    [[nodiscard]] SDL_Renderer* GetRenderer() const { return m_Renderer; }
    [[nodiscard]] SDL_Rect GetDimensions() const { return { 0, 0, m_Width, m_Height }; }
};
