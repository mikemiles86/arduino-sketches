int switchState = 0;
int wait = 100; //milliseconds.
int led_pins[7] = {2,3,4,6,7,8,9};
int control_pin = 5;

void setup(){
   for(int p=0;p<sizeof(led_pins);p++){
     pinMode(led_pins[p],OUTPUT);
   }
  pinMode(control_pin,INPUT);
}

void loop(){
  //read voltage of pin 5
  switchState = digitalRead(5);
  //button is not pressed
  if (switchState == LOW){
    wait = 250;
    blinkIn();
  }else{
    wait = 100;
    blinkOut();
  }
}

void blinkIn(){
  turnOffOnDelay(2,9);
  turnOffOnDelay(3,8);
  turnOffOnDelay(4,7);
  turnOffOnDelay(6,6);
  delay(wait);
}

void blinkOut(){
  turnOffOnDelay(6,6);
  turnOffOnDelay(4,7);
  turnOffOnDelay(3,8);
  turnOffOnDelay(2,9);
  delay(wait);
}



void turnOffOnDelay(int on_one,int on_two){
 for (int p=0; p < 8; p++){
  digitalWrite(led_pins[p],LOW);
 }
 digitalWrite(on_one,HIGH);
 digitalWrite(on_two,HIGH);
 delay(wait);
}

