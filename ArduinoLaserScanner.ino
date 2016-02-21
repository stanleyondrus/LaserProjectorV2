/*
    Arduino Laser Scanner
    by Stanley Ondrus 2016

    - XY - 2 dimensional laser scanning
    - Automatic mirror calibration
    - Remote serial control (via bluetooth)
    - Auto mode
    - Remote control app with GUI

    www.stanleyprojects.com
    www.github.com/stanleyondrus/ArduinoLaserScanner
*/

#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

static int METHOD = DOUBLE;
static int stepsPerRevolution = 400;  // steps per revolution

Adafruit_StepperMotor *myX = AFMS.getStepper(stepsPerRevolution, 2);
Adafruit_StepperMotor *myY = AFMS.getStepper(stepsPerRevolution, 1);

int serialLed = 10;
int autoLed = 11;
int calibrationLed = 12;
int laserPin = 13;
int switchPin = 14;
int autoModePin = 15;
int photodiodePin = 16;

int speedValue = 800;
int initialSize = 20;

int currentType = 0;
int currentId = 0;
int currentSize = initialSize;
int currentSpeed = speedValue;
int currentDuration = 0;

int minType = 1;
int maxType = 5;  // how many shapes
int minId = 1;
int maxId = 5;  // how many patterns
int minSize = 3;
int maxSize = 30; // size in steps
int minPatternSpeed = 10;
int maxPatternSpeed = 800;  // speed of steppers
int minDuration = 1;
int maxDuration = 10;  // iterations of for loop

int patternSize[] = {5, 10, 15, 20, 25, 30};
int sizeStart = 0;
int sizeEnd = 7;

int photodiodeValue = 0;    // photodiode value needed for calibration
int photodiodeThreshold = 170; // min value when laser points to diode

int returnY = 109;  // Y steps needed to return home from calibration
int returnX = 12;  // X steps needed to return home from calibration

boolean laser = false;
boolean calibrated = false;
boolean calibration = false;
boolean randomSize = false;

int c = 0;  // used for serial receive

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP
void forwardstep1() {
  myX->onestep(FORWARD, METHOD);
}
void backwardstep1() {
  myX->onestep(BACKWARD, METHOD);
}

void forwardstep2() {
  myY->onestep(FORWARD, METHOD);
}
void backwardstep2() {
  myY->onestep(BACKWARD, METHOD);
}

AccelStepper x(forwardstep1, backwardstep1); // use functions to step
AccelStepper y(forwardstep2, backwardstep2); // use functions to step

void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Arudino Laser Scanner");

  pinMode(serialLed, OUTPUT);
  pinMode(autoLed, OUTPUT);
  pinMode(calibrationLed, OUTPUT);
  pinMode(laserPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(autoModePin, INPUT);
  pinMode(photodiodePin, INPUT);

  AFMS.begin();  // create with the default frequency 1.6KHz

  stepperSpeed(speedValue);

  x.setAcceleration(1000);
  y.setAcceleration(1000);

  laserOff();
  sLedOff();
  aLedOff();
  cLedOff();
}

void loop()
{
  if (switchRead())
  {
    if (calibration)
    {
      calibrate();
    }
    if (!(calibrated))
    {
      calibrateOnSerial();
    }
    serialMode();
  }

  if (autoModeRead())
  {
    autoMode();
  }
}

void serialEvent() {
  while (Serial.available())
  {
    c = Serial.read();

    switch (c)
    {
      case 'A': //laser on
        laserOn();
        Serial.println("Laser On");
        break;

      case 'B': //laser off
        laserOff();
        Serial.println("Laser Off");
        break;

      case 'C': //calibrate
        calibrate();
        break;

      case 'D': //stop
        setCurrentPattern(0, 0);
        calibration = false;
        Serial.println("Stopped");
        break;

      case 'E': //random size enable
        randomSize = true;
        Serial.println("Random Size Enabled");
        break;

      case 'F': //random size disable
        randomSize = false;
        Serial.println("Random Size Disabled");
        break;

      case 'G': //size increment
        if (currentSize < 30)
        {
          currentSize += 5;
        }
        //  Serial.println("Current Size: " + currentSize);
        break;

      case 'H': //size decrement
        if (currentSize > 5)
        {
          currentSize -= 5;
        }
        //  Serial.println("Current Size: " + currentSize);
        break;

      case 'I': //square 1
        setCurrentPattern(1, 1);
        currentDetails("Square 1");
        break;

      case 'J': //square 2
        setCurrentPattern(1, 2);
        currentDetails("Square 2");
        break;

      case 'K': //square 3
        setCurrentPattern(1, 3);
        currentDetails("Square 3");
        break;

      case 'L': //square 4
        setCurrentPattern(1, 4);
        currentDetails("Square 4");
        break;

      case 'M': //cross 1
        setCurrentPattern(2, 1);
        currentDetails("Cross 1");
        break;

      case 'N': //cross 2
        setCurrentPattern(2, 2);
        currentDetails("Cross 2");
        break;

      case 'O': //cross 3
        setCurrentPattern(2, 3);
        currentDetails("Triangle 1");
        break;

      case 'P': //cross 4
        setCurrentPattern(2, 4);
        currentDetails("Triangle 2");
        break;

      case 'Q': //line 1
        setCurrentPattern(3, 1);
        currentDetails("Line 1");
        break;

      case 'R': //line 2
        setCurrentPattern(3, 2);
        currentDetails("Line 2");
        break;

      case 'S': //line 3
        setCurrentPattern(3, 3);
        currentDetails("Line 3");
        break;

      case 'T': //line 4
        setCurrentPattern(3, 4);
        currentDetails("Line 4");
        break;

      case 'U': //sticky man figure
        setCurrentPattern(4, 1);
        currentDetails("Man Figure");
        break;

      case 'V': //
        setCurrentPattern(4, 2);
        currentDetails("Smiley");
        break;

      case 'W': //
        setCurrentPattern(4, 3);
        currentDetails("Heart");
        break;

      case 'X': //
        setCurrentPattern(4, 4);
        currentDetails("Star");
        break;
    }
  }
}

//----switches-and-button-reads------------
boolean autoModeRead() {
  if (digitalRead(autoModePin) == HIGH) {
    return true;
  } else {
    return false;
  }
}

boolean switchRead() {
  if (digitalRead(switchPin) == HIGH) {
    return true;
  } else {
    return false;
  }
}
//-----------------------------------------

//------------calibration-----------------
boolean calibrateOnSerial()
{
  calibration = true;
  cLedOn();
  Serial.println("XY Calibration");

  stepY(returnY, 1);
  stepX(returnX, 1);

  for (int a = 0; a <= stepsPerRevolution; a++)
  {
    for (int i = 0; i <= stepsPerRevolution; i++)
    {
      serialEvent();
      if (!(calibration) || (!(switchRead())))
      {
        notSuccessful();
        return false;
      }
      laserOn();
      photodiodeValue = map(analogRead(photodiodePin), 0, 1023, 0, 255);
      //delay(50);
      if (photodiodeValue >= photodiodeThreshold)
      {
        laserOff();
        rotateHome();
        Serial.println("Calibrated");
        cLedOff();
        calibration = false;
        calibrated = true;
        return true;
      }
      stepY(1, 1);
    }
    stepX(1, 1);
  }
  notSuccessful();
}

boolean calibrate() {
  calibration = true;
  cLedOn();
  Serial.println("XY Calibration");

  stepY(returnY, 1);
  stepX(returnX, 1);

  for (int a = 0; a <= stepsPerRevolution; a++)
  {
    for (int i = 0; i <= stepsPerRevolution; i++)
    {
      serialEvent();
      if (!(calibration))
      {
        notSuccessful();
        return false;
      }
      laserOn();
      photodiodeValue = map(analogRead(photodiodePin), 0, 1023, 0, 255);
      //delay(50);
      if (photodiodeValue >= photodiodeThreshold)
      {
        laserOff();
        rotateHome();
        Serial.println("Calibrated");
        cLedOff();
        calibration = false;
        calibrated = true;
        return true;
      }
      stepY(1, 1);
    }
    stepX(1, 1);
  }
  notSuccessful();
}

boolean notSuccessful()
{
  Serial.println("Calibration not successful.");
  laserOff();
  cLedOff();
  rotateHome();
  calibrated = true;
  calibration = false;
  return false;
}

void rotateHome()
{
  stepY(returnY, 2);
  stepX(returnX, 2);
}
//-----------------------------------------


//--------serial-mode-functions--------------
void serialMode()
{
  sLedOn();
  if (currentType != 0 || currentId != 0)
  {
    if (randomSize)
    {
      currentSize = patternSize[random(sizeStart, sizeEnd)];
    }
    currentSpeed = 800;
    currentDuration = 1;
    patternCall(currentType, currentId, currentSize, currentSpeed, currentDuration);
  }
  sLedOff();
}

void setCurrentPattern(int patternType, int patternId)
{
  currentType = patternType;
  currentId = patternId;
}

void currentDetails(String pattern)
{
  String details = pattern + " - Size: " + currentSize + " Speed: " + currentSpeed + " Duration: " + currentDuration;
  Serial.println(details);
}
//-----------------------------------------

//--------auto-mode-functions--------------
void autoMode()
{
  aLedOn();
  calibrated = false;
  currentType = random(minType, maxType);
  currentId = random(minId, maxId);
  currentSize = patternSize[random(sizeStart, sizeEnd)];
  //currentSpeed = random(minPatternSpeed, maxPatternSpeed);
  currentDuration = random(minDuration, maxDuration);

  patternCall(currentType, currentId, currentSize, currentSpeed, currentDuration) ;

  currentType = 0;
  currentId = 0;
  currentSize = initialSize;
  currentDuration = 0;
  aLedOff();
}

void patternCall(int patternType, int patternId, int patternSize, int patternSpeed, int patternDuration)
{
  stepperSpeed(patternSpeed);

  for (int i = 0; i <= patternDuration; i++)
  {
    patternTypeCall(patternType, patternId, patternSize);
  }
}

void patternTypeCall(int patternType, int patternId, int patternSize)
{
  switch (patternType) {
    case 1:
      square(patternId, patternSize);
      break;

    case 2:
      object(patternId, patternSize);
      break;

    case 3:
      line(patternId, maxSize);
      break;

    case 4:
      logo(patternId, maxSize / 2);
      break;

    default:
      square(patternId, patternSize);
      break;
  }
}
//--------------------------------------

//-------------patterns-----------------
void square(int patternId, int patternSize)
{
  switch (patternId) {
    case 1:
      square1(patternSize);
      break;

    case 2:
      square2(patternSize);
      break;

    case 3:
      square3(patternSize);
      break;

    case 4:
      square4(patternSize);
      break;

    default:

      break;
  }
}

void object(int patternId, int patternSize)
{
  switch (patternId) {
    case 1:
      cross1(patternSize);
      break;

    case 2:
      cross2(patternSize);
      break;

    case 3:
      triangle1(20);
      break;

    case 4:
      cicuska(20);
      break;

    default:

      break;
  }
}

void line(int patternId, int patternSize)
{
  switch (patternId) {
    case 1:
      line1(patternSize);
      break;

    case 2:
      line2(patternSize);
      break;

    case 3:
      line3(patternSize);
      break;

    case 4:
      line4(patternSize);
      break;

    default:

      break;
  }
}

void logo(int patternId, int patternSize)
{
  switch (patternId) {
    case 1:
      manFigure(patternSize);
      break;

    case 2:
      smiley(patternSize);
      break;

    case 3:
      heart(patternSize);
      break;

    case 4:
      star(patternSize);
      break;

    default:

      break;
  }
}
//------------------------------------


//-------------squares-----------------
void square1(int squareSize)
{
  laserOn();
  stepX(squareSize, 1);
  stepY(squareSize, 1);
  stepX(squareSize, 2);
  stepY(squareSize, 2);
  laserOff();
}

void square2(int squareSize)
{
  laserOn();
  stepX(squareSize, 1);
  laserOff();
  stepY(squareSize, 1);
  laserOn();
  stepX(squareSize, 2);
  laserOff();
  stepY(squareSize, 2);
}

void square3(int squareSize)
{
  laserOff();
  stepX(squareSize, 1);
  laserOn();
  stepY(squareSize, 1);
  laserOff();
  stepX(squareSize, 2);
  laserOn();
  stepY(squareSize, 2);
  laserOff();
}

void square4(int squareSize)
{
  laserOn();
  delay(50);
  laserOff();
  stepX(squareSize, 1);
  laserOn();
  delay(50);
  laserOff();
  stepY(squareSize, 1);
  laserOn();
  delay(50);
  laserOff();
  stepX(squareSize, 2);
  laserOn();
  delay(50);
  laserOff();
  stepY(squareSize, 2);
}
//----------------------------------------

//-------------objects-----------------
void cross1(int crossSize)
{
  laserOn();
  for (int i = 0; i < crossSize; i++)
  {
    stepX(1, 1);
    stepY(1, 1);
  }
  laserOff();
  stepX(crossSize, 2);
  laserOn();
  for (int i = 0; i < crossSize; i++)
  {
    stepX(1, 1);
    stepY(1, 2);
  }
  laserOff();
  stepX(crossSize, 2);
}

void cross2(int crossSize)
{
  square1(crossSize);

  laserOn();
  for (int i = 0; i < crossSize; i++)
  {
    stepX(1, 1);
    stepY(1, 1);
  }
  laserOff();
  stepX(crossSize, 2);
  laserOn();
  for (int i = 0; i < crossSize; i++)
  {
    stepX(1, 1);
    stepY(1, 2);
  }
  laserOff();
  stepX(crossSize, 2);
}

void triangle1(int objectSize)
{
  laserOn();
  stepX(objectSize, 1);

  for (int i = 0; i < objectSize / 2; i++)
  {
    stepY(2, 1);
    stepX(1, 2);
  }

  for (int i = 0; i < objectSize / 2; i++)
  {
    stepY(2, 2);
    stepX(1, 2);
  }

  laserOff();
}

void cicuska(int crossSize)
{
  int pixel = crossSize / 11;

  stepX(2 * pixel, 1);

  laserOn();

  stepX(7 * pixel, 1);

  //DOPRAVA HORE
  stepY(1 * pixel, 1);
  stepX(1 * pixel, 1);

  stepY(1 * pixel, 1);
  stepX(1 * pixel, 1);

  //STLPEC VPRAVO NAHOR
  stepY(9 * pixel, 1);

  //PRAVE USKO
  stepX(1 * pixel, 2);
  stepY(1 * pixel, 2);

  stepX(1 * pixel, 2);
  stepY(1 * pixel, 2);

  stepX(1 * pixel, 2);
  stepY(1 * pixel, 2);

  stepX(1 * pixel, 2);

  //STRED
  stepY(1 * pixel, 1);
  stepX(3 * pixel, 2);
  stepY(1 * pixel, 2);

  //LAVE USKO
  stepX(1 * pixel, 2);
  stepY(1 * pixel, 1);

  stepX(1 * pixel, 2);
  stepY(1 * pixel, 1);

  stepX(1 * pixel, 2);
  stepY(1 * pixel, 1);

  stepX(1 * pixel, 2);

  //PRAVY STLPEC
  stepY(9 * pixel, 2);

  //DOPRAVA DOLE
  stepX(1 * pixel, 1);
  stepY(1 * pixel, 2);

  stepX(1 * pixel, 1);
  stepY(1 * pixel, 2);

  laserOff();

  stepX(2 * pixel, 2);
}
//----------------------------------------

//-------------line-----------------
void line1(int lineSize)
{
  stepY(lineSize / 2, 1);
  laserOn();
  stepX(lineSize, 1);
  stepX(lineSize, 2);
  laserOff();
  stepY(lineSize / 2, 2);
}

void line2(int lineSize) // from the center to sides
{
  int pixel = lineSize / 11;

  stepY(lineSize / 2, 1);
  stepX(5 * pixel, 1);
  laserOn();
  stepX(1 * pixel, 1);
  stepX(2 * pixel, 2);
  stepX(3 * pixel, 1);
  stepX(4 * pixel, 2);
  stepX(5 * pixel, 1);
  stepX(6 * pixel, 2);
  stepX(7 * pixel, 1);
  stepX(8 * pixel, 2);
  stepX(9 * pixel, 1);
  stepX(10 * pixel, 2);
  stepX(11 * pixel, 1);
  stepX(11 * pixel, 2);
  stepX(11 * pixel, 1);
  stepX(11 * pixel, 2);
  laserOff();
  stepY(lineSize / 2, 2);

}

void line3(int lineSize) // from the center to sides - up/down
{
  int pixel = lineSize / 11;

  stepX(5 * pixel, 1);
  laserOn();
  stepX(1 * pixel, 1);
  stepX(2 * pixel, 2);
  laserOff();
  stepY(3 * pixel, 1);
  laserOn();
  stepX(3 * pixel, 1);
  stepX(4 * pixel, 2);
  laserOff();
  stepY(3 * pixel, 1);
  laserOn();
  stepX(5 * pixel, 1);
  stepX(6 * pixel, 2);
  laserOff();
  stepY(3 * pixel, 1);
  laserOn();
  stepX(7 * pixel, 1);
  stepX(8 * pixel, 2);
  laserOff();
  stepY(3 * pixel, 2);
  laserOn();
  stepX(9 * pixel, 1);
  stepX(10 * pixel, 2);
  laserOff();
  stepY(3 * pixel, 2);
  laserOn();
  stepX(11 * pixel, 1);
  stepX(11 * pixel, 2);
  laserOff();
  stepY(3 * pixel, 2);
  laserOn();
  stepX(11 * pixel, 1);
  stepX(11 * pixel, 2);
  laserOff();
}

void line4(int lineSize) // from the center to sides - up/down
{
  int pixel = lineSize / 11;

  stepY(5 * pixel, 1);
  laserOn();
  stepY(1 * pixel, 1);
  stepY(2 * pixel, 2);
  laserOff();
  stepX(3 * pixel, 1);
  laserOn();
  stepY(3 * pixel, 1);
  stepY(4 * pixel, 2);
  laserOff();
  stepX(3 * pixel, 1);
  laserOn();
  stepY(5 * pixel, 1);
  stepY(6 * pixel, 2);
  laserOff();
  stepX(3 * pixel, 1);
  laserOn();
  stepY(7 * pixel, 1);
  stepY(8 * pixel, 2);
  laserOff();
  stepX(3 * pixel, 2);
  laserOn();
  stepY(9 * pixel, 1);
  stepY(10 * pixel, 2);
  laserOff();
  stepX(3 * pixel, 2);
  laserOn();
  stepY(11 * pixel, 1);
  stepY(11 * pixel, 2);
  laserOff();
  stepX(3 * pixel, 2);
  laserOn();
  stepY(11 * pixel, 1);
  stepY(11 * pixel, 2);
  laserOff();
}
//----------------------------------------

//-------------objects-----------------
void manFigure(int logoSize)
{
  int pixel = logoSize / 11;
  stepY(3 * pixel, 1);
  stepX(3 * pixel, 1);
  laserOn();
  stepY(6 * pixel, 1);
  stepX(3 * pixel, 2);
  stepY(2 * pixel, 1);
  stepX(4 * pixel, 1);
  stepY(3 * pixel, 1);
  stepX(3 * pixel, 1);
  stepY(3 * pixel, 2);
  stepX(4 * pixel, 1);
  stepY(2 * pixel, 2);
  stepX(3 * pixel, 2);
  stepY(6 * pixel, 2);
  stepX(2 * pixel, 2);
  stepY(3 * pixel, 1);
  stepX(1 * pixel, 2);
  stepY(3 * pixel, 2);
  stepX(2 * pixel, 2);
  laserOff();
  stepX(3 * pixel, 2);
  stepY(3 * pixel, 2);
}

void smiley(int logoSize)
{
  int pixel = logoSize / 11;
  stepY(3 * pixel, 1);
  stepX(2 * pixel, 1);
  stepY(2 * pixel, 1);
  laserOn();
  stepY(4 * pixel, 1);
  stepX(2 * pixel, 1);
  laserOff();
  stepY(1 * pixel, 1);
  laserOn();
  stepX(2 * pixel, 2);
  stepY(2 * pixel, 1);
  stepX(2 * pixel, 1);
  stepY(2 * pixel, 2);
  laserOff();
  stepY(1 * pixel, 2);
  laserOn();
  stepY(2 * pixel, 2);
  stepX(3 * pixel, 1);
  stepY(2 * pixel, 1);
  stepX(2 * pixel, 1);
  laserOff();
  stepY(1 * pixel, 1);
  laserOn();
  stepX(2 * pixel, 2);
  stepY(2 * pixel, 1);
  stepX(2 * pixel, 1);
  stepY(2 * pixel, 2);
  laserOff();
  stepY(1 * pixel, 2);
  laserOn();
  stepY(4 * pixel, 2);
  stepX(7 * pixel, 2);
  laserOff();
  stepY(2 * pixel, 2);
  stepX(2 * pixel, 2);
  stepY(3 * pixel, 2);
}

void heart(int logoSize)
{
  int pixel = logoSize / 11;
  laserOff();

  stepX(5 * pixel, 1);

  laserOn();

  stepX(1 * pixel, 1);
  stepY(1 * pixel, 1);

  stepX(1 * pixel, 1);
  stepY(1 * pixel, 1);

  stepX(1 * pixel, 1);
  stepY(1 * pixel, 1);

  stepX(1 * pixel, 1);
  stepY(1 * pixel, 1);

  stepX(1 * pixel, 1);
  stepY(1 * pixel, 1);

  //column right
  stepX(1 * pixel, 1);
  stepY(3 * pixel, 1);
  stepX(1 * pixel, 2);
  //

  stepY(1 * pixel, 1);
  stepX(1 * pixel, 2);
  stepY(1 * pixel, 1);

  //row 2moves right
  stepX(2 * pixel, 2);
  //

  stepY(1 * pixel, 2);
  stepX(1 * pixel, 2);

  stepY(1 * pixel, 2);
  stepX(1 * pixel, 2);

  stepY(1 * pixel, 1);
  stepX(1 * pixel, 2);

  stepY(1 * pixel, 1);

  //row 2moves left
  stepX(2 * pixel, 2);
  //

  stepY(1 * pixel, 2);
  stepX(1 * pixel, 2);

  stepY(1 * pixel, 2);

  //column left
  stepX(1 * pixel, 2);
  stepY(3 * pixel, 2);
  stepX(1 * pixel, 1);
  //

  stepY(1 * pixel, 2);
  stepX(1 * pixel, 1);

  stepY(1 * pixel, 2);
  stepX(1 * pixel, 1);

  stepY(1 * pixel, 2);
  stepX(1 * pixel, 1);

  stepY(1 * pixel, 2);
  stepX(1 * pixel, 1);

  stepY(1 * pixel, 2);

  laserOff();

  stepX(5 * pixel, 2);
}

void star(int logoSize)
{
int pixel= logoSize/11; 

laserOff();

stepX(1*pixel,1);
stepY(2*pixel,1);

laserOn();

stepX(4*pixel,1);
stepY(2*pixel,1);

stepX(1*pixel,1);

stepY(2*pixel,2);

stepX(4*pixel,1);
stepY(1*pixel,1);

stepX(1*pixel,2);
stepY(1*pixel,1);

stepX(1*pixel,2);
stepY(1*pixel,1);

stepX(1*pixel,1);
stepY(1*pixel,1);

stepX(1*pixel,1);

//column right
stepY(2*pixel,1);
//

stepX(3*pixel,2);

stepY(2*pixel,1);

stepX(1*pixel,2);
stepY(1*pixel,1);
stepX(1*pixel,2);
stepY(1*pixel,2);
stepX(1*pixel,2);

//column left
stepY(2*pixel,2);
//

stepX(3*pixel,2);

stepY(2*pixel,2);

stepX(1*pixel,1);
stepY(1*pixel,2);

stepX(1*pixel,1);
stepY(1*pixel,2);

stepX(1*pixel,2);
stepY(1*pixel,2);

stepX(1*pixel,2);
stepY(1*pixel,2);

laserOff();

stepX(1*pixel,2);
stepY(2*pixel,2);
}
//----------------------------------------

//-----stepper-and-laser-control----------
void stepX(int steps, int newDirection)
{
  if (newDirection == 1)
    myX->step(steps, FORWARD, METHOD);
  else
    myX->step(steps, BACKWARD, METHOD);
}

void stepY(int steps, int newDirection)
{
  if (newDirection == 1)
    myY->step(steps, FORWARD, METHOD);
  else
    myY->step(steps, BACKWARD, METHOD);
}

void moveX(int newPosition)
{
  x.moveTo(newPosition);

  while (x.distanceToGo() != 0)
  {
    x.run();
  }
}

void moveY(int newPosition)
{
  y.moveTo(newPosition);

  while (y.distanceToGo() != 0)
  {
    y.run();
  }
}

void moveXY(int newXPosition, int newYPosition)
{
  x.moveTo(newXPosition);
  y.moveTo(newYPosition);

  while (x.distanceToGo() != 0 || y.distanceToGo() != 0)
  {
    x.run();
    y.run();
  }
}

void stepperSpeed(int stepperSpeed)
{
  x.setSpeed(stepperSpeed);
  y.setSpeed(stepperSpeed);
  x.setMaxSpeed(stepperSpeed);
  y.setMaxSpeed(stepperSpeed);
  myX->setSpeed(stepperSpeed);
  myY->setSpeed(stepperSpeed);
}

void laserOn()
{
  digitalWrite(laserPin, HIGH);
}

void laserOff()
{
  digitalWrite(laserPin, LOW);
}
//----------------------------------

//-----------LED-control------------
void sLedOn()
{
  digitalWrite(serialLed, HIGH);
}
void aLedOn()
{
  digitalWrite(autoLed, HIGH);
}
void cLedOn()
{
  digitalWrite(calibrationLed, HIGH);
}

void sLedOff()
{
  digitalWrite(serialLed, LOW);
}
void aLedOff()
{
  digitalWrite(autoLed, LOW);
}
void cLedOff()
{
  digitalWrite(calibrationLed, LOW);
}
//----------------------------------


