#include "audio.hpp"

ma_engine AudioEngine;

void Audio::Init() {
    ma_result result;
    result = ma_engine_init(NULL, &AudioEngine);
    if (result != MA_SUCCESS) {
        FATAL_ERROR("sound system init failed");
    }
    ma_engine_start(&AudioEngine);
}

void Audio::Shutdown() {
    ma_engine_stop(&AudioEngine);
}

Sound::Sound(const std::string& filename) {
    ma_result result;
    result = ma_sound_init_from_file(&AudioEngine,
                                     filename.c_str(),
                                     0,
                                     NULL, NULL,
                                     &sound_);
    if (result != MA_SUCCESS) {
        Log("%s sound load failed!", filename.c_str());
    }
}

void Sound::Play() {
    ma_sound_start(&sound_);
}

void Sound::Pause() {
}

void Sound::Stop() {
    ma_sound_stop(&sound_);
}

Sound::~Sound() {
    ma_sound_uninit(&sound_);
}

void Sound::SetVolume(float volume) {
    ma_sound_set_volume(&sound_, Clamp(0.0f, 10.0f, volume));
}

void Sound::EnableLoop() {
    ma_sound_set_looping(&sound_, true);
}

void Sound::DisableLoop() {
    ma_sound_set_looping(&sound_, false);
}
