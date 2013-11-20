
int pressed = 0;
int press_count = 0;

void setup() {
  pinMode(13, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  turnOffAll();
  Serial.begin(9600);
}
  
void loop() {
  buttonToggle();
  delay(100);
}

void buttonToggle(){
  if (digitalRead(13) == HIGH) {
    if (!pressed){
      pressed = 1;
      press_count++;
      if (press_count>3){
        press_count = 1;
      }
      turnOn(press_count+2);
    } 
  }else{
    pressed = 0;
    turnOffAll();
    Serial.println("Button Unpressed");
  }

}

void turnOffAll(){
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void turnOn(int pin){
  turnOffAll();
  Serial.println("Turn On " + (String)pin);
  digitalWrite(pin, HIGH);
}

