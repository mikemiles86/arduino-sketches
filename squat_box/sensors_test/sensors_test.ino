//PhotoResistor Sensor Variables
uint8_t prSensorPin      = A0;
int prSensorLastValue = 0;
//The amount of variance between readings to single a change.
int prSensorThreshold = 80;
int prSensorStatus    = 0;

//PIR Sensor Variables
int pirSensorPin  = 2;
int pirSensorCalibrationTime = 30;

//LED pins.
const int greenLED = 11;
const int redLED   = 12;

//SETUP
void setup(){
  Serial.begin(9600);
  setupLeds();
  setLeds(HIGH,HIGH);
  setupPirSensor();
  setupPrSensor();
  setLeds(LOW,LOW);
  Serial.println("System Ready.");
  setLeds(LOW,LOW);
  roomOpen();
  delay(50);
}

//LOOP
void loop(){
    boolean movement = checkMovement();
    lightsChanged();
    Serial.println(millis()/1000);
    Serial.print("Movement:");
    Serial.println((movement ? "Detected":"None"));
    Serial.print("Lights:");
    Serial.println((prSensorStatus>0 ? "On":(prSensorStatus<0 ? "Off":"Unknown")));
    if ( (movement && (prSensorStatus>0)) || (!movement && (prSensorStatus<0))){
    //if ((movement && (lights>0)) || (!movement && (lights<0))){
      Serial.println("Change Status.");
      if (prSensorStatus > 0){
        roomOccupied();
      }else if (prSensorStatus < 0){
        roomOpen();
      }
    }
    
    //wait 2 seconds.
    delay(2000);
}


boolean checkMovement(){
  boolean movement = false;
  if (digitalRead(pirSensorPin) == HIGH){

     movement = true;
  }else{
    movement = false;
  }

  return movement;
}

void lightsChanged(){
   int changed = 0;
   int prSensorValue = analogRead(prSensorPin);
   //has it changed since the last reading?
   if (abs(prSensorLastValue - prSensorValue)>= prSensorThreshold){
     if (prSensorLastValue > prSensorValue){
        changed--;
      }else{
        changed++;
      }
      prSensorStatus = changed;
   }
   prSensorLastValue = prSensorValue;
}

void roomOccupied(){
  setLeds(LOW,HIGH);
}

void roomOpen(){
  setLeds(HIGH,LOW);
}

//Setup functions
void setupLeds(){
  Serial.println("Setup LEDs");
  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
}

void setupPirSensor(){
  pinMode(pirSensorPin,INPUT);
  digitalWrite(pirSensorPin,LOW);
  
  //calibrate
  Serial.print("calibrating PIR Sensor ");
  for (int i = 0; i < pirSensorCalibrationTime; i++){
    Serial.print(".");
    if (i%2 == 0){
      roomOpen();
    }else{
      roomOccupied();
    }
    delay(1000);
  }
  Serial.println(" done.");
  Serial.println("PIR Sensor Active.");
  delay(50);
}

void setupPrSensor(){
  Serial.print("calibrating PR Sensor");
  roomOpen();
  delay(1000);
  prSensorLastValue = analogRead(prSensorPin);
  roomOccupied();
  delay(1000);
  Serial.println(" done.");
  Serial.println("PR Sensor Active.");
  delay(50);
}


void setLeds(boolean greenSettings, boolean redSettings){
  digitalWrite(greenLED,greenSettings);
  digitalWrite(redLED,redSettings);
}
