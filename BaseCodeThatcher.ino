/**
 * @author Jessica Thatcher
 * 
 * @version 1.0, Oct 4, 2015
 */
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#define rMotor 13 /**< The variable to control the right motor controller */
#define lMotor 12 /**< The variable to control the left motor controller */

#define frontSensor A1    /**< \def The pin connected to the front sensor */
#define backSensor A2     /**< \def The pin connected to the back sensor */
#define rightSensor A3    /**< \def The pin connected to the right sensor */
#define leftSensor A4     /**< \def The pin connected to the left sensor */

int frontReading[3] = {0, 0, 0};  /**< An array to hold readings from the front sensor */
int backReading[3] = {0, 0, 0};   /**< An array to hold readings from the back sensor */
int rightReading[3] = {0, 0, 0};  /**< An array to hold readings from the right sensor */
int leftReading[3] = {0, 0, 0,};  /**< An array to hold readings from the left sensor */

int frontRead = 0;  /**< A variable to hold the average of the last three readings from the front sensor */
int backRead = 0;   /**< A variable to hold the average of the last three readings from the back sensor */
int leftRead = 0;   /**< A variable to hold the average of the last three readings from the left sensor */
int rightRead = 0;  /**< A variable to hold the average of the last three readings from the right sensor */

static int SLOW_THRESHOLD = 300;  /**< The sensor value to signal the robot should slow down */
static int STOP_THRESHOLD = 200;  /**< The sensor value to siganl the robot to stop now */

char currentMotion = ' ';   /**< Keeps track of whether the robot is moving forward or backward */

/** \brief Sets pin modes and initializes motors.
 *  
 * This function declares the pins connected to the motors as output
 * pins and sends initializing pulses to the motor controllers. It also
 * sets the pins connected to the IR sensors as input pins.
 */
void setup() {
  delay(5000);
  pinMode(rMotor, OUTPUT);    //declare motor pins as output
  pinMode(lMotor, OUTPUT);
  pinMode(frontSensor, INPUT);  //declare sensor pins as input
  pinMode(backSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(rxPin, INPUT);        //declare serial read pin as input
  pinMode(txPin, OUTPUT);       //declare serial transmit pin as output
  Serial.begin(4800);
  for(int i = 0; i < 300; i++){ //initialize input buffer for GPS reading
    input[i] = ' ';
  }
  delay(5);
  digitalWrite(rMotor, HIGH); //send initializing pulses to the motor controllers
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(rMotor, LOW);
  digitalWrite(lMotor, LOW);
  delay(20);
}

/** \brief Controls the tasks the robot completes.
 * 
 * The loop calls functions to determine what tasks Robbie currently needs to complete.
 * These tasks are determined by input from the touchscreen.
 */
void loop() {
}

/** \brief Makes the motor controllers accelerate forward.
 * 
 * This function sends pulses to each motor controller so that the 
 * robot gradually sppeds up to top speed.
 */
void speedUp() {
  currentMotion = 'F';
  for(int i = 1500; i <= 1750; i++){
    digitalWrite(rMotor, HIGH);
    digitalWrite(rMotor, HIGH);
    delayMicroseconds(i);
    digitalWrite(lMotor, LOW);
    digitalWrite(lMotor, LOW);
    delayMicroseconds(5250);
    delayMicroseconds(150);
  }
}

/** \brief Continually sends pulses to motors so that they move forward.
 * 
 * This function sends pulses of equal width to the motors so that the
 * robot moves forward at a constant speed.
 */
void forward(){
  currentMotion = 'F';
  digitalWrite(rMotor, HIGH);
  digitalWrite(rMotor, HIGH);
  delayMicroseconds(1750);
  digitalWrite(lMotor, LOW);
  digitalWrite(lMotor, LOW);
  delayMicroseconds(5250);
}

/** \brief Stops the forward-moving robot.
 *  
 * This function sends pulses of decreasing width to the motor
 * controllers to slow down the robot to a stop.
 */
void stopFromForward(){
  for(int j = 1750; j >= 1500; j--){
    digitalWrite(rMotor, HIGH);
    digitalWrite(lMotor, HIGH);
    delayMicroseconds(j);
    digitalWrite(rMotor, LOW);
    digitalWrite(lMotor, LOW);
    delayMicroseconds(5250);
    delayMicroseconds(150);
  }
  currentMotion = 'S';
}

/** \brief Causes the robot to move backward.
 *  
 * This function sends pulses of constant width to both motor 
 * controllers so that the robot will move backward at a
 * constant speed.
 */
void backward() {
  currentMotion = 'B';
  digitalWrite(rMotor, HIGH);
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1250);
  digitalWrite(rMotor, LOW);
  digitalWrite(lMotor, LOW);
  delayMicroseconds(5250);
}

/** \brief Accelerates the robot backwards.
 * 
 * This function sends pulses of decreasing width to the motor
 * controllers so that the robot speeds up in the backwards direction.
 */
void speedBack(){
  currentMotion = 'B';
  for(int i = 1500; i >= 1250; i++){
    digitalWrite(rMotor, HIGH);
    digitalWrite(rMotor, HIGH);
    delayMicroseconds(i);
    digitalWrite(lMotor, LOW);
    digitalWrite(lMotor, LOW);
    delayMicroseconds(5250);
  }
}

/** \brief Stops the robot from backwards motion.
 * 
 * This function sends pulses of increasing width to the motor
 * controllers so that the robot slows to a stop from moving
 * backwards.
 */
void stopFromBackward(){
  for(int j = 1250; j <= 1500; j--){
    digitalWrite(rMotor, HIGH);
    digitalWrite(lMotor, HIGH);
    delayMicroseconds(j);
    digitalWrite(rMotor, LOW);
    digitalWrite(lMotor, LOW);
    delayMicroseconds(5250);
    delayMicroseconds(150);
  }
  currentMotion = 'S';
}

/** \brief Causes the robot to turn right.
 *  
 * This function stops the right motor controller and sets
 * left motor controller to forward so that the robot 
 * turns left.
 */
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

/** \brief Keeps the robot from moving.
 * 
 * This function keeps the robot from moving by sending pulses of the correct width
 * to the motor controllers.
 */
void stayStopped(){
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(lMotor, LOW);
  digitalWrite(rMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(rMotor, LOW);
  delayMicroseconds(5250);
}

/** \brief Causes the robot to turn left.
 *  
 * This function stops the left motor controller and sets the
 * right motor controller to forward so that the robot 
 * turns left.
 */
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

/** \brief Reads each sensor and updates variables accordingly.
 * 
 * This function reads the value from each sensor and updates each
 * sensor's array. The oldest reading is dropped, and the newest
 * reading is added.
 */
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

/** \brief Finds the location of the desired room.
 *  
 * This function finds the location of the requested room using a lookup table.
 */
int findLocation(int room){
  int rooms[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  /**< An array to hold the room numbers that Robbie can visit */
  int locations[15] = {(1, 1), (2, 2), (3, 3), (4, 4), (5, 5), (6, 6), (7, 7), (8, 8),
              (9, 9), (10, 10), (11, 11), (12, 12), (13, 13), (14, 14), (15, 15)};
              /**< An array to hold the locations of the rooms */
  int foundIndex = -1;  /**< A variable to hold the index of the found room */

  for(int index = 0; index < 1; index++){
    if(rooms[index] == room){
      foundIndex = index;
      break;
    }
  }
  return locations[foundIndex];
}

/** \brief Simulates random motion.
 * 
 * This function simulates random motion using both location from the GPS and readings from
 * the sensors.
 */
void wander(){
  
}

