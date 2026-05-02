#pragma once
#include "Audio.h"
#include <Arduino.h>

class AudioManager {
public:
    AudioManager();
    void begin();
    void loop();
    void playStream(const char* url);
    void stop();
    void setVolume(uint8_t vol);
    uint8_t getVolume();
    bool isPlaying();
    String getCurrentStation();

private:
    Audio audio;
    uint8_t volume;
    bool playing;
    String currentUrl;
};
