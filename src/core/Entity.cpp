//
// Created by Anthony Lesch on 11/2/25.
//

#include "Entity.h"

static uint32_t s_LastEntityID = 0;

Entity::Entity()
{
    m_EntityID = s_LastEntityID++;
}
