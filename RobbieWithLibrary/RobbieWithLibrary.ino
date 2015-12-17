#include <ThatcherRobotFinal.h>

Robot Robbie;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Robbie.speedUp();
  Robbie.forward(2000);
  Robbie.slowDown();
  Robbie.stopRobot();
  delay(10000);
}
