#include <Encoder.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Encoder motorEnc(2,3);
OneWire oneWire(12);
DallasTemperature sensors(&oneWire);
float temp;

int fanPinOne = 9;
int fanPinTwo = 10;
int fanPinPWM = 11;

int monitorMotorPinOne = 8;
int monitorMotorPinTwo = 7;
int monitorMotorPinPWM = 6;

int endstopWidePosition = 150; // the value need to be experimentally defined
/*  
 *  We have two plywood gears with 10 and 50 teeth (1:5 reduction ratio).
 *  We need to rotate monitor wich attached to 50-tooth gear on 90 degrees,
 *  so it means that we need to rotate small gear on 450 degrees or 1.25 turn.
 *  Gearmotor has 11 impulses per motor shaft turn and 1:200 reduction ratio.
 *  So we have 2200 impulses per gear-end shaft turn and 2750 impulses at all.
 *  Something about 30 impulses per degree. Long monitor size is about 530 mm.
 *  530 * tan (1/30 deg) = 0.3 mm or 1.5 mm per 5 impulses (or half from center)
 *  Let use 5 impulses as rotation quantity.
 */
int wideTallPosition = 2750;

int CWendStopPin = 4; // CW rotation endstop button pin
int CCWendStopPin = 5; // CCW rotation endstop button pin

int CWendStopState; // CW rotation endstop state
int CCWendStopState; // CCW rotation endstop state

int direction = 1; // rotation direction flag: 1 means CW; -1  means CCW

int oldPosition = -999; // encoder lowest position
int newPosition; // encoder current position

void setup() {
  Serial.begin(9600); // Serial port initialisation
  sensors.begin(); // One-wire initialisation
  
  pinMode(fanPinOne, OUTPUT);
  pinMode(fanPinTwo, OUTPUT);
  pinMode(fanPinPWM, OUTPUT);
  
  pinMode(monitorMotorPinOne, OUTPUT);
  pinMode(monitorMotorPinTwo, OUTPUT);
  pinMode(monitorMotorPinPWM, OUTPUT);

  pinMode(CWendStopPin, INPUT);
  pinMode(CCWendStopPin, INPUT);
  
  rotate(direction, 5000, 125); /* 5000 is a big number because we need to
  rotate until CW rotation endstop turns 1 to define starting position */

  direction = direction * (-1);
  rotate(direction, endstopWidePosition, 255);
}

void loop() {
  if (Serial.available()) {
    if (Serial.read() == "o") {
      rotate(direction, wideTallPosition, 255);
      Serial.print("Rotation comlete!");
      Serial.print(newPosition);
      Serial.println();
    }
    direction = direction * (-1);
  }

  sensors.requestTemperatures();  // Send the command to get temperature
  temp = sensors.getTempCByIndex(0); // Read temperature from the first sensor
  digitalWrite(fanPinOne, LOW);
  digitalWrite(fanPinTwo, HIGH);
  /* If temperature is 18 or low the fan is off. 
   * While temperature rising to 40 degrees PWM rising to 255
   */
  analogWrite(fanPinPWM, constrain(map(temp, 18, 40, 0, 255) ,0, 255));
}

void rotate(int dir, int steps, int PWM) {
  int startPosition;
  int stopPin;
  long timer;
  
  newPosition= motorEnc.read();
  startPosition = newPosition;
  if (dir == 1) {
    // CW rotation
    digitalWrite(monitorMotorPinOne, LOW);
    digitalWrite(monitorMotorPinTwo, HIGH);
    stopPin = CWendStopPin;
  } else {
    // CCW rotation
    digitalWrite(monitorMotorPinOne, HIGH);
    digitalWrite(monitorMotorPinTwo, LOW);
    stopPin = CCWendStopPin;
  }
  timer = millis();
  while ((newPosition - startPosition < dir * steps) && (digitalRead(stopPin) != HIGH)) {
    analogWrite(monitorMotorPinPWM, PWM);
    newPosition= motorEnc.read();
    if (newPosition != oldPosition) {
      oldPosition = newPosition;
    }
  }
  analogWrite(monitorMotorPinPWM, 0);
  Serial.print("Cutoff position = ");
  Serial.print(newPosition);
  Serial.print(" working time = ");
  Serial.print(millis() - timer);
  delay(1000);
  newPosition= motorEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
  }
  Serial.print(", slowdown position = ");
  Serial.print(newPosition);
  Serial.println();
}
