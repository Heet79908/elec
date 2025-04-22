#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 7;
const int echoPin = 6;
const int buzzer = 5;

// Green LEDs on pins 8 and 9
const int greenLeds[] = {8, 9};
// White LEDs on pins 10 and 11
const int whiteLeds[] = {10, 11};
// Red LEDs on pins 12 and 13
const int redLeds[] = {12, 13};

// Motor 1 control pins
const int motor1IN1 = 3;
const int motor1IN2 = 4;

// Motor 2 control pins
const int motor2IN1 = 2;
const int motor2IN2 = A0;

long duration;
int distance;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  for (int i = 0; i < 2; i++) {
    pinMode(greenLeds[i], OUTPUT);
    pinMode(redLeds[i], OUTPUT);
    pinMode(whiteLeds[i], OUTPUT);
  }

  pinMode(motor1IN1, OUTPUT);
  pinMode(motor1IN2, OUTPUT);
  pinMode(motor2IN1, OUTPUT);
  pinMode(motor2IN2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time and convert to distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);

  String status = "";

  if (distance <= 0 || distance > 60) {
    for (int i = 0; i < 2; i++) {
      digitalWrite(greenLeds[i], LOW);
      digitalWrite(redLeds[i], LOW);
      digitalWrite(whiteLeds[i], LOW);
    }
    digitalWrite(buzzer, LOW);
    // Run both motors
    digitalWrite(motor1IN1, HIGH);
    digitalWrite(motor1IN2, LOW);
    digitalWrite(motor2IN1, HIGH);
    digitalWrite(motor2IN2, LOW);
    status = "Clear";
  } 
  else if (distance <= 10) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenLeds[0], LOW);
    digitalWrite(greenLeds[1], LOW);
    digitalWrite(redLeds[0], HIGH);
    digitalWrite(redLeds[1], HIGH);
    digitalWrite(whiteLeds[0], LOW);
    digitalWrite(whiteLeds[1], LOW);
    // Stop both motors
    digitalWrite(motor1IN1, LOW);
    digitalWrite(motor1IN2, LOW);
    digitalWrite(motor2IN1, LOW);
    digitalWrite(motor2IN2, LOW);
    status = "Stop";
  } 
  else if (distance <= 20) {
    digitalWrite(buzzer, LOW);
    digitalWrite(greenLeds[0], LOW);
    digitalWrite(greenLeds[1], LOW);
    digitalWrite(redLeds[0], HIGH);
    digitalWrite(redLeds[1], LOW);
    digitalWrite(whiteLeds[0], LOW);
    digitalWrite(whiteLeds[1], LOW);
    // Run both motors
    digitalWrite(motor1IN1, HIGH);
    digitalWrite(motor1IN2, LOW);
    digitalWrite(motor2IN1, HIGH);
    digitalWrite(motor2IN2, LOW);
    status = "Warning";
  } 
  else if (distance <= 30) {
    digitalWrite(buzzer, LOW);
    digitalWrite(greenLeds[0], LOW);
    digitalWrite(greenLeds[1], LOW);
    digitalWrite(redLeds[0], LOW);
    digitalWrite(redLeds[1], LOW);
    digitalWrite(whiteLeds[0], HIGH);
    digitalWrite(whiteLeds[1], HIGH);
    // Run both motors
    digitalWrite(motor1IN1, HIGH);
    digitalWrite(motor1IN2, LOW);
    digitalWrite(motor2IN1, HIGH);
    digitalWrite(motor2IN2, LOW);
    status = "OK";
  } 
  else if (distance <= 40) {
    digitalWrite(buzzer, LOW);
    digitalWrite(greenLeds[0], LOW);
    digitalWrite(greenLeds[1], LOW);
    digitalWrite(redLeds[0], LOW);
    digitalWrite(redLeds[1], LOW);
    digitalWrite(whiteLeds[0], HIGH);
    digitalWrite(whiteLeds[1], LOW);
    // Run both motors
    digitalWrite(motor1IN1, HIGH);
    digitalWrite(motor1IN2, LOW);
    digitalWrite(motor2IN1, HIGH);
    digitalWrite(motor2IN2, LOW);
    status = "OK";
  } 
  else if (distance <= 50) {
    digitalWrite(buzzer, LOW);
    digitalWrite(greenLeds[0], HIGH);
    digitalWrite(greenLeds[1], HIGH);
    digitalWrite(redLeds[0], LOW);
    digitalWrite(redLeds[1], LOW);
    digitalWrite(whiteLeds[0], LOW);
    digitalWrite(whiteLeds[1], LOW);
    // Run both motors
    digitalWrite(motor1IN1, HIGH);
    digitalWrite(motor1IN2, LOW);
    digitalWrite(motor2IN1, HIGH);
    digitalWrite(motor2IN2, LOW);
    status = "OK";
  } 
  else if (distance <= 60) {
    digitalWrite(buzzer, LOW);
    digitalWrite(greenLeds[0], HIGH);
    digitalWrite(greenLeds[1], LOW);
    digitalWrite(redLeds[0], LOW);
    digitalWrite(redLeds[1], LOW);
    digitalWrite(whiteLeds[0], LOW);
    digitalWrite(whiteLeds[1], LOW);
    // Run both motors
    digitalWrite(motor1IN1, HIGH);
    digitalWrite(motor1IN2, LOW);
    digitalWrite(motor2IN1, HIGH);
    digitalWrite(motor2IN2, LOW);
    status = "OK";
  }

  lcd.setCursor(0, 1);
  if (distance > 0 && distance <= 10) {
    lcd.print("WARNING!!");
  } else {
    lcd.print("Status : OK");
  }

  delay(500);
}
