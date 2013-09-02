#include <Servo.h>

const byte connectedServos = 5;
int starting_pin = 2;
//Servo myServos[connectedServos];
int myServos[connectedServos];

void setup(){
  for(int s=0; s<connectedServos;s++){
    //myServos[s].attach(starting_pin+2); //set to pin s+2 (starts at pin 2)
    myServos[s] = starting_pin + s;
    pinMode(myServos[s],OUTPUT);
    toggleServo(s,0); //close pin on setup
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
  int index = commandLine.indexOf(" ");
  String command = commandLine.substring(0,index);
  String parameters = commandLine.substring(index+1);
  
  if (command == "commands"){
    listCommands();
  }else if (command == "valves"){
    listValves();
  }else if (command == "open"){
     toggleValve(parameters,1);
  }else if (command == "close"){
    toggleValve(parameters,0);
  }else{
    printError("Unknown command\""+command+"\"");
  }

}

void listCommands(){
  String msg;
  msg = "\n";
  //msg =msg + "commands: //list of commands\n";
  msg =msg + "valves: //displays the number of valves and thier pins\n";
  msg =msg + "open: [n [s]] //open valve n (optional) close after  s seconds\n";
  msg =msg + "close: [n [s]] //close valve n (optional) after s seconds\n";
  
  msg =msg + "pass\"help\" as parameter for info on command";

  printSuccess(msg);
}

void listValves(){
  String msg = "\n";
   for(int s=0; s<connectedServos;s++){
     msg =msg + s +": pin "+(starting_pin + s) + "\n";
   }
  printSuccess(msg);
}


void toggleValve(String parameters,int open_valve){
  String msg = "";
  if (parameters == "help"){
    msg += (open_valve ? "open":"close");
    msg +=" [valve_num] [seconds]";
    printSuccess(msg);
  }else{
    int servo = -1;
    int seconds = -1;
    int index = parameters.indexOf(" ");
    if(index > 0){
      servo  = stringToInt(parameters.substring(0,index));
      seconds = stringToInt(parameters.substring(index+1));
    }else{
      servo = stringToInt(parameters);
    }
   
    if ((servo >= 0) && (servo < connectedServos)){
      msg = "Valve " + (String)servo;
      if (open_valve){
        msg =msg + " opened and";
        toggleServo(servo,1);
      }
 
      if (seconds > 0){
        delay(seconds*1000);
        msg =msg + " after " + (String)seconds;
      }
      
      if (!open_valve || (open_valve && seconds>0)){
        msg= msg + " closed";
        toggleServo(servo,0);
      }
      if (seconds > 0){
        msg =msg + " after " + (String)seconds;
      }      
      printSuccess(msg);
  }else{
      msg = "Invalid valve number ("+ (String)servo + ")";
      printError(msg);
    }
  }
}

void printSuccess(String message){
  message = "Success: " + message;
  Serial.println(message);
}

void printError(String message){
  message = "Error: " + message;
  Serial.write(message);
}

void toggleServo(int servo,int open_servo){
 // myServos[servo].write((open_servo ? HIGH:LOW));
 if (open_servo){
   digitalWrite(myServos[servo],HIGH);
 }else{
   digitalWrite(myServos[servo],LOW);
 }
}

int stringToInt(String mystring){
  String msg = mystring+ " to ";
  long n =  mystring.toInt();
  msg = msg + n;
//  Serial.println(msg);
  return n;
}

