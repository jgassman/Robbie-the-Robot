/*
  Robot.h - Library for controlling a robot.
  Created by Jessica Thatcher, November 9, 2015.
  Released into the public domain.
*/
#ifndef ThatcherRobotFinal_h
#define ThatcherRobotFinal_h

#include "Arduino.h"
#include "Adafruit_BMP085_U.h"

class Robot
{
  public:
    Robot();
    void speedUp();
    void forward(int goTime);
	void stopRobot();
	void backward(int goTime);
	void speedBack();
	void right();
	void left();
	int getFloor();
	void wander();
	bool isStuck();
	void from214To215();
	
  private:
	int fValue;
	int bValue;
	const static int PROX_THRESHOLD = 150;
	Adafruit_BMP085_Unified bmp;
};

#endif