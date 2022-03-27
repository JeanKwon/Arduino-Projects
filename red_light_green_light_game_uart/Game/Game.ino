/*
 * Red Light Green Light game 
 * A player gets 5 seconds to push the corresponding button of the blinking LED 
 * Two arduinos are used through UART communication protocol 
 * Game receives the data from Play and keeps running the game 
 */

int GLED = 3;
int RLED = 5;
int WLED = 7;

char pushCode = 0; 
int gameScore = 0;
int LEDNum = 0;
int randNum = 11;

unsigned long startTime = 0;
unsigned long diffTime = 0;

char incomingByte;

void setup() 
{
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(WLED, OUTPUT);
}

void loop() 
{
  digitalWrite(GLED,LOW);
  digitalWrite(RLED, LOW);
  
  randNum = random(2);
  LEDSelector(randNum);
  digitalWrite(LEDNum,HIGH);
  
  startTime = millis();
  Serial.flush();

  while(true)
  {
    if(Serial.available() > 0)
    {
      incomingByte = Serial.read();
          if (incomingByte == pushCode) //Check if incomingByte from Play matches the pushCode 
          {
            gameScore++; 
            digitalWrite(LEDNum,LOW);
            Serial.println(gameScore);
            LEDBlink();
            break;
          } 
          else 
          {
                diffTime = millis() - startTime;                
                if( diffTime > 5000) //Check if it has passed 5 seconds 
                {
                  Serial.print("Your final score: ");
                  Serial.println(gameScore);
                  digitalWrite(GLED,LOW);
                  digitalWrite(RLED, LOW);
                  Serial.println("** Game Over. New Game Started ***");
                  gameScore = 0;
                  break;
                }
          }
      }
    }
  }

//Based on the generated number, selects the corresponding LED port and pushCode (9 represents Green, and 8 represents Red) 
int  LEDSelector(int num)
{
  if (num == 0)
  {
    LEDNum = GLED;
    pushCode = 9; 
  }
  else if (num == 1)
  {
    LEDNum = RLED;
    pushCode = 8;
  }
}

void LEDBlink()
{
 int t=0;
  while(t<2)
  {
     digitalWrite(WLED, HIGH);   
     delay(1000);                      
     digitalWrite(WLED, LOW);    
     delay(1000); 
     t++;
  }
 }
