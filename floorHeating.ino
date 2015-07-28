int pumpPin = 8;  

int roomPin[]  = {
  9,10,11};

int thermostatPin[] = {
  2,3,4};
boolean thermostatOn[] = {
  false,false,false};

int buttonPin[] = {
  5,6,7};
long timeDelay = 10000L; //Time in milliseconds  60_000 ms is 1 min
long endTime[] = {
  0,0,0};

int rooms = 3;

boolean controlsAuto = true; 
int controlLedPin = 12; 
int controlButtonPin = A0;

void setup() {

  //Serial.begin(9600);

  //  Setup the pump pin.
  pinMode(pumpPin, OUTPUT);

  //  Setup control led pin.
  pinMode(controlLedPin, OUTPUT);

  // Setup control button pin. 
  pinMode(controlButtonPin, INPUT_PULLUP);

  for(int i = 0;i < rooms;i++){

    // Setup the room pins.
    pinMode(roomPin[i], OUTPUT);

    // Setup the thermostat pins.
    pinMode(thermostatPin[i], INPUT_PULLUP); 

    //Setup the button pins.
    pinMode(buttonPin[i], INPUT_PULLUP); 
  }
}

// the loop function runs over and over again forever
void loop() {

  if(digitalRead(controlButtonPin) == LOW){
    controlsAuto = !controlsAuto;
    for(int i = 0;i < rooms;i++){
      thermostatOn[i] = false;
      endTime[i] = 0;
    }
    delay(400);
  }

  if(controlsAuto){
    checkIfAuto();
  }
  else{
    checkIfManuell();
  }
  checkLed();
}

void checkIfAuto(){
  for(int i = 0;i < rooms;i++){
    if(digitalRead(thermostatPin[i]) == LOW){
      thermostatOn[i] = true;
    }
    else{
      thermostatOn[i] = false;
    }
  }
}

void checkIfManuell(){
  for(int i = 0; i < rooms; i++){
    if(digitalRead(buttonPin[i]) == LOW){
      if(thermostatOn[i]){
        thermostatOn[i] = false;
        endTime[i] = 0;
      }
      else{
        thermostatOn[i] = true;

        long time = timeDelay + millis();

        endTime[i] = time;
      }
      
      delay(400);
    }

    if(endTime[i] < millis()){
      thermostatOn[i] = false;
    }
  }
}

void checkLed(){
  boolean allOf = true;
  for(int i = 0;i < rooms; i++){
    if(thermostatOn[i]){
      digitalWrite(roomPin[i], HIGH);
      allOf = false;
    }
    else{
      digitalWrite(roomPin[i], LOW);
    }
  }
  digitalWrite(pumpPin,!allOf);
  digitalWrite(controlLedPin,controlsAuto);
}
