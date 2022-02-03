#include "tinyengine/engine.hpp"
#include "tinyengine/event.hpp"
#include "tinyengine/camera.hpp"

class WelcomeScene final: public Scence {
public:
    void OnInit() override {
        Log("init scence");
        camera.Move(Point{0, 0});
        camera.Scale(Point{1, 1});
    }

    void OnUpdate(float dt) override {
    }

    void OnQuit() override {
        Log("quit scence");
    }

private:
    Camera camera;
};

RUN_WINDOW("Space Sector", 1024, 720, WelcomeScene)
