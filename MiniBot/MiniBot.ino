#include <Servo.h>                           // Include servo library
 
#define lineR_pin 10     //line sensors
#define lineL_pin 11

Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

int lineL;
int lineR;

 /** \brief Sets pin modes and initializes motors.
 *  
 * This function attaches the servos to the servo pins and 
 * sets the pins connected to the line sensors as input pins.
 */
void setup(){
  pinMode(lineR_pin, INPUT);  // declare pinmode for line tracking
  pinMode(lineL_pin, INPUT);
  
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  servoLeft.attach(13);                      // Attach left signal to pin 13
  servoRight.attach(12);                     // Attach right signal to pin 12

  Serial.begin(9600);  //start serial communication
}  

/** \brief Controls the tasks the robot completes.
 * 
 * The loop calls functions to control the motion of the robot.
 */
void loop(){
  sensors();
  printSensors();
}

/** \brief Causes the robot to move forward.
 * 
 * This function sends pulses of equal width to the motors so that the
 * robot moves forward at a constant speed.
 */
void forward(){
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  //delay(3000);                               // ...for 3 seconds
}

/** \brief Causes the robot to move backward.
 *  
 * This function sends pulses of constant width to both motor 
 * controllers so that the robot will move backward at a
 * constant speed.
 */
void backward(){
  servoLeft.writeMicroseconds(1300);   // Left wheel clockwise
  servoRight.writeMicroseconds(1700);  // Right wheel counterclockwise
}

/** \brief Causes the robot to turn left.
 *  
 * This function causes both wheels to turn clockwise so that
 * the robot turns left.
 */
void left(){
  servoLeft.writeMicroseconds(1300);   // Left wheel clockwise
  servoRight.writeMicroseconds(1300);  // Right wheel clockwise
}

/** \brief Causes the robot to turn right.
 *  
 * This function causes both wheels to turn counterclockwise
 * so that the robot turns right.
 */
void right(){
  servoLeft.writeMicroseconds(1700);   // Left wheel counterclockwise
  servoRight.write Microseconds(1700); // Right wheel counterclockwise
}

/** \brief Checks line sensors.
 * 
 * This function reads the input from the line sensors.
 */
int sensors(){
  lineR = digitalRead(lineR_pin); 
  lineL = digitalRead(lineL_pin);
}

/** \brief Prints sensor values.
 * 
 * This function prints the sensor values to the serial monitor.
 */
void printSensors(){
  Serial.println(lineR);
  Serial.print("Left Line Sensor = ");
  Serial.println(lineL);
  Serial.println("--------------------------------------");
}
