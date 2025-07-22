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

template<typename T>
void Entity::setComponent(const T& component)
{
    this->components.push_back(std::make_unique<T>(component));
}

template<typename T>
std::optional<std::reference_wrapper<const T>> Entity::getComponent() const
{
    auto it = std::find_if(this->components.begin(), this->components.end(),
        [&](const std::unique_ptr<Component>& comp) {
            return typeid(*comp) == typeid(T);
        }
    );

    if(it == this->components.end())
    {
        return **it;
    }
    else 
    {
        return std::nullopt;
    }
}