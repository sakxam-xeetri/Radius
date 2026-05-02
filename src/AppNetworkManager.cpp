#include "AppNetworkManager.h"
#include "config.h"

AppNetworkManager::AppNetworkManager(DisplayManager& dispMgr) : display(dispMgr) {
    pinMode(BOOT_BUTTON, INPUT_PULLUP);
}

void AppNetworkManager::begin() {
    display.showStatus("Connecting...", "Checking WiFi");
    
    // AutoConnect
    // wifiManager.setDebugOutput(false);
    if (!wifiManager.autoConnect("Radius-Setup")) {
        Serial.println("Failed to connect and hit timeout");
        display.showStatus("WiFi Failed", "Restarting...");
        delay(3000);
        ESP.restart();
    }
    
    Serial.println("WiFi Connected!");
    display.showStatus("WiFi Connected", WiFi.localIP().toString());
}

void AppNetworkManager::loop() {
    // Check if BOOT button is pressed for 3 seconds to trigger config portal
    if (digitalRead(BOOT_BUTTON) == LOW) {
        if (!buttonPressed) {
            buttonPressed = true;
            buttonPressTime = millis();
        } else {
            if (millis() - buttonPressTime > 3000) {
                Serial.println("Button held for 3s. Starting Config Portal...");
                display.showStatus("AP Mode Active", "Connect to Radius-Setup");
                
                // Start config portal blocking mode
                if (!wifiManager.startConfigPortal("Radius-Setup")) {
                    Serial.println("Failed to connect or hit timeout");
                    display.showStatus("WiFi Failed", "Restarting...");
                    delay(3000);
                    ESP.restart();
                }
                
                Serial.println("Connected after config portal.");
                display.showStatus("WiFi Connected", WiFi.localIP().toString());
                buttonPressed = false;
            }
        }
    } else {
        buttonPressed = false;
    }
}

bool AppNetworkManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
