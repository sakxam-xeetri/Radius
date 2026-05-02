Radius – Circuit Connection (Markdown)
1. ESP32-S3 ↔ MAX98357A Wiring
MAX98357A Pin	ESP32-S3 Pin	Description
VIN	5V	Power supply (recommended for better audio output)
GND	GND	Common ground
BCLK	GPIO 17	I2S Bit Clock
LRC (WS)	GPIO 18	I2S Word Select (Left/Right Clock)
DIN	GPIO 16	I2S Audio Data Input
SD	GND	Shutdown pin (LOW = enabled)
GAIN	NC	Leave unconnected (default gain)
2. Speaker Connection
MAX98357A Pin	Connection
SPK+	Speaker +
SPK−	Speaker −
3. Power Stability (Important)
Component	Connection
1000µF Capacitor (+)	VIN
1000µF Capacitor (−)	GND

Place the capacitor close to the MAX98357A module.

4. Optional Gain Configuration
GAIN Pin State	Effect
Floating (default)	~9 dB gain
Connected to GND	Lower gain
Connected to VIN	Higher gain
5. Block Diagram
ESP32-S3
  ├── GPIO17 → BCLK
  ├── GPIO18 → LRC
  ├── GPIO16 → DIN
  ├── 5V      → VIN
  └── GND     → GND
                ↓
           MAX98357A
                ↓
             Speaker
6. Notes
Use short wires for I2S signals
Ensure common ground between all components
Prefer external 5V supply for stable audio
Avoid powering speaker directly from ESP32