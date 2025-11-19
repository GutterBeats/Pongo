//
// Created by Anthony Lesch on 11/2/25.
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

using TexturePtr = std::shared_ptr<SDL_Texture>;

class ResourceManager final
{
    explicit ResourceManager(SDL_Renderer* renderer);

public:
    static bool Initialize(SDL_Renderer* renderer);
    static void Destroy();
    static ResourceManager& GetInstance();

    [[nodiscard]] static TexturePtr GetTexture(const std::string& texturePath);
    [[nodiscard]] static TexturePtr LoadText(const std::string& text, float fontSize);

private:

    SDL_Renderer* m_Renderer;
    std::unordered_map<std::string, TexturePtr> m_Textures;
    std::unordered_map<float, TTF_Font*> m_Fonts;
};
