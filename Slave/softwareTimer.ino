unsigned long readRFIDLastMillis;
unsigned long canIdCheckLastMillis;
unsigned long blinkLastMillis;

const short RFID_READ_DELAY = 20;
const short CAN_ID_CHECK_DELAY = 5000;
const short BLINK_DELAY = 500;

bool isTimerDone(int waitTime, long type) {
  long currentMillis = millis();
  return (currentMillis > type + waitTime);
}

void softwareTimerSetup() {
  readRFIDLastMillis = 0;
  canIdCheckLastMillis = 0;
  blinkLastMillis = 0;
}

const short getBLINK_DELAY() {
  return BLINK_DELAY;
}

unsigned long getblinkLastMillis() {
  return blinkLastMillis;
}

void setblinkLastMillis(unsigned long newval) {
  blinkLastMillis = newval;
}

unsigned long getReadRFIDLastMillis() {
  return readRFIDLastMillis;
}

short getRFID_READ_DELAY() {
  return RFID_READ_DELAY;
}

void setReadRFIDLastMillis(unsigned long newval) {
  readRFIDLastMillis = newval;
}

void setCanIdCheckLastMillis(unsigned long newval) {
  canIdCheckLastMillis = newval;
}

unsigned long getCanIdCheckLastMillis() {
  return canIdCheckLastMillis;
}

const short getCAN_ID_CHECK_DELAY() {
  return CAN_ID_CHECK_DELAY;
}
