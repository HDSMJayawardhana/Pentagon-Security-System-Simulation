// ============================================================
// Pentagon Security System Simulation
// Course  : GP106 - Computer Engineering
// Year    : 2021 (First Year Final Project)
// Tools   : Arduino + Tinkercad
// ============================================================
// Security Zones:
//   Zone 1 - Outer Perimeter (Low Security)
//   Zone 2 - Inner Perimeter (Medium Security)
//   Zone 3 - Core Zone      (High Security)
//
// States:
//   SECURE   - All zones clear
//   ALERT    - Single zone breach
//   LOCKDOWN - Multiple zone breach / Core breach
// ============================================================

// ──────────────────────────────────────────────
// PIN DEFINITIONS
// ──────────────────────────────────────────────

// Input Sensors (Push buttons simulate sensors)
const int SENSOR_ZONE1 = 2;   // Outer perimeter sensor
const int SENSOR_ZONE2 = 3;   // Inner perimeter sensor
const int SENSOR_ZONE3 = 4;   // Core zone sensor
const int AUTH_CARD    = 5;   // Authorization card input
const int AUTH_PIN     = 6;   // PIN authorization input
const int AUTH_BIO     = 7;   // Biometric authorization input

// Output Actuators
const int LED_GREEN    = 8;   // SECURE state indicator
const int LED_YELLOW   = 9;   // ALERT state indicator
const int LED_RED      = 10;  // LOCKDOWN state indicator
const int BUZZER       = 11;  // Alarm buzzer
const int RELAY_LOCK   = 12;  // Door lock relay
const int LCD_SIM      = 13;  // Status LED (LCD simulation)

// ──────────────────────────────────────────────
// CONSTANTS
// ──────────────────────────────────────────────

// System States
#define STATE_SECURE   0
#define STATE_ALERT    1
#define STATE_LOCKDOWN 2

// Access Levels
#define ACCESS_DENIED  0
#define ACCESS_GRANTED 1

// ──────────────────────────────────────────────
// GLOBAL VARIABLES
// ──────────────────────────────────────────────

int systemState    = STATE_SECURE;
int prevState      = STATE_SECURE;
int alertCount     = 0;
unsigned long lastAlertTime = 0;
const long ALERT_TIMEOUT    = 10000; // 10 seconds

// ──────────────────────────────────────────────
// SETUP
// ──────────────────────────────────────────────

void setup() {
  Serial.begin(9600);

  // Configure sensor inputs with pull-up resistors
  pinMode(SENSOR_ZONE1, INPUT_PULLUP);
  pinMode(SENSOR_ZONE2, INPUT_PULLUP);
  pinMode(SENSOR_ZONE3, INPUT_PULLUP);
  pinMode(AUTH_CARD,    INPUT_PULLUP);
  pinMode(AUTH_PIN,     INPUT_PULLUP);
  pinMode(AUTH_BIO,     INPUT_PULLUP);

  // Configure output pins
  pinMode(LED_GREEN,   OUTPUT);
  pinMode(LED_YELLOW,  OUTPUT);
  pinMode(LED_RED,     OUTPUT);
  pinMode(BUZZER,      OUTPUT);
  pinMode(RELAY_LOCK,  OUTPUT);
  pinMode(LCD_SIM,     OUTPUT);

  // System startup sequence
  startupSequence();

  Serial.println("==========================================");
  Serial.println("  PENTAGON SECURITY SYSTEM - ONLINE      ");
  Serial.println("==========================================");
  Serial.println("  Status: SECURE | All Zones Clear       ");
  Serial.println("==========================================");
}

// ──────────────────────────────────────────────
// MAIN LOOP
// ──────────────────────────────────────────────

void loop() {

  // Read all sensor inputs
  // LOW = triggered (active LOW with pull-up)
  bool zone1 = !digitalRead(SENSOR_ZONE1);
  bool zone2 = !digitalRead(SENSOR_ZONE2);
  bool zone3 = !digitalRead(SENSOR_ZONE3);
  bool card  = !digitalRead(AUTH_CARD);
  bool pin   = !digitalRead(AUTH_PIN);
  bool bio   = !digitalRead(AUTH_BIO);

  // ── BOOLEAN LOGIC ──────────────────────────
  //
  // Authorization Logic (AND gate):
  //   FULL_ACCESS  = card AND pin AND bio
  //   PART_ACCESS  = card AND pin (without bio)
  //   MIN_ACCESS   = card only
  //
  // Threat Detection Logic:
  //   LOCKDOWN = zone3
  //            OR (zone1 AND zone2)
  //            OR (breach AND NOT authorized)
  //
  //   ALERT    = (zone1 OR zone2) AND NOT zone3
  //
  //   SECURE   = NOT zone1 AND NOT zone2 AND NOT zone3
  //
  // ───────────────────────────────────────────

  // Authorization levels using AND logic
  bool fullAccess = card && pin && bio;   // AND gate - all 3
  bool partAccess = card && pin;           // AND gate - 2 factors
  bool minAccess  = card;                  // Single factor

  // Breach detection using OR/AND/NOT logic
  bool anyBreach      = zone1 || zone2 || zone3;   // OR gate
  bool multiBrech     = zone1 && zone2;             // AND gate
  bool coreBreached   = zone3;                      // Direct
  bool unauthorizedAccess = anyBreach && !minAccess; // AND + NOT

  // Determine system state
  if (coreBreached || multiBrech || unauthorizedAccess) {
    systemState = STATE_LOCKDOWN;
  }
  else if (zone1 || zone2) {
    if (partAccess) {
      systemState = STATE_SECURE;  // Authorized access
    } else {
      systemState = STATE_ALERT;
    }
  }
  else {
    systemState = STATE_SECURE;
  }

  // ── UPDATE OUTPUTS ─────────────────────────
  updateOutputs(systemState);

  // ── SERIAL MONITOR LOG ─────────────────────
  if (systemState != prevState) {
    logStateChange(zone1, zone2, zone3,
                   card, pin, bio,
                   fullAccess, systemState);
    prevState = systemState;
  }

  delay(100); // 100ms polling rate
}

// ──────────────────────────────────────────────
// FUNCTION: Update LED/Buzzer/Lock Outputs
// ──────────────────────────────────────────────

void updateOutputs(int state) {

  // Reset all outputs first
  digitalWrite(LED_GREEN,  LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED,    LOW);
  noTone(BUZZER);

  switch (state) {

    case STATE_SECURE:
      // GREEN LED ON - System Secure
      digitalWrite(LED_GREEN,  HIGH);
      digitalWrite(RELAY_LOCK, LOW);   // Lock engaged
      digitalWrite(LCD_SIM,    LOW);
      break;

    case STATE_ALERT:
      // YELLOW LED ON + Slow Beep
      digitalWrite(LED_YELLOW, HIGH);
      digitalWrite(RELAY_LOCK, LOW);   // Lock remains
      tone(BUZZER, 1000);              // 1kHz alert tone
      delay(200);
      noTone(BUZZER);
      delay(300);
      break;

    case STATE_LOCKDOWN:
      // RED LED ON + Fast Alarm + Unlock blocked
      digitalWrite(LED_RED,    HIGH);
      digitalWrite(RELAY_LOCK, HIGH);  // Lock override
      tone(BUZZER, 2000);              // 2kHz alarm
      delay(100);
      noTone(BUZZER);
      delay(100);
      tone(BUZZER, 1500);
      delay(100);
      noTone(BUZZER);
      delay(100);
      break;
  }
}

// ──────────────────────────────────────────────
// FUNCTION: Log State to Serial Monitor
// ──────────────────────────────────────────────

void logStateChange(bool z1, bool z2, bool z3,
                    bool card, bool pin, bool bio,
                    bool auth, int state) {

  Serial.println("------------------------------------------");
  Serial.println("  SECURITY EVENT DETECTED                 ");
  Serial.println("------------------------------------------");

  // Zone Status
  Serial.print("  Zone 1 (Outer)  : ");
  Serial.println(z1 ? "⚠ BREACHED" : "✓ CLEAR");

  Serial.print("  Zone 2 (Inner)  : ");
  Serial.println(z2 ? "⚠ BREACHED" : "✓ CLEAR");

  Serial.print("  Zone 3 (Core)   : ");
  Serial.println(z3 ? "⚠ BREACHED" : "✓ CLEAR");

  // Authorization Status
  Serial.println("  ── Authorization ──────────────────");
  Serial.print("  Card Auth       : ");
  Serial.println(card ? "✓ VALID" : "✗ INVALID");

  Serial.print("  PIN Auth        : ");
  Serial.println(pin  ? "✓ VALID" : "✗ INVALID");

  Serial.print("  Biometric Auth  : ");
  Serial.println(bio  ? "✓ VALID" : "✗ INVALID");

  Serial.print("  Full Access     : ");
  Serial.println(auth ? "✓ GRANTED" : "✗ DENIED");

  // System State
  Serial.println("  ── System State ───────────────────");
  Serial.print("  STATUS          : ");

  switch (state) {
    case STATE_SECURE:
      Serial.println("🟢 SECURE");
      break;
    case STATE_ALERT:
      Serial.println("🟡 ALERT - Investigating...");
      break;
    case STATE_LOCKDOWN:
      Serial.println("🔴 LOCKDOWN - All Access Denied!");
      break;
  }

  Serial.println("------------------------------------------");
}

// ──────────────────────────────────────────────
// FUNCTION: Startup LED Sequence
// ──────────────────────────────────────────────

void startupSequence() {
  Serial.println("  System Initializing...");

  // Blink all LEDs 3 times
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_GREEN,  HIGH);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED,    HIGH);
    tone(BUZZER, 1500);
    delay(200);

    digitalWrite(LED_GREEN,  LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED,    LOW);
    noTone(BUZZER);
    delay(200);
  }

  // Green ON = System Ready
  digitalWrite(LED_GREEN, HIGH);
  tone(BUZZER, 2000);
  delay(500);
  noTone(BUZZER);

  Serial.println("  System Ready!");
}

// ──────────────────────────────────────────────
// FUNCTION: Access Control Check
// Returns: ACCESS_GRANTED or ACCESS_DENIED
// ──────────────────────────────────────────────

int checkAccess(int zone, bool card, bool pin, bool bio) {

  // Zone 1: Only card needed (OR logic)
  if (zone == 1) {
    return (card) ? ACCESS_GRANTED : ACCESS_DENIED;
  }

  // Zone 2: Card AND PIN needed (AND logic)
  if (zone == 2) {
    return (card && pin) ? ACCESS_GRANTED : ACCESS_DENIED;
  }

  // Zone 3: Card AND PIN AND Biometric (AND gate - all 3)
  if (zone == 3) {
    return (card && pin && bio) ? ACCESS_GRANTED : ACCESS_DENIED;
  }

  return ACCESS_DENIED;
}
