

**Arduino-based recoil simulation system for laser tag / airsoft training guns**

This project brings realistic recoil to toy guns or laser tag rifles using a servo, tracks ammunition, and includes a two-touch reload gesture.

## Features

- Servo-based recoil simulation (quick kick-back)
- 20-round ammunition counter
- Realistic two-touch reload gesture
- Safety lever (arm/disarm)
- Trigger button with debounce
- LED indicator for system armed status
- Serial output for debugging (hit locations)

## Hardware Requirements

| Component              | Description                              |
|------------------------|------------------------------------------|
| Arduino Uno / Nano     | Main controller                          |
| Servo                  | SG90 or similar (for recoil)             |
| Lever switch           | Master safety switch                     |
| Touch sensors (×2)     | Capacitive or simple buttons             |
| Push button            | Trigger                                  |
| LED                    | Armed status (can use built-in on D13)   |

## Pin Connections

| Component              | Arduino Pin | Description                          |
|------------------------|-------------|--------------------------------------|
| Touch Sensor 1         | D2          | Start of reload gesture              |
| Touch Sensor 2         | D3          | Complete reload gesture              |
| Trigger Button         | D4          | Fire trigger                         |
| Servo (Recoil)         | D5          | PWM signal for recoil                |
| Lever Switch           | D7          | Safety lever (HIGH = armed)          |
| LED Indicator          | D13         | System armed indicator               |

**Power**:  
- Servo: Connect VCC to 5V, GND to common ground  
- Add a 100µF+ capacitor across servo power lines to prevent brownouts

## How It Works

1. **Safety Lever** (D7) must be HIGH (ON) for the system to respond.
2. **Reload**:
   - Touch Sensor 1 (D2) → starts reload timer (1.5 seconds)
   - Touch Sensor 2 (D3) within time window → reloads to 20 rounds
3. **Fire**:
   - Press trigger button (D4)
   - If ammo remains → decrements count, simulates hit, triggers recoil
4. **Recoil**:
   - Servo moves to 50° (kick) for 80 ms, then returns to 90° (neutral)

## Configuration (Edit in Code)

| Constant                  | Default | Description                          |
|---------------------------|---------|--------------------------------------|
| `MAX_ROUNDS`              | 20      | Magazine capacity                    |
| `RECOIL_FORWARD`          | 50      | Servo angle for recoil kick          |
| `RECOIL_NEUTRAL`          | 90      | Resting servo position               |
| `RECOIL_DURATION_MS`      | 80      | Recoil pulse duration (ms)           |
| `DEBOUNCE_DELAY_MS`       | 300     | Delay after firing                   |
| `RELOAD_TIMEOUT_MS`       | 1500    | Max time between two touches         |

## Installation

1. Wire components according to the pin table above.
2. Install the **Servo** library (built-in with Arduino IDE).
3. Upload the code to your Arduino.
4. Open Serial Monitor at 115200 baud for debug messages.

## Future Enhancements

- Add laser/IR transmitter for real target hits
- Sound effects (buzzer or DFPlayer)
- LCD ammo counter
- Magazine release button
- Bluetooth for multiplayer stats

## picturess
![Project Prototype](https://raw.githubusercontent.com/phonot/SLRM/main/right_.jpg)

![Project Prototype](https://raw.githubusercontent.com/phonot/SLRM/main/left.jpg)

## License

MIT License – free to use, modify, and share.

---
Made with for realistic laser tag and training simulations feel free to expand upon
[Thank you Raki for helping me on this project]

