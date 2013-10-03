const byte connectedRelays = 4;
int starting_pin = 2;
int delayTime = 500;
int myRelays[connectedRelays];

void setup(){
  // initialize each relay 
  for (int s=0; s < connectedRelays; s++){
    //set relay pin to s+starting_pin 
     myRelays[s] = starting_pin + s;
     pinMode(myRelays[s], OUTPUT);
     //start the pin high, so relay is open
     toggleRelay(s,1); 
  }
  
  Serial.begin(9600); //begin serial output to send/recieve commands
}

void loop(){
  //read from Serial input for command
  if (Serial.available()){
    //run the command if found and valid
    runCommand(readCommand());
  }
  //delay for delay timesec.
  delay(delayTime);
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
  Serial.println(commandLine);
  if (command == "commands"){
    listCommands();
  }else if (command == "relays"){
    listRelays();
  }else if (command == "open"){
     toggleRelay(parameters,1);
  }else if (command == "close"){
    toggleRelay(parameters,0);
  }else{
    printError("Unknown command\""+command+"\"");
  }

}

void listCommands(){
  String msg;
  msg = "\n";
  //msg =msg + "commands: //list of commands\n";
  msg =msg + "relays: //displays the number of relays and thier pins\n";
  msg =msg + "open: [n [s]] //open relay n (optional) close after  s seconds\n";
  msg =msg + "close: [n [s]] //close relay n (optional) after s seconds\n";
  
  msg =msg + "pass\"help\" as parameter for info on command";

  printSuccess(msg);
}

void listRelays(){
  String msg = "\n";
   for(int s=0; s<connectedRelays;s++){
     msg =msg + s +": pin "+(starting_pin + s) + "\n";
   }
  printSuccess(msg);
}


void toggleRelay(String parameters,int relay_voltage){
  String msg = "";
  if (parameters == "help"){
    msg += (relay_voltage ? "open":"close");
    msg +=" [valve_num] [seconds]";
    printSuccess(msg);
  }else{
    int relay = -1;
    int seconds = -1;
    int index = parameters.indexOf(" ");
    if(index > 0){
      relay  = stringToInt(parameters.substring(0,index));
      seconds = stringToInt(parameters.substring(index+1));
    }else{
      relay = stringToInt(parameters);
    }
   
    if ((relay >= 0) && (relay < connectedRelays)){
      msg = "Relay " + (String)relay;
      if (relay_voltage){
        msg =msg + " opened";
        toggleRelay(relay,1);
      }
 
      if (seconds > 0){
        delay(seconds*1000);
        msg =msg +(relay_voltage ? " after ":"") + (String)seconds;
      }
      
      if (!relay_voltage || (relay_voltage && seconds>0)){
        msg= msg + " closed";
        toggleRelay(relay,0);
      }
      if (seconds > 0){
        msg =msg + " after " + (String)seconds;
      }      
      printSuccess(msg);
  }else{
      msg = "Invalid valve number ("+ (String)relay + ")";
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
  Serial.println(message);
}

void toggleRelay(int relay,int relay_voltage){
 if (relay_voltage){
   digitalWrite(myRelays[relay],HIGH);
 }else{
   digitalWrite(myRelays[relay],LOW);
 }
}

int stringToInt(String mystring){
  String msg = mystring+ " to ";
  long n =  mystring.toInt();
  msg = msg + n;
//  Serial.println(msg);
  return n;
}


  
