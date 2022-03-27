/*
 * A distance sensor using IR Emitter and IR Receiver 
 * The brightness of the LED changes depends on the distance between the IR emitter and the receiver
 */
 
#define IR 4
#define LED 6

long zero;

void setup() {
  Serial.begin(9600);
  
  pinMode(IR, INPUT);
  pinMode(LED, OUTPUT);
  
  zero = 0; //Noise Calibration Takes 100 samples 
  for (int i=0; i<100; i++)
  {
    zero += analogRead(IR);
  }
  
  zero /= 100;
}

void loop() 
{
  int val = analogRead(IR);
  val = map(val, zero, 1023, 0, 255);
  val = constrain(val, 0, 255);
  Serial.println(val); 
  analogWrite(LED,val); 
  delay(500);
}
