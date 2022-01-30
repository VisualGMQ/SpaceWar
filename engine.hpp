#pragma once
#include "pch.hpp"
#include "libmath.hpp"
#include "renderer.hpp"
#include <string>
#include <exception>

class Engine final {
public:
    void Init(const std::string& title, const Size& size);
    void Shutdown();

    void Exit() { shouldExit_ = true; }
    bool ShouldExit() const { return glfwWindowShouldClose(window_); }

    // TODO implement your logic here
    void Update();
    // TODO implement your render here
    void Render();

    GLFWwindow* GetWindow() { return window_; }

    void SwapContext();
    void PollEvent();

private:
    bool shouldExit_ = false;

    // window
    GLFWwindow* window_;
};

extern Engine engine;
