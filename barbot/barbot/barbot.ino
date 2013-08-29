#include <Servo.h>

const byte connectedServos = 5;
Servo myServos[connectedServos];

void setup(){
  for(int s=0; s<connectedServos;s++){
    myServos[s].attach(s+2); //set to pin s+2 (starts at pin 2)
    closeServo(s); //close pin on setup
  }
  Serial.begin(9600); //begin serial output
}

void loop(){
  //read from Serial input
  if (Serial.available()){
    runCommand(readCommand());
  }
  delay(500); //wait .5sec before looping again.
}

String readCommand(){
  String commandLine = "";
  char character;
  
  while(Serial.available()){
    character = Serial.read();
    commandLine.concat(character);
  }
  
  return commandLine;
}

void runCommand(String commandLine){
  //need to seperate command from parameters
  String command = commandLine.substring(0,commandLine.indexOf(' '));
  String parameters = commandLine.substring(commandLine.indexOf(' '));
  
  if (command == "commands"){
    //listCommands();
  }else if (command == "valves"){
    listValves();
  }else if (command == "open"){
     openValve(parameters);
  }else if (command == "close"){
    //closeValve(parameters);
  }else{
    printError("Unknown command");
  }

}

void listValves(){
  printSuccess((String)connectedServos);
}

void openValve(String parameters){
  if (parameters == "help"){
    printSuccess("openvalve n [seconds]");
  }else{
    int servo = -1;
    int seconds = -1;
    
    if(parameters.indexOf(" ")){
      servo  = (int)parameters.substring(0,parameters.indexOf(" "));
      seconds = (int)parameters.substring(parameters.indexOf(" "));
    }else{
      servo = (int)parameters;
    }
   
    if ((servo > 0) && (servo < connectedServos)){
      openServo(servo);
      if (seconds > 0){
        delay(seconds*1000);
        closeServo(servo);
      }
      printSuccess("Servo ".(String)servo + " opened. " + (seconds ? "Closed after " + (String)(seconds) + " seconds":""));
    }else{
      printError("Invalid valve number");
    }
  }
}

void printSuccess(String message){
  Serial.write("Success: " + message);
}

void printError(String message){
  Serial.write("Error: " + message);
}

void openServo(int servo){
  myServos[servo].write(170);
}

void closeServo(int servo){
  myServos[servo].write(0);
}


