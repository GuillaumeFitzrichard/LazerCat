#include "VarSpeedServo.h"

/* YOU CAN CUSTOM THESE VARIABLES IF YOU WANT TO ALTER THE TOWER BEHAVIOUR 
echo 2
trig 4
tilt 6
pan 9
lazer 13
balloon 27
*/

// X servo angle will stay in [min_x, max_x] range
// Y servo angle will stay in [min_y, max_y] range
// to be adjusted to the size of your living room
#define trigPin 4
#define echoPin 2
float min_x = 75;
float max_x = 150;
float min_y = 0;
float max_y = 25;
int min_freeze = 100;
int max_freeze = 2000;
int minimal_movement;
int call;

VarSpeedServo x_servo;  
VarSpeedServo y_servo;
int pos = 0;

/* YOU SHOULD NOT HAVE TO MODIFY THE CODE BELOW THIS LINE */

// finding center of square for starting point
int random_delay;
float x_position = min_x + (max_x - min_x)/2;
float y_position = min_y + (max_y - min_y)/2; 
float x_old_position = x_position;
float y_old_position = y_position;
float x_new_position;
float y_new_position;
float x_speed;
float y_speed;
int movement_time;
int servoXSpeed;
int servoYSpeed;
int spazRange;

// Instantiating two servos


void setup() {
  Serial.begin (19200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  y_servo.attach(6); 
  x_servo.attach(9);  
  pinMode (13, OUTPUT);
  digitalWrite (13, HIGH);  
  
  
  y_servo.write(y_position, servoYSpeed); 
  x_servo.write(x_position, servoXSpeed);     

}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  spazRange = 75;
  Serial.println("########################LOOP");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance >= spazRange) {
    sensorUnengage(); 
  } else  if (distance > 0 && distance <= spazRange){
    sensorEngage();
  }
}

void randDelay(int time) {
  long duration, distance;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  int pos;
  spazRange = 75;
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  int calls;
  calls = time / 100;
  for (call = 0; call < calls; call++) {
    delay(10);
    Serial.print(time);
    Serial.println("TIME");
    Serial.println(" DELAY!!!!!!****");
    Serial.print(distance);
    Serial.println(" cm");
    if (distance > 0 && distance <= spazRange) {
      sensorEngage();
    }
  }
}
void sensorEngage() {
  long duration, distance;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  movement_time = random(20,40);
  random_delay = random(min_freeze, max_freeze);
  x_new_position = random(min_x+minimal_movement, max_x-minimal_movement);
  y_new_position = random(min_y+minimal_movement, max_y-minimal_movement);

  Serial.println("  ENGAGE++++++++++++++++++++++++++++  ");
  Serial.print(servoXSpeed);
  Serial.println(" Xspeed");
  Serial.print(servoYSpeed);
  Serial.println(" Yspeed");
  Serial.print(distance);
  Serial.println(" cm");
  
  servoXSpeed = random(100, 200);
  servoYSpeed = random(100, 200);
  minimal_movement = random(10);

  if( (y_new_position > y_old_position) && (abs(y_new_position - y_old_position) < 5 )) {
    y_new_position = y_new_position + minimal_movement;
  }  else if ( (y_new_position < y_old_position) && (abs(y_new_position - y_old_position) < 5 )) {
    y_new_position = y_new_position - minimal_movement;
  }

  if( (x_new_position > x_old_position) && (abs(x_new_position - x_old_position) < 5 )) {
    x_new_position = x_new_position + minimal_movement;
  }  else if ( (x_new_position < x_old_position) && (abs(x_new_position - x_old_position) < 5 )) {
    x_new_position = x_new_position - minimal_movement;
  }

  x_speed = (x_new_position - x_old_position)/5;
  y_speed = (y_new_position - y_old_position)/5;  
  for (pos = 0; pos < 5; pos += 1) { 
    x_position = x_position + x_speed;
    y_position = y_position + y_speed;
    x_servo.write(x_position, servoXSpeed);  
    y_servo.write(y_position, servoYSpeed);                    
    delay(10);
  }
  x_old_position = x_new_position;
  y_old_position = y_new_position;
  delay(10);
  
}

void sensorUnengage() {
  long duration, distance;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  movement_time = random(40,100);
  random_delay = random(min_freeze, max_freeze);
  x_new_position = random(min_x+minimal_movement, max_x-minimal_movement);
  y_new_position = random(min_y+minimal_movement, max_y-minimal_movement);
  
  Serial.println("  UNENGAGE------------------- ");
  Serial.print(servoXSpeed);
  Serial.println(" Xspeed");
  Serial.print(servoYSpeed);
  Serial.println(" Yspeed");
  Serial.print(distance);
  Serial.println(" cm");

  servoXSpeed = random(20, 100);
  servoYSpeed = random(20, 100);
  minimal_movement = random(10);
  if( (y_new_position > y_old_position) && (abs(y_new_position - y_old_position) < 5 )) {
    y_new_position = y_new_position + minimal_movement;
  }  else if ( (y_new_position < y_old_position) && (abs(y_new_position - y_old_position) < 5 )) {
    y_new_position = y_new_position - minimal_movement;
  }
  
  if( (x_new_position > x_old_position) && (abs(x_new_position - x_old_position) < 5 )) {
    x_new_position = x_new_position + minimal_movement;
  }  else if ( (x_new_position < x_old_position) && (abs(x_new_position - x_old_position) < 5 )) {
    x_new_position = x_new_position - minimal_movement;
  }

  x_speed = (x_new_position - x_old_position)/movement_time;
  y_speed = (y_new_position - y_old_position)/movement_time;  
  for (pos = 0; pos < movement_time; pos += 1) {
    digitalWrite (13, HIGH); 
    x_position = x_position + x_speed;
    y_position = y_position + y_speed;
    x_servo.write(x_position, servoXSpeed);  
    y_servo.write(y_position, servoYSpeed); 
    if (servoXSpeed < 40 || servoYSpeed < 40) {
      digitalWrite (13, LOW); 
    }                   
    delay(10);
  } 

  
  x_old_position = x_new_position;
  y_old_position = y_new_position;
  digitalWrite (13, HIGH);
  randDelay(random_delay);
}

