const int piezo = A0;
const int leds[6] = {2,3,4,5,6,7};

int ambient = 0;
int level = 0;

void setup(){
  for (int p=0;p<sizeof(leds);p++) {
    pinMode(leds[p], OUTPUT);
    digitalWrite(leds[p],HIGH);
  }
  Serial.begin(9600);
  Serial.print("Calibrate");
  calibratePiezo();
  Serial.println("...Calibrated!");
}

void loop() {
  int soundlevel = analogRead(piezo);
  Serial.println("current level:" + (String)soundlevel);
  setLEDS(0,5,false);
  if (soundlevel && (soundlevel >= ambient)) {
    int led_limit = round((soundlevel-ambient)/level);
    Serial.println("Max:" + (String)led_limit);
    setLEDS(0,led_limit,true);
  }
}

void calibratePiezo(){
  long sum = 0;
  int loops = 100;
  int m = 0;
  
  while (m < loops ){
    sum += analogRead(piezo);
    m++;
    delay(100);
  }
  Serial.println("CALIBRATE SUM:"+(String)sum);
  if (sum > 0) {
    ambient = round(sum/loops);
    level = round((1024-ambient)/6);
    Serial.println("Ambient: "+(String)ambient);
    Serial.println("Level: "+(String)level);
  }
}

void setLEDS(int start_led, int end_led, boolean stat) {
  while (start_led <= end_led) {
    digitalWrite(leds[start_led], (stat ? HIGH:LOW));
    start_led++;
  }
}



