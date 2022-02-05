#pragma once

#include "pch.hpp"
#include "tool.hpp"
#include "log.hpp"
#include "libmath.hpp"

class Audio final {
public:
    static void Init();
    static void Shutdown();
};

class Sound final {
public:
    Sound(const std::string& filename);
    ~Sound();

    void Play();
    void Pause();
    void Stop();
    void SetVolume(float volume);
    void EnableLoop();
    void DisableLoop();

private:
    ma_sound sound_;
};
