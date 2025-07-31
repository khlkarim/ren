#include <io/events/mouse/Moved.hpp>
using ren::io::events::mouse::Moved;

std::optional<Moved> Moved::poll(GLFWwindow* window)
{
    static double lastX = -1.0, lastY = -1.0;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (lastX == -1.0 && lastY == -1.0) {
        lastX = xpos;
        lastY = ypos;
        return std::nullopt;
    }

    if (xpos != lastX || ypos != lastY) {
        Moved moved(window, xpos, ypos);
        lastX = xpos;
        lastY = ypos;
        return moved;
    }

    return std::nullopt;
}