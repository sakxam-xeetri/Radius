#include "AudioManager.h"
#include "config.h"
#include "DisplayManager.h"

extern DisplayManager* globalDisplay;

AudioManager::AudioManager() : volume(10), playing(false) {
}

void AudioManager::begin() {
    // I2S Configuration
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(volume); // 0...21 max
}

void AudioManager::loop() {
    // This must be called constantly in the main loop to keep audio buffer fed
    audio.loop();
}

void AudioManager::playStream(const char* url) {
    audio.stopSong();
    currentUrl = url;
    audio.connecttohost(url);
    playing = true;
    Serial.print("Playing stream: ");
    Serial.println(url);
    if(globalDisplay) {
        globalDisplay->updateLine1("Playing...");
        globalDisplay->updateLine2(url);
    }
}

void AudioManager::stop() {
    audio.stopSong();
    playing = false;
    Serial.println("Audio playback stopped.");
    if(globalDisplay) {
        globalDisplay->updateLine1("Radius Ready");
        globalDisplay->updateLine2("Stopped");
    }
}

void AudioManager::setVolume(uint8_t vol) {
    if (vol > 21) vol = 21; // ESP32-audioI2S lib limit is 21
    volume = vol;
    audio.setVolume(volume);
    Serial.print("Volume set to: ");
    Serial.println(volume);
}

uint8_t AudioManager::getVolume() {
    return volume;
}

bool AudioManager::isPlaying() {
    return playing;
}

String AudioManager::getCurrentStation() {
    return currentUrl;
}

// Optional callback functions required by ESP32-audioI2S library
// These provide debugging information over serial
void audio_info(const char *info){
    Serial.print("audio_info: "); Serial.println(info);
}
void audio_id3data(const char *info){
    Serial.print("id3data: ");Serial.println(info);
}
void audio_eof_mp3(const char *info){
    Serial.print("eof_mp3: ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station: ");Serial.println(info);
    if(globalDisplay) globalDisplay->updateLine1(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle: ");Serial.println(info);
    if(globalDisplay) globalDisplay->updateLine2(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate: ");Serial.println(info);
}
void audio_commercial(const char *info){
    Serial.print("commercial: ");Serial.println(info);
}
void audio_icyurl(const char *info){
    Serial.print("icyurl: ");Serial.println(info);
}
void audio_lasthost(const char *info){
    Serial.print("lasthost: ");Serial.println(info);
}
