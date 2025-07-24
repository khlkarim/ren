#pragma once

namespace ren::components
{

class Component
{
public:
	virtual ~Component() = default;
	virtual std::unique_ptr<Component> clone() const = 0;
};

}