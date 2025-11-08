//
// Created by Anthony Lesch on 11/2/25.
//

#include "Layer.h"

Layer::Layer()
{
}

Layer::~Layer()
{
    Entities.clear();
}

void Layer::Update(const float deltaTime)
{
    for (const auto& entity : Entities) {
        entity->Update(deltaTime);
    }
}

void Layer::Draw(SDL_Renderer* renderer)
{
    for (const auto& entity : Entities) {
        entity->Draw(renderer);
    }
}

void Layer::AddEntity(std::unique_ptr<Entity> entity)
{
    Entities.push_back(std::move(entity));
}
