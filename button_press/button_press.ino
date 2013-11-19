int button_state   = 0;
int button_count   = 0;
int button         = 13;
int red            = 3;
int blue           = 4;
int green          = 5;

void setup() {
  pinMode(button,INPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);

  button_state = digitalRead(button);
}

void loop() {
  
  if (buttonChanged()){
    setButtonCount();
    colorChange(button_count);    
  }

}

boolean buttonChanged() {
  boolean return_state = false;
  int current_state = digitalRead(button);
  if (current_state && !button_state) {
 // if (current_state != button_state) {
    return_state =  true;
  }else if (!current_state){
    colorChange(10);
  }
  button_state = current_state;
  return return_state;
}

void setButtonCount() {
  button_count++;
  
  if (button_count > 2){
    button_count = 0;
  }
  
}

void colorChange(int count) {
  switch (count) {
    case 0:
      setColors(HIGH,LOW,LOW);
      break;
    case 1:
      setColors(LOW,HIGH,LOW);
      break;
    case 2:
      setColors(LOW,LOW,HIGH);
      break;
    default:
      setColors(LOW,LOW,LOW);
      break;  
  }
}

void setColors(int red_state, int blue_state, int green_state) {
  digitalWrite(red,red_state);
  digitalWrite(blue,blue_state);
  digitalWrite(green,green_state);
}
