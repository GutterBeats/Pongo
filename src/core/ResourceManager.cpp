//
// Created by Anthony Lesch on 11/2/25.
//

#include "ResourceManager.h"

#include <memory>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

static ResourceManager* s_Instance = nullptr;

ResourceManager::ResourceManager(SDL_Renderer* renderer)
    : m_Renderer(renderer)
{
}

void ResourceManager::Init(SDL_Renderer* renderer)
{
    if (s_Instance) return;

    s_Instance = new ResourceManager(renderer);

    TTF_Init();
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
    if (m_Textures.contains(texturePath)) return m_Textures.at(texturePath);

    SDL_Texture* texture = IMG_LoadTexture(m_Renderer, texturePath.c_str());
    if (!texture) {
        SDL_Log("Unable to load texture: %s", texturePath.c_str());
        return nullptr;
    }

    TexturePtr tex(texture, SDL_DestroyTexture);
    m_Textures[texturePath] = tex;

    return tex;
}
