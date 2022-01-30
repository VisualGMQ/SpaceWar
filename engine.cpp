#include "engine.hpp"
#include "event.hpp"

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void Engine::Init(const std::string& title, const Size& size) {
    if (!glfwInit()) {
        throw std::runtime_error("glfw init failed");
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // only for MacOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window_ = glfwCreateWindow(size.x, size.y,
                               title.c_str(),
                               NULL, NULL);

    if (!window_) {
        glfwTerminate();
        throw std::runtime_error("glfw window create failed");
    }

    glfwMakeContextCurrent(window_);

    glfwSetFramebufferSizeCallback(engine.GetWindow(), OnWindowResize);

    Renderer::Init();

    Renderer::SetViewport(0, 0, size.x, size.y);
}

void Engine::SwapContext() {
    glfwSwapBuffers(window_);
}

void Engine::PollEvent() {
    glfwPollEvents();
}

void Engine::Shutdown() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Engine::Update() {
}

void Engine::Render() {
}

Engine engine;
