//
// Created by Anthony Lesch on 11/11/25.
//

#include "Window.h"

#include <string>

#include "SDL3/SDL_log.h"

Window::Window(const char* title, const int width, const int height)
{
    const bool created = SDL_CreateWindowAndRenderer(
        title,
        width,
        height,
        SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_KEYBOARD_GRABBED,
        &m_Window,
        &m_Renderer
    );

    if (!created || !m_Window || !m_Renderer) {
        std::string error = "Failed to create window and renderer: ";
        error.append(SDL_GetError());

        throw std::runtime_error(error);
    }
}

Window::~Window()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    m_Renderer = nullptr;
    m_Window = nullptr;
}

void Window::BeginFrame() const
{
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_Renderer);
}

void Window::EndFrame() const
{
    SDL_RenderPresent(m_Renderer);
}
