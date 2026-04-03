# Pentagon Security System - Truth Tables

## Authorization Truth Table (AND Logic)

| Card | PIN | Biometric | Zone 1 Access | Zone 2 Access | Zone 3 Access |
|------|-----|-----------|---------------|---------------|---------------|
| 0    | 0   | 0         | ✗ DENIED      | ✗ DENIED      | ✗ DENIED      |
| 1    | 0   | 0         | ✓ GRANTED     | ✗ DENIED      | ✗ DENIED      |
| 1    | 1   | 0         | ✓ GRANTED     | ✓ GRANTED     | ✗ DENIED      |
| 1    | 1   | 1         | ✓ GRANTED     | ✓ GRANTED     | ✓ GRANTED     |
| 0    | 1   | 1         | ✗ DENIED      | ✗ DENIED      | ✗ DENIED      |
| 0    | 0   | 1         | ✗ DENIED      | ✗ DENIED      | ✗ DENIED      |

## Threat Detection Truth Table

| Zone1 | Zone2 | Zone3 | Auth | System State |
|-------|-------|-------|------|--------------|
| 0     | 0     | 0     | X    | 🟢 SECURE   |
| 1     | 0     | 0     | 1    | 🟢 SECURE   |
| 1     | 0     | 0     | 0    | 🟡 ALERT    |
| 0     | 1     | 0     | 1    | 🟢 SECURE   |
| 0     | 1     | 0     | 0    | 🟡 ALERT    |
| 1     | 1     | 0     | X    | 🔴 LOCKDOWN |
| 0     | 0     | 1     | X    | 🔴 LOCKDOWN |
| 1     | 1     | 1     | X    | 🔴 LOCKDOWN |

## Output Truth Table

| State    | Green LED | Yellow LED | Red LED | Buzzer | Lock  |
|----------|-----------|------------|---------|--------|-------|
| SECURE   | ON        | OFF        | OFF     | OFF    | CLOSE |
| ALERT    | OFF       | ON         | OFF     | SLOW   | CLOSE |
| LOCKDOWN | OFF       | OFF        | ON      | FAST   | LOCK  |

## Boolean Expressions

```
LOCKDOWN  = ZONE3 + (ZONE1 · ZONE2) + (ANY_BREACH · CARD')
ALERT     = (ZONE1 + ZONE2) · ZONE3' · AUTH'
SECURE    = ZONE1' · ZONE2' · ZONE3'
FULL_AUTH = CARD · PIN · BIO
PART_AUTH = CARD · PIN
MIN_AUTH  = CARD
```
