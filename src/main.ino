#include <Wire.h>
#include <ADXL345.h>
#include <PID_v1.h>
#include <L293.h>

ADXL345 accel(ADXL345_ALT);

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
// Kp > 400
//double Kp=55500.0, Ki=1.2, Kd=0.39;
double Kp=100000.0, Ki=20.0, Kd=5.0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// motor pins
const int speedPin1 = 9;		// that is the pin that we use to control the motor's speed
const int forwardPin1 = 6;	// this is the pin that we use to tell the motor to go forward
const int speedPin2 = 11;		// that is the pin that we use to control the motor's speed
const int forwardPin2 = 10;	// this is the pin that we use to tell the motor to go forward
// const int reversePin = 4;	// this is the pin that we use to tell the motor to go reverse
//L293_twoWire motor1( speedPin1, forwardPin1 );
//L293_twoWire motor2( speedPin2, forwardPin2 );

long int crono;
long int muestras;

void setup() {
  Serial.begin(9600);
  Wire.begin();


  /******************************************************************************
  * ADXL345 acelerometer configuration
  ******************************************************************************/

  byte deviceID = accel.readDeviceID();
  if (deviceID != 0) {
    Serial.print("0x");
    Serial.print(deviceID, HEX);
    Serial.println("");
  } else {
    Serial.println("read device id: failed");
    while(1) {
      delay(100);
    }
  }

  // Data Rate
  // - ADXL345_RATE_3200HZ: 3200 Hz
  // - ADXL345_RATE_1600HZ: 1600 Hz
  // - ADXL345_RATE_800HZ:  800 Hz
  // - ADXL345_RATE_400HZ:  400 Hz
  // - ADXL345_RATE_200HZ:  200 Hz
  // - ADXL345_RATE_100HZ:  100 Hz
  // - ADXL345_RATE_50HZ:   50 Hz
  // - ADXL345_RATE_25HZ:   25 Hz
  // - ...
  //if (!accel.writeRate(ADXL345_RATE_200HZ)) {
  if (!accel.writeRate(ADXL345_RATE_3200HZ)) {
    Serial.println("write rate: failed");
    while(1) {
      delay(100);
    }
  }

  // Data Range
  // - ADXL345_RANGE_2G: +-2 g
  // - ADXL345_RANGE_4G: +-4 g
  // - ADXL345_RANGE_8G: +-8 g
  // - ADXL345_RANGE_16G: +-16 g
  if (!accel.writeRange(ADXL345_RANGE_16G)) {
    Serial.println("write range: failed");
    while(1) {
      delay(100);
    }
  }

  if (!accel.start()) {
    Serial.println("start: failed");
    while(1) {
      delay(100);
    }
  }

  /******************************************************************************
  * PID configuration
  ******************************************************************************/
  //initialize the variables we're linked to
  Input = accel.getZ();
  Setpoint = 0.085;

  //turn the PID on
  myPID.SetOutputLimits(-254.0,254.0);
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(2);

  delay(3000);

  pinMode(speedPin1, OUTPUT);
  pinMode(speedPin2, OUTPUT);
  pinMode(forwardPin1, OUTPUT);
  pinMode(forwardPin2, OUTPUT);

  crono = millis();
  muestras = 0;

}

void loop() {
  if (!accel.update()) return;

  //
  /*
  muestras ++;
  if (millis() - crono > 1000) {
      // Serial.println(muestras);
      muestras = 0;
      crono = millis();
  }
  */

# if 0
  Serial.print(accel.getX());
  Serial.print(",");
  Serial.print(accel.getY());
  Serial.print(", z =");
  Serial.print(accel.getZ());
  Serial.println("");
# endif
 // Serial.println(accel.getZ());

  Input = accel.getZ();
  myPID.Compute();
  int speed = Output;

# if 1
  Serial.print("input: ");
  Serial.print(Input);
  Serial.print(" output: ");
  Serial.println(Output);
  Serial.print(" speed: ");
# endif

# if 0
  // delay(150);
  if (speed > 0) {

      speed = map(speed, 0,255,20,255);

      digitalWrite(speedPin1, LOW);
      analogWrite(forwardPin1, speed);
      digitalWrite(speedPin2, LOW);
      analogWrite(forwardPin2, speed);
//      motor1.forward( speed) ;	// set the direction and the speed of the motor
//motor2.forward( int(Output) );	// set the direction and the speed of the motor
  }
  else {

      speed = map(speed, 0,-255,-20,-255);
      
      digitalWrite(forwardPin1, LOW);
      analogWrite(speedPin1, -speed);
      digitalWrite(forwardPin2, LOW);
      analogWrite(speedPin2, -speed);
//     motor1.back( speed );		// set a new direction and the speed of the motor
//     motor2.back( int(Output) );		// set a new direction and the speed of the motor

  }
# endif

}
