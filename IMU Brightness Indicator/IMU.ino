#include <Wire.h>
#include "IMU.h"
#include "sensor_fusion.h"

extern float IMU_X;
extern float IMU_Y;
extern float IMU_Z;

int X_val;
int Y_val;
int Z_val;

byte c;

#define LEDG 3
#define LEDW 4
#define LEDR 6

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDW, OUTPUT);
  pinMode(LEDW, OUTPUT);
  
  imu_setup();
}

void loop() {
  imu_loop();
  X_val = IMU_X * 100;
  Y_val = IMU_Y * 100;
  Z_val = IMU_Z * 100;

  X_val = map(X_val,-100,100,0,255);
  Y_val = map(Y_val,-100,100,0,255);
  Z_val = map(Z_val,-100,100,0,255);

  analogWrite(LEDG, X_val);
  analogWrite(LEDW, Y_val);
  analogWrite(LEDR, Z_val);
  
  delay(100); 
}
