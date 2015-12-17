#include <Usb.h>
#include <Wire.h>
#include <AndroidAccessory.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

#define ARRAY_SIZE 12

#define rMotor 13
#define lMotor 12

#define frontSensor A1
#define backSensor A2
#define rightSensor A3
#define leftSensor A4

int frontReading[3] = {0, 0, 0};
int backReading[3] = {0, 0, 0};
int rightReading[3] = {0, 0, 0};
int leftReading[3] = {0, 0, 0,};
int frontRead = 0;
int backRead = 0;
int leftRead = 0;
int rightRead = 0;

char currentMotion = ' ';
int currentSpeed = 0;

static int SLOW_THRESHOLD = 300;
static int STOP_THRESHOLD = 200;

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

AndroidAccessory acc("ASUS","TF101","Tablet","Version","URI","Serial");

char hello[ARRAY_SIZE] = {'h','e','l','l','o',' ','t','o','o','t','s','!'};
int readings[3] = {0, 0, 0};

void setup() {
  delay(5000);
  digitalWrite(rMotor, HIGH); //send initializing pulses to the motor controllers
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(rMotor, LOW);
  digitalWrite(lMotor, LOW);
  delay(20);
  Serial.begin(115200);
  acc.powerOn();
}

void loop() {
  if(acc.isConnected()){
    for(int x = 0; x < ARRAY_SIZE; x++){
      Serial.print(hello[x]);
      delay(250);
    }
    Serial.println();
    delay(250);
  }

  currentMotion = 'F';
  speedUp();
  forward();
  delay(3000);
  stopMotion();
}

void speedUp() {
  if(currentMotion == 'F'){
    for(float i = currentSpeed; i <= currentSpeed + 250; i += 0.1){
      digitalWrite(rMotor, HIGH);
      digitalWrite(rMotor, HIGH);
      delayMicroseconds(i);
      digitalWrite(lMotor, LOW);
      digitalWrite(lMotor, LOW);
      delayMicroseconds(5250);
      delayMicroseconds(150);
      currentSpeed = i;
    }
  }
  else if(currentMotion == 'B'){
    for(float j = currentSpeed; j <= currentSpeed - 250; j -= 0.1){
      digitalWrite(rMotor, HIGH);
      digitalWrite(rMotor, HIGH);
      delayMicroseconds(j);
      digitalWrite(lMotor, LOW);
      digitalWrite(lMotor, LOW);
      delayMicroseconds(5250);
      delayMicroseconds(150);
      currentSpeed = j;
    }
  }
}

void forward(){
  currentMotion = 'F';
  digitalWrite(rMotor, HIGH);
  digitalWrite(rMotor, HIGH);
  delayMicroseconds(1750);
  digitalWrite(lMotor, LOW);
  digitalWrite(lMotor, LOW);
  delayMicroseconds(5250);
}

void backward() {
  currentMotion = 'B';
  digitalWrite(rMotor, HIGH);
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1250);
  digitalWrite(rMotor, LOW);
  digitalWrite(lMotor, LOW);
  delayMicroseconds(5250);
}

void stopMotion(){
  if(currentMotion == 'B'){
    for(int j = currentSpeed; j <= 1500; j++){
      digitalWrite(rMotor, HIGH);
      digitalWrite(lMotor, HIGH);
      delayMicroseconds(j);
      digitalWrite(rMotor, LOW);
      digitalWrite(lMotor, LOW);
      delayMicroseconds(5250);
      delayMicroseconds(150);
    }
  }
  else if(currentMotion == 'F'){
    for(int i = currentSpeed; i >= 1500; i--){
      digitalWrite(rMotor, HIGH);
      digitalWrite(lMotor, HIGH);
      delayMicroseconds(i);
      digitalWrite(rMotor, LOW);
      digitalWrite(lMotor, LOW);
      delayMicroseconds(5250);
      delayMicroseconds(150);
    }
  }
  currentMotion = 'S';
}

void right() {
  for(int i = 1500; i <= 1750; i++){
    digitalWrite(lMotor, HIGH);
    delayMicroseconds(i);
    digitalWrite(lMotor, LOW);
    digitalWrite(rMotor, HIGH);
    delayMicroseconds(1500);
    digitalWrite(rMotor, LOW);
    delayMicroseconds(5250);
  }
  delay(3000);
}

void stayStopped(){
  currentMotion = 'S';
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(lMotor, LOW);
  digitalWrite(rMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(rMotor, LOW);
  delayMicroseconds(5250);
}

void left(){
  for(int i = 1500; i<= 1750; i++){
    digitalWrite(rMotor, HIGH);
    delayMicroseconds(i);
    digitalWrite(rMotor, LOW);
    digitalWrite(lMotor, HIGH);
    delayMicroseconds(1500);
    digitalWrite(lMotor, LOW);
    delayMicroseconds(5250);
  }
  delay(3000);
}

void sensors(){
  frontReading[0] = frontReading[1];
  frontReading[1] = frontReading[2];
  frontReading[2] = analogRead(frontSensor);
  frontRead = (frontReading[0] + frontReading[1] + frontReading[2])/3;

  backReading[0] = backReading[1];
  backReading[1] = backReading[2];
  backReading[2] = analogRead(backSensor);

  rightReading[0] = rightReading[1];
  rightReading[1] = rightReading[2];
  rightReading[2] = analogRead(rightSensor);

  leftReading[0] = leftReading[1];
  leftReading[1] = leftReading[2];
  leftReading[2] = analogRead(leftSensor);
}

int getFloor(){
  sensors_event_t event;
  bmp.getEvent(&event);
  int altitude;

  if (event.pressure){ //if the sensor read correctly
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:    "); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure));
    altitude = bmp.pressureToAltitude(seaLevelPressure, event.pressure);
    /**< The calculated altitude from the pressure sensor */
  }
  //TODO: CREATE LOOKUP TABLE AND RETURN THE FLOOR
}
