//
// Created by Anthony Lesch on 11/2/25.
//

#include "ResourceManager.h"

#include <memory>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Assets.h"

static ResourceManager* s_Instance = nullptr;

ResourceManager::ResourceManager(SDL_Renderer* renderer)
    : m_Renderer(renderer)
{
}

bool ResourceManager::Initialize(SDL_Renderer* renderer)
{
    if (s_Instance) return true;

    s_Instance = new ResourceManager(renderer);

    if (!TTF_Init()) {
        SDL_Log("Unable to initialize TTF System!: %s", SDL_GetError());
        return false;
    }

    return true;
}

void ResourceManager::Destroy()
{
    if (!s_Instance) return;

    s_Instance->m_Textures.clear();

    delete s_Instance;
    s_Instance = nullptr;

    TTF_Quit();
}

ResourceManager& ResourceManager::GetInstance()
{
    return *s_Instance;
}

TexturePtr ResourceManager::GetTexture(const std::string& texturePath)
{
    if (s_Instance->m_Textures.contains(texturePath)) return s_Instance->m_Textures.at(texturePath);

    SDL_Texture* texture = IMG_LoadTexture(s_Instance->m_Renderer, texturePath.c_str());
    if (!texture) {
        SDL_Log("Unable to load texture: %s", texturePath.c_str());
        return nullptr;
    }

    TexturePtr tex(texture, SDL_DestroyTexture);
    s_Instance->m_Textures[texturePath] = tex;

    return tex;
}

TexturePtr ResourceManager::LoadText(const std::string& text, const float fontSize)
{
    std::string key(text);
    key.append(std::to_string(fontSize));

    if (s_Instance->m_Textures.contains(key)) {
        return s_Instance->m_Textures[key];
    }

    if (!s_Instance->m_Fonts.contains(fontSize)) {
        s_Instance->m_Fonts[fontSize] = TTF_OpenFont(Assets::Fonts::MAPLE_MONO.data(), fontSize);
    }

    SDL_Surface* surface = TTF_RenderText_Solid(s_Instance->m_Fonts[fontSize], text.c_str(), text.length(), { 0, 0, 0, 255 });
    if (!surface) {
        SDL_Log("Unable to create surface from font/text: %s", SDL_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(s_Instance->m_Renderer, surface);
    if (!texture) {
        SDL_Log("Unable to create a texture from surface!: %s", SDL_GetError());
        SDL_DestroySurface(surface);

        return nullptr;
    }

    TexturePtr tex(texture, SDL_DestroyTexture);
    s_Instance->m_Textures[key] = tex;

    return tex;
}
