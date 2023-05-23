const byte UNDOCKED_STATE = 1;
const byte DOCKING_DETECTED_STATE = 2;
const byte SETUP_STATE = 3;
const byte WORKSTATION_EDITING = 4;
const byte ERROR_DETECTED = 5;
const byte DOCKED_STATE = 6;
const byte AWAIT_DOCKING_CONFIRMATION = 7;
const byte SLEEP = 8;

byte currentState;
byte beforeSleepState;

byte getCurrentState() {
  return currentState;
}

void setupStateMachine() {
  currentState = SETUP_STATE;
  SETUP_STATEEntry();
}

void doStateMachine() {
  switch (getCurrentState()) {
    case UNDOCKED_STATE:
      UNDOCKED_STATEDo();
      if (triggerDockingDetected()) {
        UNDOCKED_STATEExit();
        currentState = DOCKING_DETECTED_STATE;
        DOCKING_DETECTED_STATEEntry();
      }
      break;

    case DOCKING_DETECTED_STATE:
      DOCKING_DETECTED_STATEDo();
      if (triggerUndockingDetected()) {
        DOCKING_DETECTED_STATEExit();
        currentState = UNDOCKED_STATE;
        UNDOCKED_STATEEntry();
      } else if (triggerMultipleReadings()) {
        DOCKING_DETECTED_STATEExit();
        currentState = ERROR_DETECTED;
        //entry of error detected state
        ERROR_DETECTEDEntry();
      } else if (triggerButtonPressed()) {
        DOCKING_DETECTED_STATEExit();
        currentState = AWAIT_DOCKING_CONFIRMATION;
        AWAIT_DOCKING_CONFIRMATIONEntry();
      }

      break;

    case SETUP_STATE:
      SETUP_STATEDo();
      if (triggerStartMessageReceived()) {
        SETUP_STATEExit();
        currentState = UNDOCKED_STATE;
        sendUndockingNotification();
        UNDOCKED_STATEEntry();
      }
      if (triggerButtonPressed()) {
        SETUP_STATEExit();
        currentState = WORKSTATION_EDITING;
        WORKSTATION_EDITINGEntry();
      }
      break;

    case WORKSTATION_EDITING:
      WORKSTATION_EDITINGDo();
      if (triggerWorkspaceEditResponse()) {
        WORKSTATION_EDITINGExit();
        currentState = SETUP_STATE;
        SETUP_STATEEntry();
      }
      break;
    case ERROR_DETECTED:
      if (/*some trigger*/ false) {
        //exit
        //change state
        //entry to new state
      }
      ERROR_DETECTEDDo();
      break;

    case DOCKED_STATE:
      //DOCKED_STATEDo()
      if (triggerButtonPressed()) {
        DOCKED_STATEExit();
        currentState = UNDOCKED_STATE;
        UNDOCKED_STATEEntry();
      }
      break;

    case AWAIT_DOCKING_CONFIRMATION:
      AWAIT_DOCKING_CONFIRMATIONDo();

      if (triggerDockingAcknowledged()) {
        AWAIT_DOCKING_CONFIRMATIONExit();
        currentState = DOCKED_STATE;
        DOCKED_STATEEntry();
      } else if (triggerDockingCancelled()) {
        AWAIT_DOCKING_CONFIRMATIONExit();
        currentState = UNDOCKED_STATE;
        UNDOCKED_STATEEntry();
      }
      break;
  }
}

void SETUP_STATEExit() {
  // setupCAN_Messages();
  setRedLed(LOW);
  setGreenLed(LOW);
  setYellowLed(LOW);
  setBlueLed(LOW);
}

void SETUP_STATEDo() {
  if (isTimerDone(getBLINK_DELAY(), getblinkLastMillis())) {

    setblinkLastMillis(millis());
    setBlueLed(!getBlueLedState());

    // Serial.println(getblinkLastMillis());
  }
}

void WORKSTATION_EDITINGExit() {
  byte currentWS = EEPROM.read(getWORKSTATION_EEPROM_ADDR());
  if (currentWS != getStoredWorkstation()) {
    EEPROM.write(getWORKSTATION_EEPROM_ADDR(), getStoredWorkstation());
  }

  setStoredWorkstation(EEPROM.read(getWORKSTATION_EEPROM_ADDR()));
  // setupCAN_Messages();
  setRedLed(LOW);
  setGreenLed(LOW);
  setYellowLed(LOW);
  setBlueLed(LOW);
}

void SETUP_STATEEntry() {
  Serial.println("SETUP_STATE ENTRY");
  setGreenLed(LOW);
  setRedLed(LOW);
}

void WORKSTATION_EDITINGEntry() {

  Serial.println("WORKSTATION_EDITING ENTRY");
  struct can_frame requestNewWorkstation;
  requestNewWorkstation.can_dlc = 0;

  unsigned long ID = 0;
  byte ws = EEPROM.read(getWORKSTATION_EEPROM_ADDR());
  byte msgType = MSG_WS_REQUEST;

  ByteToLong bt;
  bt.byte[0] = ws;
  bt.byte[1] = msgType;

  requestNewWorkstation.can_id = (CAN_EFF_FLAG | bt.myLong);
  mcp2515.sendMessage(&requestNewWorkstation);
}

void UNDOCKED_STATEEntry() {
  setRedLed(HIGH);
  Serial.println("UNDOCKED");

  // setGreenLed(LOW);
  // setRedLed(HIGH);
}

void UNDOCKED_STATEDo() {
}

void UNDOCKED_STATEExit() {
  setRedLed(LOW);
  setGreenLed(LOW);
  setYellowLed(LOW);
  setBlueLed(LOW);
}

void DOCKING_DETECTED_STATEEntry() {
  setYellowLed(HIGH);
  Serial.println("DOCKING DETECTED ENTRY");
}

void DOCKING_DETECTED_STATEDo() {
  isRFIDPresent();
}

void DOCKING_DETECTED_STATEExit() {
  setRedLed(LOW);
  setGreenLed(LOW);
  setYellowLed(LOW);
  setBlueLed(LOW);
}

void ERROR_DETECTEDDo() {
  if (isTimerDone(getBLINK_DELAY(), getblinkLastMillis())) {

    setblinkLastMillis(millis());
    setRedLed(!getRedLedState());

    // Serial.println(getblinkLastMillis());
  }
}

void WORKSTATION_EDITINGDo() {
  if (isTimerDone(getBLINK_DELAY(), getblinkLastMillis())) {

    setblinkLastMillis(millis());
    setBlueLed(!getBlueLedState());
    setYellowLed(!getYellowLedState());

    // Serial.println(getblinkLastMillis());
  }
}

bool triggerDockingDetected() {
  return isRFIDPresent();
}

bool triggerUndockingDetected() {
  return getUndetectionCounter() > 10;
}

bool triggerStartMessageReceived() {
  return isStartMessage();
}

bool triggerButtonPressed() {
  return isButtonPressed();
}



bool triggerMultipleReadings() {
  return multipleBadgesPresent();
}

bool triggerWorkspaceEditResponse() {
  struct can_frame response;

  if (mcp2515.readMessage(&response) == MCP2515::ERROR_OK) {

    ByteToLong bt;
    bt.myLong = response.can_id;

    byte ws = bt.byte[0];
    MSG_TYPE type = bt.byte[1];

    if (ws == 0 && type == MSG_WS_RESPONSE) {
      setStoredWorkstation(response.data[0]);
      return true;
    }
  }
  return false;
}

void DOCKED_STATEEntry() {
  Serial.println("DOCKED");

  setGreenLed(HIGH);
}

void DOCKED_STATEExit() {
  setRedLed(LOW);
  setGreenLed(LOW);
  setYellowLed(LOW);
  setBlueLed(LOW);
  sendUndockingNotification();
}

void ERROR_DETECTEDEntry() {
  Serial.println("DETECTED ERROR STOPPED SLAVE");
  Serial.println(currentState);
}

void AWAIT_DOCKING_CONFIRMATIONEntry() {
  Serial.println("AWAIT_DOCKING_CONFIRMATIONEntry");
  sendDockingMessage(getProductName());
}

void AWAIT_DOCKING_CONFIRMATIONDo() {
  readAndBuffer();

  if (isTimerDone(getBLINK_DELAY(), getblinkLastMillis())) {
    setblinkLastMillis(millis());
    setGreenLed(!getGreenLedState());
  }
}

void AWAIT_DOCKING_CONFIRMATIONExit() {
  getBuffer()->can_dlc = 0;
  getBuffer()->can_id = 0;

  setRedLed(LOW);
  setGreenLed(LOW);
  setYellowLed(LOW);
  setBlueLed(LOW);
}

bool triggerDockingAcknowledged() {
  struct message msg;
  getMessageInfo(&msg, getBuffer());
  return (msg.type == MSG_DOCKING_SUCCESFUL && msg.ws == 0 && msg.canMsg.data[0] == getStoredWorkstation());
}

bool triggerDockingCancelled() {
  struct message msg;
  getMessageInfo(&msg, getBuffer());
  return (msg.type == MSG_DOCKING_CANCELLED && msg.ws == 0 && msg.canMsg.data[0] == getStoredWorkstation());
}