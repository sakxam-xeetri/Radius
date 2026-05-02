#pragma once
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class DisplayManager {
public:
    DisplayManager();
    void begin();
    void showStatus(const String& line1, const String& line2);
    void updateLine1(const String& line1);
    void updateLine2(const String& line2);
    void loop();
    
private:
    LiquidCrystal_I2C lcd;
    String currentL1;
    String currentL2;
    unsigned long lastScrollTime = 0;
    int scrollIndexL2 = 0;
};
