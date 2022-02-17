#include "tinyengine/event.hpp"
#include "tinyengine/engine.hpp"

struct MouseState {
    bool left = false;
    bool right = false;
};

struct {
    MouseState oldState;
    MouseState state;
} MouseContext;

void MouseBtnCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            MouseContext.state.left = true;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            MouseContext.state.right = true;
        }
    } else if (action == GLFW_RELEASE) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            MouseContext.state.left = false;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            MouseContext.state.right = false;
        }
    }
}

void EventUpdate() {
    MouseContext.oldState = MouseContext.state;
}

Size WindowInitSize;

void InitEvent(const Size& windowInitSize) {
    WindowInitSize = windowInitSize;
}

void OnWindowResize(GLFWwindow* window, int width, int height) {
    Renderer::SetViewport(0, 0, width, height);
}

bool IsKeyPressing(int key) {
    return glfwGetKey(engine.GetWindow(), key) == GLFW_PRESS;
}

bool IsLeftPressing() {
    return MouseContext.state.left;
}

bool IsRightPressing() {
    return MouseContext.state.right;
}

bool IsLeftPressed() {
    return MouseContext.state.left && !MouseContext.oldState.left;
}

bool IsRightPressed() {
    return MouseContext.state.right && !MouseContext.oldState.right;
}

Point GetMousePosition() {
    double x, y;
    glfwGetCursorPos(engine.GetWindow(), &x, &y);
    return Point{float(x), float(y)};
}

Point GetMousePositionMapped() {
    double x, y;
    glfwGetCursorPos(engine.GetWindow(), &x, &y);
    return Point{float(x) * WindowInitSize.w / engine.GetWindowSize().w,
                 float(y) * WindowInitSize.h / engine.GetWindowSize().h};
}
