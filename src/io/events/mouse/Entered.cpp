#include <io/events/mouse/Entered.hpp>
using ren::io::events::mouse::Entered;

std::optional<Entered> Entered::poll(GLFWwindow* window)
{
    static bool wasInside = 1;

    if (glfwGetWindowAttrib(window, GLFW_HOVERED)) {
        if(!wasInside)
        {
            return Entered(window, 1);
        }
    }
    else if (wasInside)
    {
        return Entered(window, 0);
    }

    return std::nullopt;
}