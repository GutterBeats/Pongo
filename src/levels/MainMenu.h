//
// Created by Anthony Lesch on 11/12/25.
//

#pragma once

#include "core/Level.h"
#include "core/ResourceManager.h"

class MainMenu final : public Level
{
    TexturePtr m_Background;
    TexturePtr m_Table;
    TexturePtr m_Logo;

    float m_YPosition = 75.f;
    bool m_IsInitialized = false;

public:
    void Initialize() override;

    bool IsInitialized() override;

    void Update(float deltaSeconds) override;

    void Render(const Window& window) override;
};
