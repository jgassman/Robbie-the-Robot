#include <ThatcherRobotFinal.h>

Robot Robbie;

void setup() {

}

void loop() {
  Robbie.speedUp();
  Robbie.forward(2000);
  Robbie.slowDown();
  Robbie.stopRobot();
  delay(10000);
}
