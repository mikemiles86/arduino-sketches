//PhotoResistor Sensor Variables
// The pin of the pr sensor
uint8_t prSensorPin      = A0; 
// The amount of variance between readings to single a change.
int prSensorThreshold    = 80; 
// The previous value recorded
int prSensorLastValue    = 0;  
// The current value recorded
int prSensorValue        = 0;  

//Light variables
//  The current state of the lights (0=unknown, -1=off, 1=on)
int lightState          = 0;  
//  boolen if the lights state have recently changed.
boolean lightChanged    = false;  

//Passive Infra Red Sensor Variables
// The pin of the PIR sensor
const int pirSensorPin        = 2;
// The number of seconds to calibrate the sensor
int pirSensorCalibrationTime  = 30;

//Movement variables
// boolean if there is movement
boolean movement        = false;
//last second movement was detected.
int movementLast        = 0;
//threshold for gaps in seconds for movement.
int movementThreshold   = 5;

//LED pins.
const int greenLED = 12;
const int redLED   = 11;
const int yellowLED= 10;

//state of the room (0 = open, 1 = occupied)
int roomState      = 0;

//number of seconds to delay each loop
int loopDelay      = 2;

//SETUP
void setup(){
  //record serial output for monitoring
  Serial.begin(9600);
  // run setup function for the LEDs
  setupLeds();
  strobeLeds(2);
  // run setup function for the PIR Sensor
  setupPirSensor();
  strobeLeds(2);
  // run setup function for the PR sensor
  setupPrSensor();
  strobeLeds(2);
  delay(500);
  // turn off all leds.
  flashLeds(1);
  // System ready.
  Serial.println("System Ready.");
}

//LOOP
void loop(){
    //check status of PIR Sensor
    checkPirSensor();
    //check status of PR Sensor
    checkPrSensor();
    //set the status of the room
    checkRoomState();
    //set the status of the room
    setRoom();
   Serial.println("----------");
   delay(loopDelay*1000);
}

/////////////////////////////
// SETUP FUNCTIONS

void setupLeds(){
  Serial.print("Setup LEDs");
  delay(500);
  pinMode(greenLED,OUTPUT);
  digitalWrite(greenLED,HIGH);
  Serial.print(".");
  delay(500);
  pinMode(redLED,OUTPUT);
  digitalWrite(redLED,HIGH);
  Serial.print(".");
  delay(500);
  pinMode(yellowLED,OUTPUT);
  digitalWrite(yellowLED,HIGH);
  Serial.print(".");
  delay(500);
  Serial.println(" complete.");
  flashLeds(1);
}


void setupPirSensor(){
  pinMode(pirSensorPin,INPUT);
  digitalWrite(pirSensorPin,LOW);
  int calibrateDelay = 1000;
  //begin calibration
  Serial.print("calibrating PIR Sensor");
  for( int i = 0; i < pirSensorCalibrationTime; i++){
    calibrateDelay = 1000 - strobeLeds(1);
    Serial.print(".");
    delay(calibrateDelay);
  }
  //record current time as last movement.
  movementLast = millis()/1000;
  Serial.println(" calibrated.");
}
  
void setupPrSensor(){
  Serial.print("calibrating PR Sensor");
  int calibrateDelay = 1000;
  for( int i =0; i < 3;i++){
    calibrateDelay = 1000 - strobeLeds(1);
    Serial.print(".");
    delay(calibrateDelay);
  }
  //record current reading as last reading.
  prSensorLastValue = analogRead(prSensorPin);
  Serial.println(" calibrated.");
}



/////////////////////////////
// CHECK FUNCTIONS
void checkPirSensor(){
  Serial.println("Check PIR sensor.");
  //if PIR voltage is high, there is movement.
  if (digitalRead(pirSensorPin) == HIGH){
    movement = true;
    //record timing of this movement
    movementLast = millis()/1000;
  }else{
    movement = false;
  }
}

void checkPrSensor(){
  lightChanged = false;
  Serial.println("Check PR sensor.");
  prSensorValue = analogRead(prSensorPin);
  //have value changed dramatically since last reading?
  if (abs(prSensorLastValue - prSensorValue) >= prSensorThreshold){
    lightChanged = true;
    //was last reading greater then this reading?
    if (prSensorLastValue > prSensorValue){
      //lights have turned off
      lightState=-1;
    }else{
      //lightes have turned on
      lightState=1;
    }
  }
  //set this reading to be last reading for next loop.
  prSensorLastValue = prSensorValue;
}

void checkRoomState(){
  //was movement detected?
  if (movement){
      //have the lights changed?
      if (lightChanged){
        //have the lights gone up? (turned on)
        if (lightState > 0){
          //assume someone has walked into the room
          Serial.println("Someone in the room and lights were turned on");
          roomState = 1;
        //have the lights gone down (turned off)
        }else if (lightState < 0){
          //assume someone has walked out of the room
          Serial.println("Someone in the room and lights were turned off");
          roomState = 0;
        }
      //lights havent changed, but are they on?
      }else if (lightState > 0){
        //assume someone walked into a bright conference room
        Serial.println("Someone in the room with lights on.");
        roomState = 1;
      //lights have not changed, but are off
      }else{
        Serial.println("Someone in the room with lights off.");
        //assume someone walked into a dark conference room
        roomState = 1;
      }
  //no movement for the threshold time?
  }else if (((millis()/1000)-movementLast)>= movementThreshold){
    //assume no one is in the room.
    Serial.println("No movement in room for a while. Assume empty");
    roomState = 0;
  }
}

boolean checkRoomReserved(){
  /**
   * In future check exchange for reserved data
   */
   return false;
}

/////////////////////////////
// SET FUNCTIONS

void setLeds(boolean greenSettings, boolean redSettings, boolean yellowSettings){
  digitalWrite(greenLED,greenSettings);
  digitalWrite(redLED,redSettings);
  digitalWrite(yellowLED,yellowSettings);
}

void setRoom(){
  if (roomState){
    Serial.println("[ROOM IS OCCUPIED]");
    roomOccupiedLeds();
  }else if (checkRoomReserved()){
    Serial.println("[ROOM IS RESERVED]");
    roomReservedLeds();
  }else{
    Serial.println("[ROOM IS EMPTY]");
    roomOpenLeds();
  }
}

/////////////////////////////
// LED EFFECT FUNCTIONS

void roomOccupiedLeds(){
  setLeds(LOW,HIGH,LOW);
}

void roomOpenLeds(){
  setLeds(HIGH,LOW,LOW);
}

void roomReservedLeds(){
  setLeds(LOW,LOW,HIGH);
}

int flashLeds(int flashLoop){
  //will return the time taken to flash
  int start = millis();
  setLeds(LOW,LOW,LOW);
  for( int i=0; i < flashLoop; i++){
    setLeds(HIGH,HIGH,HIGH);
    delay(200);
    setLeds(LOW,LOW,LOW);
    delay(200);
  }

  return millis()-start;
}

int strobeLeds(int strobeLoop){
  //will return the time taken to strobe
  int start = millis();
  setLeds(LOW,LOW,LOW);
  for (int i=0; i < strobeLoop; i++){
    setLeds(HIGH,LOW,LOW);
    delay(200);
    setLeds(LOW,HIGH,LOW);
    delay(200);
    setLeds(LOW,LOW,HIGH);
    delay(200);
  }
  setLeds(LOW,LOW,LOW);
  //return the time taken.
  return millis()-start;
}


