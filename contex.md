1. Project Overview
Radius is a Wi-Fi–enabled smart speaker built using the ESP32-S3 and MAX98357A I2S audio amplifier. It allows users to stream and play audio directly from the internet through a custom web interface. The device acts as a standalone audio system that can be controlled from any smartphone, laptop, or tablet connected to the same network.

2. Objectives


Build a wireless audio streaming device


Enable real-time control via a web browser


Implement digital audio output using I2S protocol


Create a scalable platform for future AI and IoT integration



3. Key Features


Wi-Fi audio streaming


Web-based control interface


Real-time audio playback


Support for internet radio and custom stream URLs


Compact and low-cost design


Expandable for AI and smart assistant features



4. System Architecture
User Device (Phone/Laptop)            ↓     Web Interface (Browser)            ↓       ESP32-S3 (Wi-Fi + Control)            ↓   Audio Decoder (MP3/AAC Stream)            ↓        I2S Digital Output            ↓     MAX98357A Amplifier            ↓           Speaker

5. Components Required


ESP32-S3 Development Board


MAX98357A I2S DAC + Amplifier


4Ω / 8Ω Speaker (3W recommended)


Jumper Wires


Power Supply (5V recommended)


Capacitor (1000µF for stability)



6. Circuit Connections
ComponentConnectionVIN (MAX98357A)5VGNDGNDBCLKGPIO 17LRC (WS)GPIO 18DINGPIO 16SDGNDSpeakerSPK+ / SPK−VCC (LCD)5VGND (LCD)GNDSDA (LCD)GPIO 8SCL (LCD)GPIO 9

7. Software Requirements


Arduino IDE


ESP32 Board Package


ESP32-audioI2S Library


WiFi and WebServer Libraries



8. Working Principle


ESP32 connects to a Wi-Fi network


A web server is hosted on the ESP32


User opens the web interface via IP address


User selects or enters an audio stream URL


ESP32 fetches and decodes the audio stream


Audio data is sent via I2S protocol


MAX98357A amplifies the signal


Speaker outputs sound



9. Web Interface Features


Predefined radio station buttons


Custom URL input field


One-click audio streaming


Real-time control



10. Advantages


Wireless operation


Low power consumption


Easy to control via browser


No external DAC required


Highly customizable



11. Limitations


Requires stable Wi-Fi connection


Does not support direct YouTube links


Dependent on valid audio stream URLs



12. Applications


Internet radio player


Smart home speaker


Notification and alert system


Educational audio device


Assistive reading system



13. Future Enhancements


OLED display for track info


Volume control via web UI


Bluetooth audio mode


Voice assistant integration


Mobile app control


Multi-room audio system



14. Conclusion
Radius demonstrates how a compact microcontroller like the ESP32-S3 can be transformed into a powerful smart audio device. By combining wireless communication, real-time streaming, and digital audio processing, this project serves as a strong foundation for advanced IoT and AI-based systems.