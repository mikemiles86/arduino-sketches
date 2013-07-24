// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo servotwo;
int switchState = 0;
int pressed = 0;
 
void setup() 
{ 
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object 
  servotwo.attach(4);
  myservo.write(0);
  servotwo.write(0);
  pinMode(5,INPUT);
} 
 
void loop() 
{ 
  switchState = digitalRead(5);
  if (switchState == LOW){
    pressed = 0;
  }else if ((switchState == HIGH) && (pressed == 0)){
    myservo.write(170);
    delay(15);
    servotwo.write(170);
    delay(3000);
    myservo.write(0);
    delay(15);
    servotwo.write(0);
    delay(5000);
    pressed = 1;
 }
}
