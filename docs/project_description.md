# 🔐 Security System Simulation of the Pentagon

## Project Information

| Field | Details |
|-------|---------|
| **Project Title** | Security System Simulation of the Pentagon |
| **Course Code** | GP106 – Computer Engineering |
| **Year** | 2021 |
| **Level** | First Year Final Project |
| **Institution** | University of Peradeniya |
| **Department** | Department of Computer Engineering |
| **Tools Used** | Arduino Uno, Tinkercad |

---

## 1. 📌 Introduction

In today's world, **high-security infrastructures** such as
government buildings, military installations, and research
facilities require **robust and fail-safe access control systems**.
These systems must be capable of:

- Managing **multi-level authorization**
- Detecting **intrusions instantly**
- Operating with **zero false negatives**
- Responding to threats **automatically**

The **Pentagon** — headquarters of the United States Department
of Defense — is one of the most secured buildings in the world.
It employs **tiered security zones**, where each zone requires
a higher level of authorization to access.

This project simulates such a **multi-layered security system**
using **digital logic design** principles and **Arduino
microcontroller** programming, providing a practical
demonstration of how real-world security systems operate
at the hardware level.

---

## 2. 🎯 Problem Definition

### Problem Statement

> *High-security infrastructures require fail-safe access
> control architectures to manage multi-level authorization
> and detect intrusions instantly without false negatives.*

### Challenges Addressed

```
┌─────────────────────────────────────────────────────┐
│  CHALLENGE 1: Multi-Level Authorization             │
│  → Different zones need different access levels     │
│  → Must prevent unauthorized zone entry             │
├─────────────────────────────────────────────────────┤
│  CHALLENGE 2: Instant Intrusion Detection           │
│  → System must respond in real-time                 │
│  → No delay between breach and alarm                │
├─────────────────────────────────────────────────────┤
│  CHALLENGE 3: Zero False Negatives                  │
│  → Every breach must be detected                    │
│  → No unauthorized access should be missed         │
├─────────────────────────────────────────────────────┤
│  CHALLENGE 4: Fail-Safe Operation                   │
│  → System must default to LOCKDOWN on failure       │
│  → Cannot remain unlocked during system error       │
└─────────────────────────────────────────────────────┘
```

---

## 3. 🏛️ System Architecture

### 3.1 Zone Design

The Pentagon security system is divided into
**three concentric security zones**, each with
increasing levels of security:

```
┌─────────────────────────────────────────────────────┐
│                                                     │
│   ┌─────────────────────────────────────────────┐  │
│   │           ZONE 1 - OUTER PERIMETER          │  │
│   │                                             │  │
│   │  Security Level  : LOW                      │  │
│   │  Access Required : Card Only                │  │
│   │  Sensors         : Motion Detectors         │  │
│   │  Coverage        : Building Entrance        │  │
│   │                                             │  │
│   │   ┌─────────────────────────────────────┐   │  │
│   │   │       ZONE 2 - INNER PERIMETER      │   │  │
│   │   │                                     │   │  │
│   │   │  Security Level  : MEDIUM           │   │  │
│   │   │  Access Required : Card + PIN       │   │  │
│   │   │  Sensors         : Door Sensors     │   │  │
│   │   │  Coverage        : Office Areas     │   │  │
│   │   │                                     │   │  │
│   │   │   ┌─────────────────────────────┐   │   │  │
│   │   │   │   ZONE 3 - CORE PENTAGON    │   │   │  │
│   │   │   │                             │   │   │  │
│   │   │   │  Security Level : CRITICAL  │   │   │  │
│   │   │   │  Access : Card+PIN+Bio      │   │   │  │
│   │   │   │  Sensors: Vault Detectors   │   │   │  │
│   │   │   │  Coverage: Command Center   │   │   │  │
│   │   │   │                             │   │   │  │
│   │   │   └─────────────────────────────┘   │   │  │
│   │   └─────────────────────────────────────┘   │  │
│   └─────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────┘
```

### 3.2 Authorization Levels

| Level | Zone | Required Credentials | Logic Gate |
|-------|------|----------------------|------------|
| **Level 1** | Zone 1 | Card Only | Single Input |
| **Level 2** | Zone 2 | Card AND PIN | AND Gate |
| **Level 3** | Zone 3 | Card AND PIN AND Biometric | AND Gate (3-input) |

### 3.3 System States

| State | Trigger Condition | Response |
|-------|-------------------|----------|
| 🟢 **SECURE** | No breach in any zone | Green LED ON |
| 🟡 **ALERT** | Single zone breach with partial auth | Yellow LED + Slow Beep |
| 🔴 **LOCKDOWN** | Core breach / Multi-zone breach / Unauthorized access | Red LED + Fast Alarm + Lock |

---

## 4. 🔧 Methodology

### 4.1 Logic System Design

The security system is built on fundamental
**Boolean logic principles**:

#### AND Gate Implementation
```
Authorization Logic:

CARD ──┐
       ├─[AND]─► ZONE 2 ACCESS
PIN  ──┘

CARD ──┐
       │
PIN  ──┼─[AND]─► ZONE 3 ACCESS
       │
BIO  ──┘
```

#### OR Gate Implementation
```
Breach Detection:

ZONE1 ──┐
        ├─[OR]─► ANY_BREACH
ZONE2 ──┘

ZONE1 ──┐
        ├─[AND]─► MULTI_BREACH → LOCKDOWN
ZONE2 ──┘
```

#### NOT Gate Implementation
```
Unauthorized Access Detection:

ANY_BREACH ────┐
               ├─[AND]─► UNAUTHORIZED_ACCESS → LOCKDOWN
NOT(CARD) ─────┘
(Inverted card signal using NOT gate)
```

### 4.2 Boolean Expressions

```
─────────────────────────────────────────────────────────
SYSTEM STATE EQUATIONS
─────────────────────────────────────────────────────────

SECURE   = Z1' · Z2' · Z3'
         (NOT Zone1 AND NOT Zone2 AND NOT Zone3)

ALERT    = (Z1 + Z2) · Z3' · AUTH'
         (Any breach in Z1 or Z2, NOT core, NOT authorized)

LOCKDOWN = Z3 + (Z1 · Z2) + (BREACH · CARD')
         (Core breach OR Multi-breach OR Unauthorized)

─────────────────────────────────────────────────────────
AUTHORIZATION EQUATIONS
─────────────────────────────────────────────────────────

MIN_AUTH  = CARD
PART_AUTH = CARD · PIN
FULL_AUTH = CARD · PIN · BIO

─────────────────────────────────────────────────────────
```

### 4.3 Truth Table

#### Zone Access Truth Table

| Card | PIN | Bio | Zone1 | Zone2 | Zone3 |
|------|-----|-----|-------|-------|-------|
| 0 | 0 | 0 | ✗ | ✗ | ✗ |
| 1 | 0 | 0 | ✓ | ✗ | ✗ |
| 1 | 1 | 0 | ✓ | ✓ | ✗ |
| 1 | 1 | 1 | ✓ | ✓ | ✓ |
| 0 | 1 | 1 | ✗ | ✗ | ✗ |

#### System State Truth Table

| Z1 | Z2 | Z3 | Auth | State |
|----|----|----|------|-------|
| 0 | 0 | 0 | X | 🟢 SECURE |
| 1 | 0 | 0 | 1 | 🟢 SECURE |
| 1 | 0 | 0 | 0 | 🟡 ALERT |
| 0 | 1 | 0 | 1 | 🟢 SECURE |
| 0 | 1 | 0 | 0 | 🟡 ALERT |
| 1 | 1 | 0 | X | 🔴 LOCKDOWN |
| 0 | 0 | 1 | X | 🔴 LOCKDOWN |
| 1 | 1 | 1 | X | 🔴 LOCKDOWN |

---

## 5. 🛠️ Implementation

### 5.1 Hardware Components

| Component | Quantity | Role |
|-----------|----------|------|
| Arduino Uno | 1 | Main processing unit |
| Push Button | 6 | Simulate sensors & auth inputs |
| Green LED | 1 | SECURE state indicator |
| Yellow LED | 1 | ALERT state indicator |
| Red LED | 1 | LOCKDOWN state indicator |
| Buzzer | 1 | Audible alarm system |
| Resistor 220Ω | 3 | LED current protection |
| Resistor 10kΩ | 6 | Button pull-down |
| Relay Module | 1 | Door lock simulation |
| Breadboard | 1 | Circuit prototyping |
| Jumper Wires | Multiple | Component connections |

### 5.2 Pin Configuration

```
ARDUINO PIN    COMPONENT           FUNCTION
───────────────────────────────────────────────────
D2          →  Push Button    →  Zone 1 Sensor
D3          →  Push Button    →  Zone 2 Sensor
D4          →  Push Button    →  Zone 3 Sensor
D5          →  Push Button    →  Card Auth Input
D6          →  Push Button    →  PIN Auth Input
D7          →  Push Button    →  Biometric Auth
D8          →  Green LED      →  SECURE Indicator
D9          →  Yellow LED     →  ALERT Indicator
D10         →  Red LED        →  LOCKDOWN Indicator
D11         →  Buzzer         →  Alarm Output
D12         →  Relay Module   →  Door Lock Control
D13         →  Status LED     →  System Status
───────────────────────────────────────────────────
```

### 5.3 Software Implementation

The Arduino code implements:

```
┌────────────────────────────────────────────┐
│           SOFTWARE MODULES                 │
├────────────────────────────────────────────┤
│  1. Sensor Reading Module                  │
│     → Polls all 6 input pins               │
│     → 100ms sampling rate                  │
├────────────────────────────────────────────┤
│  2. Boolean Logic Module                   │
│     → Implements AND/OR/NOT operations     │
│     → Evaluates authorization levels       │
│     → Determines threat conditions         │
├────────────────────────────────────────────┤
│  3. State Machine Module                   │
│     → SECURE / ALERT / LOCKDOWN states     │
│     → State transition logic               │
├────────────────────────────────────────────┤
│  4. Output Control Module                  │
│     → LED control                          │
│     → Buzzer patterns                      │
│     → Relay (lock) control                 │
├────────────────────────────────────────────┤
│  5. Logging Module                         │
│     → Serial monitor output                │
│     → Event timestamping                   │
│     → State change detection               │
└────────────────────────────────────────────┘
```

### 5.4 Simulation on Tinkercad

```
Steps to Simulate:
──────────────────────────────────────────────
1. Open tinkercad.com → Circuits → Create New
2. Add Arduino Uno to workspace
3. Add 6 Push Buttons (sensors + auth)
4. Add 3 LEDs (Green, Yellow, Red)
5. Add Buzzer
6. Add Relay Module
7. Wire all components per circuit diagram
8. Paste Arduino code into code editor
9. Click "Start Simulation"
10. Test each scenario:
    • Press Zone buttons = Breach simulation
    • Press Auth buttons = Authorization
    • Observe LED and Buzzer responses
──────────────────────────────────────────────
```

---

## 6. 🔄 System Flowchart

```
START
  │
  ▼
INITIALIZE SYSTEM
  │
  ▼
STARTUP SEQUENCE (LED test + Beep)
  │
  ▼
┌─────────────────┐
│  READ SENSORS   │◄─────────────────────────┐
└────────┬────────┘                           │
         │                                   │
         ▼                                   │
   ZONE 3 BREACHED? ──YES──► 🔴 LOCKDOWN     │
         │                       │           │
         NO                      │           │
         │                       │           │
         ▼                       │           │
   ZONE1 + ZONE2? ──YES──► 🔴 LOCKDOWN      │
         │                       │           │
         NO                      │           │
         │                       │           │
         ▼                       │           │
   ZONE1 OR ZONE2?               │           │
         │                       │           │
    YES  │  NO                   │           │
    ▼    ▼                       │           │
AUTH?  🟢 SECURE                 │           │
 │                               │           │
YES  NO                          │           │
 ▼    ▼                          │           │
🟢   🟡                          │           │
SEC  ALERT                       │           │
 │    │                          │           │
 └────┴────────────────────────► │           │
              UPDATE OUTPUTS      │           │
                   │             │           │
              LOG TO SERIAL      │           │
                   │             │           │
              WAIT 100ms ────────────────────┘
```

---

## 7. 📊 Results

### Test Scenarios and Outcomes

| Scenario | Inputs | Expected | Result |
|----------|--------|----------|--------|
| No Activity | All LOW | 🟢 SECURE | ✅ PASS |
| Zone 1 breach, no auth | Z1=1, Auth=0 | 🟡 ALERT | ✅ PASS |
| Zone 1 breach, card auth | Z1=1, Card=1 | 🟢 SECURE | ✅ PASS |
| Zone 2 breach, card+PIN | Z2=1, C+P=1 | 🟢 SECURE | ✅ PASS |
| Zone 2 breach, no auth | Z2=1, Auth=0 | 🟡 ALERT | ✅ PASS |
| Multi-zone breach | Z1+Z2=1 | 🔴 LOCKDOWN | ✅ PASS |
| Core breach | Z3=1 | 🔴 LOCKDOWN | ✅ PASS |
| Zone 3, full auth | Z3+Full=1 | 🔴 LOCKDOWN | ✅ PASS |

### System Performance

```
┌─────────────────────────────────────────┐
│         PERFORMANCE METRICS             │
├─────────────────────────────────────────┤
│  Response Time    : < 100ms             │
│  False Negatives  : 0                   │
│  False Positives  : 0                   │
│  Test Cases Passed: 8/8 (100%)          │
│  States Verified  : 3/3                 │
│  Auth Levels      : 3/3                 │
└─────────────────────────────────────────┘
```

---

## 8. 💬 Discussion

### Key Findings

- **AND Gate Logic** proved highly effective for
  multi-factor authentication, ensuring all
  credentials must be valid simultaneously

- **OR Gate Logic** successfully detected any
  single zone breach and triggered appropriate
  responses

- **NOT Gate Logic** correctly identified
  unauthorized access by inverting
  authorization signals

- **Layered Security** architecture prevented
  unauthorized access to higher security zones
  even when lower zones were breached

### Limitations

```
⚠ Push buttons only simulate real sensors
⚠ No actual biometric hardware used
⚠ Single Arduino limits scalability
⚠ No wireless/network connectivity
⚠ No data logging to external storage
```

### Future Improvements

```
🚀 Replace buttons with real sensors (PIR, RFID)
🚀 Add LCD display for status messages
🚀 Implement RFID card reader
🚀 Add fingerprint sensor for biometrics
🚀 GSM module for SMS alerts
🚀 IoT integration for remote monitoring
🚀 Camera module for video surveillance
🚀 Database for access logs
```

---

## 9. ✅ Conclusion

This project successfully demonstrated a
**three-tier security system** simulation for
a high-security infrastructure using:

- ✅ **Boolean Logic** (AND/OR/NOT gates)
- ✅ **Arduino Microcontroller** programming
- ✅ **Tinkercad** circuit simulation
- ✅ **Multi-factor authentication** logic
- ✅ **Three defined system states**
  (Secure / Alert / Lockdown)

The system achieved **100% detection rate**
with **zero false negatives**, validating the
logic flow for critical infrastructure protection.

The project provided hands-on experience in:
- Digital logic design
- Embedded systems programming
- Circuit simulation
- Security system architecture

---

## 10. 📚 References

- Boolean Algebra - Digital Design Fundamentals
- Arduino Official Documentation
  https://www.arduino.cc/reference/en/
- Tinkercad Circuits - Autodesk
  https://www.tinkercad.com/circuits
- GP106 Computer Engineering Course Notes (2021)
- University of Peradeniya Engineering Faculty

---

## 👤 Author

```
Name       : Jayawardhana H.D.S.M.
Index No   : E/19/169
Course     : GP106 - Computer Engineering
Institution: University of Peradeniya
Department : Computer Engineering
Year       : 2021
```

---

*© 2021 - University of Peradeniya |
Department of Computer Engineering*
