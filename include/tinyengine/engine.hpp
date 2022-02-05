#pragma once
#include "pch.hpp"
#include "libmath.hpp"
#include "renderer.hpp"
#include "scence.hpp"
#include "inner_bmpfont.hpp"
#include "event.hpp"
#include "tool.hpp"
#include "audio.hpp"

class Engine final {
public:
    void Init(const std::string& title, const Size& size, Scence* scence);
    void Shutdown();

    void Exit() { shouldExit_ = true; }
    bool ShouldExit() const { return glfwWindowShouldClose(window_); }

    void Update(float deltaTime);
    void Render();

    GLFWwindow* GetWindow() { return window_; }

    void SwapContext();
    void PollEvent();

    void ChangeScence(Scence* scence);
    void PushScence();
    void PopScence();
    bool ScenceStackEmpty() { return scenceStack_.empty(); }

    inline Size GetWindowSize() const {
        int w, h;
        glfwGetWindowSize(window_, &w, &h);
        return Size{float(w), float(h)};
    }

    InnerBmpFont& GetInnerBmpFont() { return innerBmpFont_; }

private:
    bool shouldExit_ = false;

    // window
    GLFWwindow* window_;
    Unique<Scence> scence_ = nullptr;
    std::stack<Unique<Scence>> scenceStack_;
    InnerBmpFont innerBmpFont_;
};

#define RUN_WINDOW(title, w, h, scence) \
int main(int argc, char** argv) { \
    engine.Init(title, Size{w, h}, new scence); \
    GLfloat deltaTime = 0.0f; \
    GLfloat lastFrame = 0.0f; \
    while (!engine.ShouldExit()) { \
        float currentFrame = glfwGetTime(); \
        deltaTime = currentFrame - lastFrame; \
        lastFrame = currentFrame; \
        Renderer::Clear(); \
        engine.Update(deltaTime); \
        engine.Render(); \
        engine.SwapContext(); \
        engine.PollEvent(); \
    } \
    engine.Shutdown(); \
    return 0; \
}

extern Engine engine;
