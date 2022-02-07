#include "tinyengine/engine.hpp"

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void Engine::Init(const std::string& title, const Size& size, Scence* scence) {
    if (!glfwInit()) {
        FATAL_ERROR("glfw init failed");
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // only for MacOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window_ = glfwCreateWindow(size.w, size.h,
                               title.c_str(),
                               nullptr, nullptr);

    if (!window_) {
        glfwTerminate();
        FATAL_ERROR("glfw window create failed");
    }

    glfwMakeContextCurrent(window_);

    glfwSetFramebufferSizeCallback(engine.GetWindow(), OnWindowResize);

    if (!gladLoadGL(glfwGetProcAddress)) {
        glfwTerminate();
        FATAL_ERROR("glad load failed");
    }

    int width, height;
    glfwGetFramebufferSize(GetWindow(), &width, &height);
    Renderer::SetViewport(0, 0, width, height);

    Renderer::Init();
    Log("render system init OK");
    Renderer::SetClearColor(Color{0.1, 0.1, 0.1, 1});
    
    Audio::Init();
    Log("sound system init OK");

    scence_.reset(scence);
    scence_->OnInit();
}

void Engine::ChangeScence(Scence* scence) {
    if (scence_)
        scence_->OnQuit();
    scence_.reset(scence);
    scence_->OnInit();
}

void Engine::PushScence() {
    if (scence_) {
        scence_->OnQuit();
        scenceStack_.push(std::move(scence_));
        scence_ = nullptr;
    }
}

void Engine::PopScence() {
    scence_ = std::move(scenceStack_.top());
    scence_->OnInit();
    scenceStack_.pop();
}

void Engine::SwapContext() {
    glfwSwapBuffers(window_);
}

void Engine::PollEvent() {
    glfwPollEvents();
}

void Engine::Shutdown() {
    Audio::Shutdown();
    if (scence_)
        scence_->OnQuit();
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Engine::Update(float deltaTime) {
    if (scence_)
        scence_->OnUpdate(deltaTime);
    Renderer::Update();
}

void Engine::Render() {
    if (scence_)
        scence_->OnRender();
}

Engine engine;
