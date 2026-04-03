# Pentagon Security System - Logic Diagram

## Boolean Logic Implementation

### Authorization Logic

```
CARD ──────┐
           ├── AND ──► FULL_ACCESS (Zone 3)
PIN  ──────┤
           │
BIO  ──────┘

CARD ──────┐
           ├── AND ──► PART_ACCESS (Zone 2)
PIN  ──────┘

CARD ──────────────► MIN_ACCESS  (Zone 1)
```

### Threat Detection Logic

```
ZONE1 ─────┐
           ├── OR ───────────────────────┐
ZONE2 ─────┘                            │
                                        ├── ► ANY_BREACH
ZONE3 ──────────────────────────────────┘

ZONE1 ─────┐
           ├── AND ──► MULTI_BREACH
ZONE2 ─────┘

ZONE3 ──────────────► CORE_BREACH

ANY_BREACH ────┐
               ├── AND ──► UNAUTHORIZED_ACCESS
NOT(CARD) ─────┘
```

### State Machine Logic

```
CORE_BREACH    ─────┐
                    │
MULTI_BREACH   ─────┼── OR ──► LOCKDOWN STATE 🔴
                    │
UNAUTHORIZED   ─────┘

(ZONE1 OR ZONE2)
AND NOT(ZONE3)
AND NOT(AUTH)  ──────────────► ALERT STATE 🟡

NOT(ZONE1)
AND NOT(ZONE2)
AND NOT(ZONE3) ──────────────► SECURE STATE 🟢
```

## State Transition Diagram

```
              ┌─────────────────────────────────────┐
              │                                     │
              ▼                                     │
        ┌──────────┐  Single Zone    ┌──────────┐   │
        │  SECURE  │ ──── Breach ───►│  ALERT   │   │
        │  🟢 LED  │                 │  🟡 LED  │   │
        └──────────┘                └──────────┘   │
              ▲                          │          │
              │                    Multi/Core       │
              │                      Breach         │
              │                          │          │
              │                          ▼          │
              │                    ┌──────────┐     │
              │     Auth Reset     │ LOCKDOWN │     │
              └────────────────────│  🔴 LED  │─────┘
                                   └──────────┘
```
