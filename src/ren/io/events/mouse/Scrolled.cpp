#include "io/events/mouse/Scrolled.hpp"
using ren::io::events::mouse::Scrolled;

std::optional<Scrolled> Scrolled::poll(GLFWwindow* window)
{
    static double lastXOffset = 0.0, lastYOffset = 0.0;
    double xoffset = 0.0, yoffset = 0.0;

    struct ScrollData {
        double xoffset;
        double yoffset;
    };
    static ScrollData scrollData = {0.0, 0.0};

    auto scrollCallback = [](GLFWwindow*, double x, double y) {
        scrollData.xoffset += x;
        scrollData.yoffset += y;
    };

    static bool callbackSet = false;
    if (!callbackSet) {
        glfwSetScrollCallback(window, scrollCallback);
        callbackSet = true;
    }

    if (scrollData.xoffset != lastXOffset || scrollData.yoffset != lastYOffset) {
        Scrolled event(window, scrollData.xoffset - lastXOffset, scrollData.yoffset - lastYOffset);
        lastXOffset = scrollData.xoffset;
        lastYOffset = scrollData.yoffset;
        return event;
    }
    return std::nullopt;
}