#include <Pololu3piPlus32U4.h>
using namespace Pololu3piPlus32U4;

Encoders encoders;  //used to measure roatations of the wheels
Buzzer buzzer;      //we can use this to make sounds to indicate different events
Motors motors;      //use this to move
ButtonA buttonA;    //use this to activate events with the press of a button

unsigned long currentMillis;
unsigned long prevMillis;
const unsigned long Period = 50;

long countsLeft = 0;
long countsRight = 0;
long prevLeft = 0;
long prevRight = 0;


//done functions
bool p1 = true;
bool p2 = false;
bool p3 = false;
bool check = true;

const int CLICKS_PER_ROTATION = 12;
const float GEAR_RATIO = 75.81F;
const float WHEEL_DIAMETER = 3.2;
const float WHEEL_CIRCUMFERENCE = 10.0531f;  //wheel revolutions

float SL = 0.0F;  //distance traveled by the left wheel
float Sr = 0.0F;  //distance traveled by the right wheel

int distance[3] = { 12, -12, 18 };




void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  delay(1000);
}

void loop() {
while (check ==true)
{
  while (p1 == true) 
  {
    ledYellow(1);
    
    //calling first forward
    Forward12();

    //switch to next loop
    p1 = false;
    p2 = true;
    ledYellow(0);
    delay(100);
  }

  while (p2 == true)
   {
    ledGreen(1);

    //switch to next loop
    p3 = true;
    p2 = false;
    delay(100);
    ledGreen(0);
    
  }

  while (p3 == true) 
  {

    ledRed(1);

    //calling last forward
    dancemove1();

    //switch to next loop
    buzzer.play("!L16 V8 c23d23e23f3g3ab>23c23ba23g32fedc");
    delay(1000); 
   
    ledRed(0);
    p3 = false;
    check = false;
  }
}
  
}


void checkEncoders() {
  currentMillis = millis();
  if (currentMillis > prevMillis + Period) {
    countsLeft += encoders.getCountsAndResetLeft();
    countsRight += encoders.getCountsAndResetRight();

    SL += ((countsLeft - prevLeft) / (CLICKS_PER_ROTATION * GEAR_RATIO) * WHEEL_CIRCUMFERENCE);
    Sr += ((countsRight - prevRight) / (CLICKS_PER_ROTATION * GEAR_RATIO) * WHEEL_CIRCUMFERENCE);





    //printing out counts
    Serial.print("Left: ");
    Serial.print(SL);

    Serial.print("           Right: ");
    Serial.println(Sr);

    prevLeft = countsLeft;
    prevRight = countsRight;
    prevMillis = currentMillis;
  }
}

void Forward12() {
  checkEncoders();
  int Speed = 150;

  if (SL < 30.5) {
    //start slowing down, left wheels
    if (SL > 20.5) {
      Speed = 100 * ((30 - SL) / 10);

      if (Speed < 70) Speed = 70;
    }

  } else {
    Speed = 0;
  }

  motors.setSpeeds(Speed, Speed);
}

void backwards12() {
  checkEncoders();
  int Speed = -150;

  if (SL > -30.5) {
    //start slowing down, left wheels
    if (SL < -20.5) {
      Speed = -100 * ((-30 + SL) / -10);

      if (Speed < -70) Speed = -70;
    }


  } else {
    Speed = 0;
  }
  motors.setSpeeds(Speed, Speed);
}

void dancemove1() {
  checkEncoders();
  int Speed = 150;

  if (SL < 45.72) {
    //start slowing down, left wheels
    if (SL > 30.5) {
      Speed = 100 * ((30 - SL) / 10);

      if (Speed < 70) Speed = 70;
    }

  } else {
    Speed = 0;
  }
  motors.setSpeeds(Speed, 0);
}

void dancemove2() {
  checkEncoders();
  int Speed = 150;

  if (SL < 45.72) {
    //start slowing down, left wheels
    if (SL > 30.5) {
      Speed = 100 * ((30 - SL) / 10);

      if (Speed < 70) Speed = 70;
    }

  } else {
    Speed = 0;
  }
  motors.setSpeeds(0, Speed);
}