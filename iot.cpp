#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// --- Pin Map ---
// Motor Driver (L293D)
const int IN1 = 2; const int IN2 = 3;
const int IN3 = 4; const int IN4 = 5;

// Sensors
#define TRIG 7
#define ECHO 8
#define MQ2 A0
#define BUZZER 13

// Thresholds
const int GAS_THRESHOLD = 450;
const int OBSTACLE_DIST = 20;

SoftwareSerial BT(10, 11); // RX, TX
LiquidCrystal lcd(12, 9, A1, A2, A3, A4);

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  
  BT.begin(9600);
  lcd.begin(16, 2);
  lcd.print("System Online");
  delay(1500);
}

void loop() {
  int gasLevel = analogRead(MQ2);
  long distance = getDistance();

  // SAFETY OVERRIDE: Gas Detection
  if (gasLevel > GAS_THRESHOLD) {
    handleGasLeak(gasLevel);
    return; // Exit loop to keep robot stopped
  }

  // BLUETOOTH JOYSTICK CONTROL
  if (BT.available() > 0) {
    char command = BT.read();
    executeCommand(command);
  }

  // Periodic LCD Update
  updateLCD("Safe", gasLevel);
}

// --- Movement Logic ---
void executeCommand(char cmd) {
  switch (cmd) {
    case 'F': moveForward(); break;  // Forward
    case 'B': moveBackward(); break; // Backward
    case 'L': turnLeft(); break;     // Left
    case 'R': turnRight(); break;    // Right
    case 'S': stopMotors(); break;   // Stop
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

// --- Sensor Utilities ---
long getDistance() {
  digitalWrite(TRIG, LOW); delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH) * 0.034 / 2;
}

void handleGasLeak(int level) {
  stopMotors();
  digitalWrite(BUZZER, HIGH);
  BT.println("!!! ALERT: GAS LEAK DETECTED: " + String(level) + " !!!");
  updateLCD("GAS LEAK!", level);
  delay(500); // Beep pattern
  digitalWrite(BUZZER, LOW);
}

void updateLCD(String status, int gas) {
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Stat: " + status);
  lcd.setCursor(0,1); lcd.print("Gas Level: " + String(gas));
}