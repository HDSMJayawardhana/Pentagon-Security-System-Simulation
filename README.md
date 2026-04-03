# 🔐 Security System Simulation of the Pentagon

> **Course:** GP106 – Computer Engineering
> **Year:** 2021 | First Year Final Project
> **Tools:** Arduino + Tinkercad

---

## 📌 Project Overview

A **digital security system simulation** replicating the
tiered zoning protocols of a high-security infrastructure
like the Pentagon. The system uses **Boolean logic gates**
(AND/OR/NOT) to implement hierarchical access validation
with instant intrusion detection.

---

## 🏛️ System Architecture

```
┌─────────────────────────────────────────────────┐
│  ┌──────────────────────────────────────────┐   │
│  │         ZONE 1 - OUTER PERIMETER         │   │
│  │         Access: Card Only                │   │
│  │  ┌────────────────────────────────────┐  │   │
│  │  │      ZONE 2 - INNER PERIMETER      │  │   │
│  │  │      Access: Card + PIN            │  │   │
│  │  │  ┌──────────────────────────────┐  │  │   │
│  │  │  │   ZONE 3 - CORE (Pentagon)   │  │  │   │
│  │  │  │   Access: Card+PIN+Biometric  │  │  │   │
│  │  │  └──────────────────────────────┘  │  │   │
│  │  └────────────────────────────────────┘  │   │
│  └──────────────────────────────────────────┘   │
└─────────────────────────────────────────────────┘
```

---

## 🔌 Hardware Components

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno | 1 | Main Controller |
| Push Button | 6 | Sensor Simulation |
| LED Green | 1 | Secure State |
| LED Yellow | 1 | Alert State |
| LED Red | 1 | Lockdown State |
| Buzzer | 1 | Alarm Sound |
| Resistor 220Ω | 3 | LED Protection |
| Resistor 10kΩ | 6 | Button Pull-down |
| Relay Module | 1 | Door Lock |
| Breadboard | 1 | Assembly |

---

## 📐 Pin Configuration

| Arduino Pin | Component | Function |
|-------------|-----------|----------|
| D2 | Button | Zone 1 Sensor |
| D3 | Button | Zone 2 Sensor |
| D4 | Button | Zone 3 Sensor |
| D5 | Button | Card Auth |
| D6 | Button | PIN Auth |
| D7 | Button | Biometric Auth |
| D8 | Green LED | Secure Indicator |
| D9 | Yellow LED | Alert Indicator |
| D10 | Red LED | Lockdown Indicator |
| D11 | Buzzer | Alarm |
| D12 | Relay | Door Lock |
| D13 | LED | Status |

---

## 🔁 System States

| State | Condition | LED | Buzzer | Lock |
|-------|-----------|-----|--------|------|
| 🟢 SECURE | No breach detected | GREEN | OFF | CLOSED |
| 🟡 ALERT | Single zone breach | YELLOW | SLOW BEEP | CLOSED |
| 🔴 LOCKDOWN | Core/Multi breach | RED | FAST ALARM | LOCKED |

---

## ⚙️ Boolean Logic

```
LOCKDOWN  = ZONE3 + (ZONE1 · ZONE2) + (BREACH · CARD')
ALERT     = (ZONE1 + ZONE2) · ZONE3' · AUTH'
SECURE    = ZONE1' · ZONE2' · ZONE3'

FULL_AUTH = CARD · PIN · BIO   → Zone 3
PART_AUTH = CARD · PIN         → Zone 2
MIN_AUTH  = CARD               → Zone 1
```

---

## 📂 Repository Structure

```
Pentagon-Security-System/
│
├── README.md
├── docs/
│   └── project_description.md
├── arduino/
│   └── security_system.ino     ← Main Arduino Code
├── diagrams/
│   ├── circuit_diagram.md      ← Wiring diagram
│   ├── logic_diagram.md        ← Boolean logic gates
│   ├── flowchart.md            ← System flowchart
│   └── truth_table.md          ← Truth tables
└── simulation/
    └── tinkercad_instructions.md
```

---

## 🚀 How to Run

### On Tinkercad (Simulation)
```
1. Go to → tinkercad.com
2. Create New Circuit
3. Add Arduino Uno
4. Wire components as per circuit_diagram.md
5. Copy code from arduino/security_system.ino
6. Click "Start Simulation"
7. Press buttons to simulate sensor triggers
8. Watch LED states and Serial Monitor
```

### On Real Arduino
```bash
1. Open Arduino IDE
2. Load arduino/security_system.ino
3. Select Board: Arduino Uno
4. Select correct COM Port
5. Click Upload
6. Open Serial Monitor (9600 baud)
7. Press buttons to test
```

---

## 🧪 Test Cases

| Test | Zone1 | Zone2 | Zone3 | Card | PIN | Bio | Expected |
|------|-------|-------|-------|------|-----|-----|----------|
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 🟢 SECURE |
| 2 | 1 | 0 | 0 | 0 | 0 | 0 | 🟡 ALERT |
| 3 | 1 | 0 | 0 | 1 | 0 | 0 | 🟢 SECURE |
| 4 | 1 | 1 | 0 | 1 | 1 | 0 | 🔴 LOCKDOWN |
| 5 | 0 | 0 | 1 | 1 | 1 | 1 | 🔴 LOCKDOWN |
| 6 | 0 | 1 | 0 | 1 | 1 | 0 | 🟢 SECURE |

---

## 🎯 Key Features

- ✅ **Three-tier zone security** architecture
- ✅ **Multi-factor authentication** (Card + PIN + Biometric)
- ✅ **Boolean logic implementation** (AND/OR/NOT gates)
- ✅ **Instant threat detection** with zero false negatives
- ✅ **Tri-state output** (Secure / Alert / Lockdown)
- ✅ **Serial monitor logging** for all events
- ✅ **Startup self-test** sequence

---

## 📚 References

- Boolean Algebra & Logic Gates - CO221 Digital Design
- Arduino Reference Documentation
- Tinkercad Simulation Platform
- GP106 Computer Engineering Course Notes (2021)

---

## 👤 Author

**Jayawardhana H.D.S.M.**
E/19/169 | University of Peradeniya
Department of Computer Engineering
