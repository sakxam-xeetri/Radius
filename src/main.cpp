#include <Arduino.h>
#include "DisplayManager.h"
#include "AppNetworkManager.h"
#include "AudioManager.h"
#include "WebServerHandler.h"

DisplayManager displayManager;
AppNetworkManager networkManager(displayManager);
AudioManager audioManager;
WebServerHandler webServer(audioManager);

DisplayManager* globalDisplay = &displayManager;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n\n--- Radius Wi-Fi Audio Streaming ---");

    displayManager.begin();
    networkManager.begin();
    audioManager.begin();
    webServer.begin();

    Serial.println("System initialized successfully.");
    displayManager.showStatus("Radius Ready", WiFi.localIP().toString());
}

void loop() {
    // These functions MUST be non-blocking
    networkManager.loop();
    webServer.loop();
    audioManager.loop(); // Crucial for uninterrupted I2S audio stream
    displayManager.loop(); // For scrolling long text
}
