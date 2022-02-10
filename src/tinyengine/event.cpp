#include "tinyengine/event.hpp"
#include "tinyengine/engine.hpp"

struct {
    bool left = false;
    bool right = false;
} MouseState;

void OnWindowResize(GLFWwindow* window, int width, int height) {
    Renderer::SetViewport(0, 0, width, height);
}

bool IsKeyPressing(int key) {
    return glfwGetKey(engine.GetWindow(), key) == GLFW_PRESS;
}

bool IsLeftPressing() {
    return glfwGetMouseButton(engine.GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool IsRightPressing() {
    return glfwGetMouseButton(engine.GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

Point GetMousePosition() {
    double x, y;
    glfwGetCursorPos(engine.GetWindow(), &x, &y);
    return Point{float(x), float(y)};
}
