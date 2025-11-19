//
// Created by Anthony Lesch on 11/12/25.
//

#pragma once

#include "Window.h"

class Level
{
public:
    virtual ~Level() = default;

    virtual void Initialize() = 0;
    virtual bool IsInitialized() = 0;

    virtual void Update(float deltaSeconds) = 0;
    virtual void Render(const Window& window) = 0;
};
