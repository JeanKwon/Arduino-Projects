/*
 * Red Light Green Light game 
 * A player gets 5 seconds to push the corresponding button of the blinking LED 
 * Two arduinos are used through UART communication protocol 
 * Play sends the pushCode to the other arduino (Game) when the button is pushed
 */

#include "transmitter.h"

int GButtonPin = 9;
int RButtonPin = 6;

char pushCode = 0;
int GButtonPrevState = 0;
int RButtonPrevState = 0;
int GButtonCurrentState = 0;
int RButtonCurrentState = 0;

void setup() {
  Serial.begin(9600);
  
  transmitter_setup();
  
  pinMode(GButtonPin, INPUT);
  pinMode(RButtonPin, INPUT);
  
  GButtonPrevState = digitalRead(GButtonPin);
  RButtonPrevState = digitalRead(RButtonPin);
}

void loop() {
  GButtonCurrentState = digitalRead(GButtonPin);
  RButtonCurrentState = digitalRead(RButtonPin);

  if (GButtonPrevState == 0 && GButtonCurrentState == 1)
  {
    pushCode = 9; //pushCode 9 represnets that Green button is pushed 
  }
  if (RButtonPrevState == 0 && RButtonCurrentState == 1)
  {
    pushCode = 8; //pushCode 8 represnts that Red button is pushed 
  }
  
  sending(pushCode);

  pushCode = 0; 
  GButtonPrevState = GButtonCurrentState;
  RButtonPrevState = RButtonCurrentState;
  
  delay(100);
}
