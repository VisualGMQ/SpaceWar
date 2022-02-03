#include "event.hpp"

void OnWindowResize(GLFWwindow* window, int width, int height) {
    Renderer::SetViewport(0, 0, width, height);
}
