//var to hold sensor value
int lightSensorValue;
//var to hold last sensor value
int lightSensorLastValue = 0;
//var to hold varience level
int lightSensorVariance = 40;
//var to hold LED status
int ledStatus = 0;

//LED pin
const int greenLEDPin = 11;
const int redLEDPin   = 12;

void setup(){
  //Make the LED pins output.
  pinMode(greenLEDPin,OUTPUT);
  pinMode(redLEDPin,OUTPUT);
  Serial.begin(9600);
  lightSensorLastValue = analogRead(A0);
  roomOpen();
}

void loop(){
  
  int lights = lightsChanged();
  
  //lights go up?
  if (lights > 0){
    roomOccupied();
  //lights went down
  }else if (lights < 0){
    roomOpen();
  }
 //wait another second.
  delay(2000);
}

int lightsChanged(){
    int changed = 0;
  //read the input from A0 and store it in a variable
    lightSensorValue = analogRead(A0);
    Serial.print(lightSensorValue);
    Serial.print("\n");
    //has it changed since the last reading?
    if (abs(lightSensorLastValue - lightSensorValue)>= lightSensorVariance){
      if (lightSensorLastValue > lightSensorValue){
        changed--;
      }else{
        changed++;
      }
    }
    lightSensorLastValue = lightSensorValue;
    return changed;   
}

void roomOpen(){
   Serial.print("Changed: Open\n");
   digitalWrite(greenLEDPin,HIGH);
  digitalWrite(redLEDPin,LOW);
}

void roomOccupied(){
   Serial.print("Changed: Occupied\n");
   digitalWrite(greenLEDPin,LOW);
  digitalWrite(redLEDPin,HIGH);
}

