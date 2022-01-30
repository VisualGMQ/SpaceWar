#include "engine.hpp"
#include "event.hpp"

int main(int argc, char** argv) {
    engine.Init("sandbox", Size{720, 480});

    Color color{0.1, 0.1, 0.1, 1};
    Renderer::SetClearColor(color);
    while (!engine.ShouldExit()) {
        Renderer::Clear();
        engine.PollEvent();
        engine.Update();
        engine.Render();
        engine.SwapContext();
    }

    engine.Shutdown();
    return 0;
}
