int switchState = 0;
int wait = 100; //milliseconds.

void setup(){
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(2,INPUT);
}

void loop(){
  //read voltage of pin 2
  switchState = digitalRead(2);
  //button is not pressed
  if (switchState == LOW){
    //enable pin 3, disable 4 & 5
    onOffOffPause(3,4,5);
  }else{
    //enable pin 5, disable 3 & 4
    onOffOffPause(5,3,4);
    //enable pin 4, disable 3 & 5
    onOffOffPause(4,3,5);
  }
}

void onOffOffPause(int x,int y,int z){
  digitalWrite(x,HIGH);
  digitalWrite(y,LOW);
  digitalWrite(z,LOW);
  delay(wait);
}
