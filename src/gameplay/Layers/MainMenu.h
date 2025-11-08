//
// Created by Anthony Lesch on 11/2/25.
//

#pragma once

#include "core/Layer.h"

class MainMenu final : public Layer
{
public:
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;
};
