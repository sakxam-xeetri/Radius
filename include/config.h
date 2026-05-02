#pragma once

// I2S Pins for MAX98357A on ESP32-S3
// These match the circuit diagram
#define I2S_BCLK      17
#define I2S_LRC       18
#define I2S_DOUT      16

// I2C Pins for 16x2 LCD Display
#define I2C_SDA       8
#define I2C_SCL       9
#define LCD_ADDR      0x27

// Built-in Button for WiFi Reset
#define BOOT_BUTTON   0

// Web Server Port
#define WEB_PORT      80
