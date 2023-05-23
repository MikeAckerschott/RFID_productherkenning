byte lastButtonState = LOW;
const byte BUTTONPIN = 2;


void setupButtons() {
  pinMode(BUTTONPIN, INPUT);
}

//checks if a single button is pressed at currentMillis; if so, sets timeButtonsPressed[buttonNr] to currenttime
bool isButtonPressed() {
  byte buttonState = digitalRead(BUTTONPIN);
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    return (buttonState == LOW);
  }
  return false;
}
