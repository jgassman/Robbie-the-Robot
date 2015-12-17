/*
  Robot.cpp - Library for controlling a robot.
  Created by Jessica Thatcher, November 9, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "ThatcherRobotFinal.h"

Robot::Robot(){
	#define rMotor 13 /** The variable to control the right motor controller */
	#define lMotor 12 /** The variable to control the left motor controller */

	#define fSensor A1     /** \def The pin connected to the front sensor */
	#define bSensor A2     /** \def The pin connected to the back sensor */

	int fValue;  /** A variable to hold the reading from the front sensor */
	int bValue;   /** A variable to hold the reading from the back sensor */

	const static int PROX_THRESHOLD = 150;  /** The sensor value to signal the robot should stop */
	Adafruit_BMP085_Unified bmp;	/** The altitude sensor */
	
	pinMode(rMotor, OUTPUT);
	pinMode(lMotor, OUTPUT);
	pinMode(fSensor, INPUT);
	pinMode(bSensor, INPUT);
	delay(1000);
	digitalWrite(rMotor, HIGH);
	digitalWrite(lMotor, HIGH);
	delayMicroseconds(1500);
	digitalWrite(rMotor, LOW);
	digitalWrite(lMotor, LOW);
	delay(5250);
	Serial.begin(9600);
	randomSeed(analogRead(0));
}

/** \brief Increases the robot's speed.
 * 
 * This function sends pulses to each motor controller so that the 
 * robot gradually speeds up to top speed.
 */
void Robot::speedUp() {
  for(int i = 1500; i <= 1750; i+=10){
    if(isStuck()){
		break;
	}
    
    digitalWrite(rMotor, HIGH);
    digitalWrite(lMotor, HIGH); 
    delayMicroseconds(i);
    digitalWrite(rMotor, LOW);
    digitalWrite(lMotor, LOW);
    delayMicroseconds(5250);
  }
}

/** \brief Causes the robot to move forward.
 * 
 * This function sends pulses of equal width to the motors so that the
 * robot moves forward at a constant speed.
 *
 * \param[in] goTime The time to go forward in milliseconds.
 */
void Robot::forward(int goTime){
  int goneTime = 0;
  while(goneTime < goTime){
	if(Robot::isStuck()){
		break;
	}

    int curTime = millis();
    digitalWrite(rMotor, HIGH);
    delayMicroseconds(1750);
    digitalWrite(rMotor,LOW);
    digitalWrite(lMotor, HIGH);
    delayMicroseconds(1750);
    digitalWrite(lMotor, LOW);
    delayMicroseconds(5250);
    goneTime += millis() - curTime;
  }
}

/** \brief Causes the robot to move backward.
 *  
 * This function sends pulses of equal width to both motor 
 * controllers so that the robot will move backward at a
 * constant speed.
 * 
 * \param[in] goTime The time to go forward in milliseconds.
 */
void Robot::backward(int goTime) {
	int goneTime = 0;
	while(goneTime < goTime){
		if(isStuck()){
			break;
		}
		int curTime = millis();
		digitalWrite(rMotor, HIGH);
		digitalWrite(lMotor, HIGH);
		delayMicroseconds(1250);
		digitalWrite(rMotor, LOW);
		digitalWrite(lMotor, LOW);
		delayMicroseconds(5250);
		goneTime += millis() - curTime;
	}
}

/** \brief Accelerates the robot backwards.
 * 
 * This function sends pulses of decreasing width to the motor
 * controllers so that the robot speeds up in the backwards direction.
 */
void Robot::speedBack(){
  for(int i = 1500; i >= 1250; i++){
	if(isStuck()){
      break;
    }
    digitalWrite(rMotor, HIGH);
    digitalWrite(rMotor, HIGH);
    delayMicroseconds(i);
    digitalWrite(lMotor, LOW);
    digitalWrite(lMotor, LOW);
    delayMicroseconds(5250);
  }
}

/** \brief Stops the robot.
 * 
 * This function sends pulses of equal width to both motors
 * with the correct pulse width to cause the motors to stop
 * moving.
 */
void Robot::stopRobot(){
  digitalWrite(rMotor,HIGH);
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(rMotor, LOW);
  digitalWrite(lMotor, LOW);
  delayMicroseconds(5250);  
}

/** \brief Causes the robot to turn right.
 *  
 * This function stops the right motor controller and sets
 * left motor controller to forward so that the robot 
 * turns left.
 */
void Robot::right() {
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1750);
  digitalWrite(lMotor,LOW);
  digitalWrite(rMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(rMotor, LOW);
  delayMicroseconds(5250);
  delay(1100);
  stopRobot();
}

/** \brief Causes the robot to turn left.
 *  
 * This function stops the left motor controller and sets the
 * right motor controller to forward so that the robot 
 * turns left.
 */
void Robot::left(){
  digitalWrite(rMotor, HIGH);
  delayMicroseconds(1750);
  digitalWrite(rMotor,LOW);
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(lMotor, LOW);
  delayMicroseconds(5250);
  delay(1250);
  stopRobot();
}

/** \brief Determines if the robot is stuck.
 * 
 * This function reads the value from the front sensor and stops
 * the robot while there is something in front of the robot. If the 
 * robot is stopped for more than 5 seconds, it returns the value 
 * true to signal that the robot is, indeed, stuck. If not, it returns
 * false to signal that everything is awesome!
 * 
 * \return Whether or not the robot is stuck.
 */
bool Robot::isStuck(){
    fValue = analogRead(fSensor);
    int whileTime = millis();
    //While something is close to the front sensor
    while(fValue > PROX_THRESHOLD){
      //Stop moving
      stopRobot();
      fValue = analogRead(fSensor);
      //If Robbie is stuck for more than 5 seconds
      if(millis() - whileTime > 5000){
        //Give up on this motion
        return true;
      }
    }
    return false;
}


/** \brief Simulates random motion.
 * 
 * This function generates a random number between 0 and 100. If the
 * number ends in 5, the robot turns left. If it ends in 0, the robot
 * turns right. Otherwise, the robot goes forward.
 */
void Robot::wander(){
  int randNum = random(101);
  if(randNum % 5 == 0){
    if(randNum % 10 == 0){
      right();
    }
    else{
      left();
    }
  }
  else{
    forward(1000);
  }
}

/** \brief Makes the robot travel from room 214 to room 215.
 * 
 * This function calls the forward, left, right, and speedUp functions
 * in the correct sequence to get the robot from room 214 to room 215
 * in the Physics building.
 */
void Robot::from214To215(){
  Robot::forward(2000);
  left();
  Robot::speedUp();
  Robot::forward(11000);
  Robot::right();
  forward(500);
}

/** \brief Determines the current floor.
 *  
 *  This function retrieves the altitude from the BMP180 and uses
 *  this value to determine what floor the robot is on.
 */
int Robot::getFloor(){
  sensors_event_t event;
  bmp.getEvent(&event);
  int altitude;

  if (event.pressure){ //if the sensor read correctly
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:    "); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure));
    altitude = bmp.pressureToAltitude(seaLevelPressure, event.pressure);
  }
  //TODO: CREATE LOOKUP TABLE AND RETURN THE FLOOR
}