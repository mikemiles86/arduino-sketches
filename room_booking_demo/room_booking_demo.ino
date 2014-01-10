int last_state = 0;
int pressed    = 0;
int wait       = 200;

int button     = 13;
int red        = 3;
int blue       = 4;
int green      = 5;

void setup(){
  pinMode(button, INPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  turnOn(blue);
}

void loop(){
  if (buttonChanged()){
    pendingRoom();
  }else if (pressed){
    if (wait<1){
      resetRoom();
    }else {
      wait--;
    }
  }
  delay(100);
}

void pendingRoom(){
  pressed = 1;
  wait    = 200;
  turnOff(blue);
  turnOn(red);
}

void resetRoom(){
  pressed = 0;
  wait    = 200;
  turnOff(red);
  turnOn(blue);
}

boolean buttonChanged(){
  if (digitalRead(button) != last_state){
    last_state = digitalRead(button);
    return true;
  }
  return false;
}

void turnOn(int pin){
  digitalWrite(pin, HIGH);
}

void turnOff(int pin){
  digitalWrite(pin, LOW);
}



