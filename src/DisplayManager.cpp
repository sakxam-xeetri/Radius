#include "DisplayManager.h"
#include "config.h"

DisplayManager::DisplayManager() : lcd(LCD_ADDR, 16, 2) {}

void DisplayManager::begin() {
    Wire.begin(I2C_SDA, I2C_SCL);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Radius Audio");
    lcd.setCursor(0, 1);
    lcd.print("Starting...");
}

void DisplayManager::showStatus(const String& line1, const String& line2) {
    updateLine1(line1);
    updateLine2(line2);
}

void DisplayManager::updateLine1(const String& line1) {
    if (currentL1 != line1) {
        currentL1 = line1;
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 0);
        lcd.print(currentL1.substring(0, 16));
    }
}

void DisplayManager::updateLine2(const String& line2) {
    if (currentL2 != line2) {
        currentL2 = line2;
        scrollIndexL2 = 0;
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        if (currentL2.length() <= 16) {
            lcd.print(currentL2);
        } else {
            lcd.print(currentL2.substring(0, 16));
        }
    }
}

void DisplayManager::loop() {
    if (currentL2.length() > 16) {
        if (millis() - lastScrollTime > 400) { // scroll speed
            lastScrollTime = millis();
            lcd.setCursor(0, 1);
            String padded = currentL2 + "    " + currentL2;
            lcd.print(padded.substring(scrollIndexL2, scrollIndexL2 + 16));
            scrollIndexL2++;
            if (scrollIndexL2 > currentL2.length() + 3) {
                scrollIndexL2 = 0;
            }
        }
    }
}
