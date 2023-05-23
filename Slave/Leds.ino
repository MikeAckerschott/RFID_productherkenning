const byte GREEN_LED = 7;
const byte RED_LED = 6;
const byte YELLOW_LED = 5;
const byte BLUE_LED = 4;

byte redLedState = LOW;
byte greenLedState = LOW;
byte yellowLedState = LOW;
byte blueLedState = LOW;

void ledSetup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  digitalWrite(GREEN_LED, greenLedState);
  digitalWrite(RED_LED, redLedState);
  digitalWrite(YELLOW_LED, yellowLedState);
  digitalWrite(BLUE_LED, blueLedState);
}

void setAllLeds(byte state){
  setGreenLed(state);
  setRedLed(state);
  setYellowLed(state);
  setBlueLed(state);
}

byte getRedLedState() {
  return redLedState;
}

byte getBlueLedState() {
  return blueLedState;
}

byte getYellowLedState() {
  return yellowLedState;
}

byte getGreenLedState() {
  return greenLedState;
}

void setGreenLed(byte state) {
  digitalWrite(GREEN_LED, state);
  greenLedState = state;
}

void setRedLed(byte state) {
  digitalWrite(RED_LED, state);
  redLedState = state;
}

void setYellowLed(byte state) {
  digitalWrite(YELLOW_LED, state);
  yellowLedState = state;
}

void setBlueLed(byte state) {
  digitalWrite(BLUE_LED, state);
  blueLedState = state;
}

const byte getRedLed() {
  return RED_LED;
}

const byte getGreenLed() {
  return GREEN_LED;
}

const byte getBlueLed() {
  return BLUE_LED;
}

const byte getYellowLed() {
  return YELLOW_LED;
}