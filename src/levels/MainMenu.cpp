//
// Created by Anthony Lesch on 11/12/25.
//

#include <cmath>

#include "MainMenu.h"

#include "core/Assets.h"
#include "core/AudioSystem.h"
#include "core/Utils.h"

void MainMenu::Initialize()
{
    m_Background = ResourceManager::GetTexture(Assets::Textures::BACKGROUND);
    m_Logo = ResourceManager::GetTexture(Assets::Textures::LOGO);
    m_Table = ResourceManager::GetTexture(Assets::Textures::TABLE);

    AudioSystem::GetInstance().PlayMusic(Assets::Audio::DANGEROUS_CIRCUITS);
}

void MainMenu::Render(Window& window)
{
    const SDL_Rect dimensions = window.GetDimensions();

    window.RenderTexture(m_Background, nullptr, nullptr);
    window.RenderTexture(m_Table, nullptr, nullptr);

    constexpr float scaleFactor = 0.5f;
    const float targetHeight = std::floorf(static_cast<float>(m_Logo->h) * scaleFactor);
    const float targetWidth = std::floorf(static_cast<float>(m_Logo->w) * scaleFactor);

    const SDL_FRect destination = {
        static_cast<float>(dimensions.w) / 2.f - targetWidth / 2.f,
        m_YPosition,
        targetWidth,
        targetHeight
    };

    window.RenderTexture(m_Logo, nullptr, &destination);
}

void MainMenu::Update(const float deltaSeconds)
{
    static bool reversed = false;
    constexpr float speed = 48.f;
    float movementThisFrame = speed * deltaSeconds;

    if (reversed) {
        movementThisFrame *= -1;
    }

    m_YPosition += movementThisFrame;
    m_YPosition = Utils::Clamp(m_YPosition, 75.f, 100.f);

    if (m_YPosition >= 100.f || m_YPosition <= 75.f) {
        reversed = !reversed;
    }
}
