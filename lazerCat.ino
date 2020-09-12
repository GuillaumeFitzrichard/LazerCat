#include <Servo.h>

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
// to be ajsuted to the size of your living room
#define trigPin 4
#define echoPin 2
float min_x = 50;
float max_x = 180;
float min_y = 0;
float max_y = 55;
int min_freeze = 200;
int max_freeze = 3000;
float minimal_movement = 5;

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

// Instantiating two servos
Servo x_servo;  
Servo y_servo;
int pos = 0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  y_servo.attach(6);  // attaches the y servo on pin 6 to the servo object
  x_servo.attach(9);  // attaches the x servo on pin 9 to the servo object
  pinMode (13, OUTPUT);
  digitalWrite (13, HIGH);  // switch on  the laser
  
  //Place the servos in the center at the beginning 
  y_servo.write(y_position); 
  x_servo.write(x_position);     

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
  movement_time = random(10,40);
  random_delay = random(min_freeze, max_freeze);
  x_new_position = random(min_x+minimal_movement, max_x-minimal_movement);
  y_new_position = random(min_y+minimal_movement, max_y-minimal_movement);

  Serial.print(distance);
  Serial.println(" cm");
  if (distance <= 0 || distance <= 50)
  {
    if( (y_new_position > y_old_position) && (abs(y_new_position - y_old_position) < 5 )) {
    y_new_position = y_new_position + 10;
  }  else if ( (y_new_position < y_old_position) && (abs(y_new_position - y_old_position) < 5 )) {
    y_new_position = y_new_position - 10;
  }
  
  if( (x_new_position > x_old_position) && (abs(x_new_position - x_old_position) < 5 )) {
    x_new_position = x_new_position + 10;
  }  else if ( (x_new_position < x_old_position) && (abs(x_new_position - x_old_position) < 5 )) {
    x_new_position = x_new_position - 10;
  }

  x_speed = (x_new_position - x_old_position)/10;
  y_speed = (y_new_position - y_old_position)/10;  
  for (pos = 0; pos < 10; pos += 1) { 
      x_position = x_position + x_speed;
      y_position = y_position + y_speed;
      x_servo.write(x_position);  
      y_servo.write(y_position);                    
    delay(10); 
  }
  x_old_position = x_new_position;
  y_old_position = y_new_position;
  delay(10);
  } else {

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
      x_position = x_position + x_speed;
      y_position = y_position + y_speed;
      x_servo.write(x_position);  
      y_servo.write(y_position);                    
    delay(10); 
  }
  x_old_position = x_new_position;
  y_old_position = y_new_position;
  delay(random_delay);
  }
}