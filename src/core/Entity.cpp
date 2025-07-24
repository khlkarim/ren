#include <core/Entity.hpp>
using ren::Entity;

Entity::Entity()
{
    spdlog::info("Entity Constructor");
}

Entity::~Entity()
{
    spdlog::info("Entity Destructor");
}