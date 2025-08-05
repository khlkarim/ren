#include <ren/core/Scene.hpp>
using ren::core::Scene;
using ren::ecs::components::Hierarchy;

Scene::Scene()
{   
    spdlog::info("Scene Constructor");
}

Scene::~Scene()
{
    spdlog::info("Scene Destructor");
}

Hierarchy& Scene::getHierarchy()
{
    return this->hierarchy;
}

const Hierarchy& Scene::getHierarchy() const
{
    return this->hierarchy;
}

void Scene::setHierarchy(const Hierarchy& hierarchy)
{
    this->hierarchy = hierarchy;
    spdlog::info("Hierarchy set");
}