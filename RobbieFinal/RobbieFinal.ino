#define rMotor 13
#define lMotor 12

#define fSensor A1
#define bSensor A2

int fValue;
int bValue;

const int PROX_THRESHOLD = 150;

void setup() {
  pinMode(lMotor, OUTPUT);
  pinMode(rMotor, OUTPUT);
  pinMode(fSensor, INPUT);
  pinMode(bSensor, INPUT);
  delay(1000);
  digitalWrite(rMotor, HIGH); //send initializing pulses to the motor controllers
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(rMotor, LOW);
  digitalWrite(lMotor, LOW);
  delay(5250);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  from214To215();
  stopRobot();
  delay(5000);
}

void forward(int goTime){
  int goneTime = 0;
  while(goneTime < goTime){
    if(isStuck()){
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

void speedUp() {
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

void slowDown(){
 for(int i = 1750; i >= 1500; i+=10){
   if(isStuck()){
     break;
   }
   digitalWrite(rMotor, HIGH);
   digitalWrite(lMotor, HIGH);
   delayMicroseconds(i);
   digitalWrite(rMotor, LOW);    
   digitalWrite(lMotor, LOW);
   delayMicroseconds(5250);
   delayMicroseconds(150);
  }
}

void stopRobot(){
  digitalWrite(rMotor,HIGH);
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(rMotor, LOW);
  digitalWrite(lMotor, LOW);
  delayMicroseconds(5250);  
}

void right(){
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

void left(){
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

void wander(){
  int randNum = random(101);
  if(randNum % 5 == 0){
    if(randNum / 10 % 2 == 0){
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

void from214To215(){
  forward(2000);
  left();
  speedUp();
  forward(11000);
  right();
  forward(500);
}

bool isStuck(){
  fValue = analogRead(fSensor);
  int whileTime = millis();
  //While something is close to the front sensor
  while(fValue > PROX_THRESHOLD){
    //Stop moving
    stopRobot();
    fValue = analogRead(fSensor);
    //If Robbie is stuck for more than 5 seconds
    if(millis() - whileTime > 5000){
      //Yes, he's stuck
      return true;
    }
  }
  return false;
}

