//
// Created by Anthony Lesch on 11/2/25.
//

#pragma once

#include <memory>
#include <vector>

#include "Entity.h"

class Layer
{
public:
    Layer();
    virtual ~Layer();

    virtual void OnAttach() { }
    virtual void OnDetach() { }

    virtual void Update(float deltaTime);
    virtual void Draw(SDL_Renderer* renderer);

    void AddEntity(std::unique_ptr<Entity> entity);

protected:

    std::vector<std::unique_ptr<Entity>> Entities;
};
