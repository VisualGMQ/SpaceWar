#include "tinyengine/tinyengine.hpp"

class TestAudio : public Scence {
public:
    void OnInit() override {
        sound_.reset(new Sound("assets/test/goodbyESAKA.wav"));
        sound_->SetVolume(10);
        sound_->Play();
    }

    void OnRender() override {
    }

    void OnQuit() override {
        sound_.reset();
    }

private:
    Unique<Sound> sound_;
};

RUN_WINDOW("test renderer", 1024, 720, TestAudio)
