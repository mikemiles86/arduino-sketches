int next_led = 10;

void setup() {
  pinMode(2, INPUT); //button
  pinMode(10, OUTPUT); //led1
  pinMode(11, OUTPUT); //led2
  pinMode(12, OUTPUT); //led3
  pinMode(13, OUTPUT); //led4
}

void loop() {
 
  int button_pushed = digitalRead(2);
  
  if (button_pushed && (next_led < 14)) {
    digitalWrite(next_led, HIGH);
    next_led++;
  }
  delay(2000);
  
}
