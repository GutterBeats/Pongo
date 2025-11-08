//
// Created by Anthony Lesch on 11/2/25.
//

#pragma once

#include <cstdint>

#include "SDL3/SDL_render.h"

class Entity
{
    bool m_IsActive = true;
    uint32_t m_EntityID = 0;

public:
    Entity();
    virtual ~Entity() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;

    [[nodiscard]] bool IsActive() const { return m_IsActive; }
    [[nodiscard]] uint32_t GetEntityID() const { return m_EntityID; }
};
