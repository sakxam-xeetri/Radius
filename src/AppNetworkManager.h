#pragma once
#include <WiFiManager.h> // tzapu library
#include "DisplayManager.h"

class AppNetworkManager {
public:
    AppNetworkManager(DisplayManager& dispMgr);
    void begin();
    void loop();
    bool isConnected();
private:
    DisplayManager& display;
    WiFiManager wifiManager;
    unsigned long buttonPressTime = 0;
    bool buttonPressed = false;
};
