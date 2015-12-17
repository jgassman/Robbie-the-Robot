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
  //from214To215();
  //forward(10000);
  //stopRobot();
  wander();
  //speedUp();
  //forward(3000);
  //slowDown();
  //delay(5000);
}

void forward(int goTime){
  int goneTime = 0;
  while(goneTime < goTime){
    if(isStuck()){
      break;
    }
    int curTime = millis();
    digitalWrite(rMotor, HIGH);
    digitalWrite(lMotor, HIGH);
    delayMicroseconds(1750);
    digitalWrite(rMotor,LOW);
    //digitalWrite(lMotor, HIGH);
    //delayMicroseconds(1750);
    digitalWrite(lMotor, LOW);
    delayMicroseconds(5250);
    goneTime += millis() - curTime;
  }
}

void backward(int goTime) {
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

void speedUp() {
  for(int i = 1500; i <= 1750; i+=5){
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

void speedBack(){
  for(int i = 1500; i >= 1250; i-=5){
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

void slowDown(){
 for(int i = 1750; i >= 1500; i-=5){
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

void stopRobot(){
  digitalWrite(rMotor,HIGH);
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(rMotor, LOW);
  digitalWrite(lMotor, LOW);
  delayMicroseconds(5250);  
}

void right(){
  stopRobot();
  delay(500);
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1750);
  digitalWrite(lMotor,LOW);
  digitalWrite(rMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(rMotor, LOW);
  delayMicroseconds(5250);
  delay(1200);
  stopRobot();
  delay(500);
}

void left(){
  stopRobot();
  delay(500);
  digitalWrite(rMotor, HIGH);
  delayMicroseconds(1750);
  digitalWrite(rMotor,LOW);
  digitalWrite(lMotor, HIGH);
  delayMicroseconds(1500);
  digitalWrite(lMotor, LOW);
  delayMicroseconds(5250);
  delay(1200);
  stopRobot();
  delay(500);
}

void wander(){
  while(true){
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
}

void from214To215(){
  forward(1200);
  left();
  speedUp();
  forward(3000);
  forward(3000);
  forward(3000);
  right();
  stopRobot();
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

