#include <core/Scene.hpp>
using ren::Scene;
using ren::Camera; 
using ren::Entity; 
using ren::components::Hierarchy;

Scene::Scene()
{   
    spdlog::info("Scene Constructor");
}

Scene::~Scene()
{
    spdlog::info("Scene Destructor");
}

void Scene::setCamera(const Camera& camera)
{
    this->camera = camera;
    spdlog::info("Camera set");
}

Camera& Scene::getCamera()
{
    return this->camera;
}

const Camera& Scene::getCamera() const
{
    return this->camera;
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

void Scene::render()
{
    systems::RenderingSystem renderer;
    renderer.render(this->camera, this->hierarchy);
}