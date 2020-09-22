#include <Servo.h> 
Servo xservo; // c
Servo yservo; // o
//Servo Variables
int pos = 0;       
int XServoPin = 9; 
int YServoPin = 8; 
//Joystick variables
int xposPin = A0;    // 
int yposPin = A1;    // 
int Xpos = 0;
int Ypos = 0;
int buttonPin = 7;
int buttonPress = 0;
//Lazer Variables
int lazerPin = 6;

void setup() {
  pinMode(lazerPin,OUTPUT);      
  pinMode(buttonPin,INPUT);      
  digitalWrite(buttonPin,HIGH);  
  xservo.attach(XServoPin);  
  yservo.attach(YServoPin);  
}

void loop() {
  buttonPress = digitalRead(buttonPin); //Read the sate of the button
  if(buttonPress == LOW) // The button press is active low , so if it is pressed we will turn the lazer on
  {
    digitalWrite(lazerPin, HIGH); //Turn Lazer on
  }
  else
  {
    digitalWrite(lazerPin, LOW); // If it is not pressed, keep lazer off
  }


  Xpos = analogRead(xposPin);     // read and store the x position location of the joystick
  Xpos = map(Xpos,0,1023,0,180);  //map the analog read x values to the 0-180 servo values
  Ypos = analogRead(yposPin);     
  Ypos = map(Ypos,0,1023,0,180);  
  xservo.write(Xpos);             
  yservo.write(Ypos);             
  delay(20);                      
}