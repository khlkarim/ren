#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <algorithm>
#include <string>
#include <cassert>

// Base Component interface
class Component {
public:
    explicit Component(std::string id) : id_(std::move(id)) {}
    virtual ~Component() = default;

    const std::string& id() const { return id_; }

    // Allow extension with polymorphic behavior
    virtual void printInfo() const = 0;

private:
    std::string id_;
};

// Example of a concrete component
class Button : public Component {
public:
    using Component::Component;

    void printInfo() const override {
        std::cout << "Button component, ID: " << id() << "\n";
    }
};

class Slider : public Component {
public:
    using Component::Component;

    void printInfo() const override {
        std::cout << "Slider component, ID: " << id() << "\n";
    }
};

// Composite that holds Components
class Composite {
public:
    Composite() = default;
    Composite(const Composite&) {};
    Composite(Composite&& other) { std::cout << "Called dis" << std::endl; }

    void addComponent(std::unique_ptr<Component> component) {
        components_.emplace_back(std::move(component));
    }

    std::optional<std::reference_wrapper<const Component>> getComponentById(const std::string& id) const {
        auto it = std::find_if(components_.begin(), components_.end(),
            [&id](const std::unique_ptr<Component>& c) {
                return c->id() == id;
            });

        if (it != components_.end()) {
            return **it;
        }
        return std::nullopt;
    }

    void printAllComponents() const {
        for (const auto& c : components_) {
            c->printInfo();
        }
    }

public:
    std::vector<std::unique_ptr<Component>> components_;
};  

struct D
{
    int x;
};

template<class T>
void f(T param)
{
    param.printAllComponents();
}

int main() {
    Composite ui;

    ui.addComponent(std::make_unique<Button>("btn_1"));
    ui.addComponent(std::make_unique<Slider>("sld_1"));

    ui.printAllComponents();

    auto result = ui.getComponentById("btn_1");
    if (result) {
        std::cout << "Found: ";
        result->get().printInfo();
    } else {
        std::cout << "Component not found.\n";
    }

    Composite ui2(std::move(ui));

    std::cout << (&(ui.components_) == &(ui2.components_)) << std::endl;

    std::unique_ptr<Composite> ptr1(std::make_unique<Composite>());

    std::cout << ptr1 << std::endl;

    std::unique_ptr<Composite> ptr2(std::move(ptr1));

    std::cout << ptr1 << std::endl;

    [[maybe_unused]] D d;
    f(ui);

    assert(false && "what");

    return 0;
}
