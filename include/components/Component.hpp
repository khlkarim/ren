#pragma once

#include <memory>

namespace ren::components
{

class Component
{
public:
	virtual std::unique_ptr<Component> clone() const = 0;
};

}