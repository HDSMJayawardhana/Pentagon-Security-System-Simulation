# Pentagon Security System - Circuit Diagram

## Components List

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno | 1 | Main Controller |
| Push Button | 6 | Sensor Simulation |
| LED (Green) | 1 | Secure State |
| LED (Yellow) | 1 | Alert State |
| LED (Red) | 1 | Lockdown State |
| Buzzer | 1 | Alarm |
| Resistor 220Ω | 3 | LED Current Limiting |
| Resistor 10kΩ | 6 | Pull-down for Buttons |
| Relay Module | 1 | Door Lock Simulation |
| Breadboard | 1 | Circuit Assembly |
| Jumper Wires | Multiple | Connections |

## Pin Connections

```
ARDUINO         →    COMPONENT
─────────────────────────────────────────
Digital Pin 2   →    Sensor Zone 1 (Push Button)
Digital Pin 3   →    Sensor Zone 2 (Push Button)
Digital Pin 4   →    Sensor Zone 3 (Push Button)
Digital Pin 5   →    Auth Card     (Push Button)
Digital Pin 6   →    Auth PIN      (Push Button)
Digital Pin 7   →    Auth Biometric(Push Button)
Digital Pin 8   →    Green LED (+) → 220Ω → GND
Digital Pin 9   →    Yellow LED(+) → 220Ω → GND
Digital Pin 10  →    Red LED   (+) → 220Ω → GND
Digital Pin 11  →    Buzzer (+)
Digital Pin 12  →    Relay IN
Digital Pin 13  →    Status LED
5V              →    VCC (Relay, Pull-ups)
GND             →    GND (All components)
```

## Circuit Schematic (ASCII)

```
                    ARDUINO UNO
                 ┌─────────────────┐
    ZONE1 BTN ──►│ D2          D8  │──► 220Ω ──► GREEN LED ──► GND
    ZONE2 BTN ──►│ D3          D9  │──► 220Ω ──► YELLOW LED──► GND
    ZONE3 BTN ──►│ D4         D10  │──► 220Ω ──► RED LED   ──► GND
    CARD  BTN ──►│ D5         D11  │──► BUZZER(+)──► GND
    PIN   BTN ──►│ D6         D12  │──► RELAY IN
    BIO   BTN ──►│ D7         D13  │──► STATUS LED
                 │                 │
                 │   5V  ──► VCC   │
                 │   GND ──► GND   │
                 └─────────────────┘

Button Wiring (Active LOW with Pull-up):
    5V ──► BTN ──► Arduino Pin ──► Internal Pull-up
    When pressed: Pin reads LOW (triggered)
```

## Zone Architecture

```
┌─────────────────────────────────────────────────┐
│                                                  │
│  ┌────────────────────────────────────────────┐  │
│  │          ZONE 1 - OUTER PERIMETER          │  │
│  │  • Motion Sensors  • Access: Card Only     │  │
│  │                                            │  │
│  │  ┌──────────────────────────────────────┐  │  │
│  │  │       ZONE 2 - INNER PERIMETER       │  │  │
│  │  │  • Door Sensors  • Access: Card+PIN  │  │  │
│  │  │                                      │  │  │
│  │  │  ┌────────────────────────────────┐  │  │  │
│  │  │  │    ZONE 3 - CORE (Pentagon)    │  │  │  │
│  │  │  │  • Vault Sensor                │  │  │  │
│  │  │  │  • Access: Card+PIN+Biometric  │  │  │  │
│  │  │  │  ┌──────────────────────────┐  │  │  │  │
│  │  │  │  │   SECURE AREA (Server)   │  │  │  │  │
│  │  │  │  └──────────────────────────┘  │  │  │  │
│  │  │  └────────────────────────────────┘  │  │  │
│  │  └──────────────────────────────────────┘  │  │
│  └────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────┘
```
