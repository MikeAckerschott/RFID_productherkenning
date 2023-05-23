MCP2515 mcp2515(8);

const byte WORKSTATION_EEPROM_ADDR = 0;
const short WORKSTATION_CAN_ID = 256;

byte storedWorkstation;  //ID of workstation stored in EEPROM of the controller
struct can_frame buffer;

enum MSG_TYPE {
  MSG_START = 0,
  MSG_WS_REQUEST = 1,
  MSG_WS_RESPONSE = 2,
  MSG_DOCKED_SENDING = 3,
  MSG_DOCKED_DONE = 4,
  MSG_UNDOCKED = 5,
  MSG_DOCKING_CANCELLED = 6,
  MSG_DOCKING_SUCCESFUL = 7
};

union ByteToLong {
  byte byte[4];
  long myLong;
};

struct message {
  struct can_frame canMsg;
  __u8 ws;
  MSG_TYPE type;
};


void sendMessage(uint8_t ws, byte type, byte **data, byte length)
{
    struct can_frame startMsg;
    startMsg.can_dlc = length;
    ByteToLong bt;

    bt.byte[0] = ws;
    bt.byte[1] = type;
    bt.byte[2] = 0;
    bt.byte[3] = 0;

    for (int i = 0; i < length; ++i)
    {
        startMsg.data[i] = data;
        ++data;
    }

    startMsg.can_id = CAN_EFF_FLAG | bt.myLong;

    mcp2515.sendMessage(&startMsg);
}


bool getMessageInfo(struct message* pMessage, struct can_frame* msg) {
    ByteToLong bt;
    bt.myLong = CAN_EFF_FLAG | msg->can_id;
    bt.byte[3] &= ~(1UL << 8);  //flip first 3 bits to low; these bits are used for error detection in mcp2515 library
    bt.byte[3] &= ~(1UL << 7);
    bt.byte[3] &= ~(1UL << 6);

    pMessage->ws = bt.byte[0];
    pMessage->type = bt.byte[1];
    pMessage->canMsg = *msg;
}

void CAN_setup() {
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();

  storedWorkstation = EEPROM.read(WORKSTATION_EEPROM_ADDR);
}

void setupCAN_Messages() {
  storedWorkstation = EEPROM.read(WORKSTATION_EEPROM_ADDR);
}

const byte getStoredWorkstation() {
  return storedWorkstation;
}

void sendUndockingNotification() {

  ByteToLong bt;
  byte workstation = getStoredWorkstation();
  bt.byte[0] = storedWorkstation;
  bt.byte[1] = MSG_UNDOCKED;

  struct can_frame undockedMsg;
  undockedMsg.can_dlc = 0;
  undockedMsg.can_id = CAN_EFF_FLAG | bt.myLong;

  mcp2515.sendMessage(&undockedMsg);
}

void sendDockingMessage(String productname) {
  int totalMessages = productname.length() / 8 + 1;  //only 8 chars inside can body
  for (int i = 0; i < totalMessages; ++i) {
    struct can_frame msg;
    createDockingMessage(productname, i, &msg, (i == (totalMessages - 1)));
    mcp2515.sendMessage(&msg);
  }
}

void createDockingMessage(String productname, byte messageNr, struct can_frame* msg, bool isFinalMessage) {
  Serial.println(productname);
  String messageString = productname.substring(messageNr * 8, (messageNr + 1) * 8);  //split string in parts of 8 or less
  msg->can_dlc = messageString.length();
  for (int j = 0; j < messageString.length(); ++j) {
    msg->data[j] = messageString.charAt(j);
  }
  ByteToLong bt;
  bt.byte[0] = getStoredWorkstation();
  if (isFinalMessage) {
    bt.byte[1] = MSG_DOCKED_DONE;
  } else {
    bt.byte[1] = MSG_DOCKED_SENDING;
  }
  msg->can_id = bt.myLong;
}

String readStringFromMessage(struct can_frame* receivedMessage) {
  String messageBody;
  for (int i = 0; i < receivedMessage->can_dlc; ++i) {
    messageBody += (char)receivedMessage->data[i];
  }
  // Serial.println(messageBody);
  return messageBody;
}

bool isStartMessage() {
  struct can_frame receivedMessage;
  struct message msg;
  if (mcp2515.readMessage(&receivedMessage) == MCP2515::ERROR_OK) {
    getMessageInfo(&msg, &receivedMessage);

    return msg.ws == 0 && msg.type == MSG_START;
  }
  return false;
}

void readAndBuffer() {
  mcp2515.readMessage(&buffer);
}

struct can_frame* getBuffer() {
  return &buffer;
}

void setStoredWorkstation(byte newval) {
  storedWorkstation = newval;
}

const int getWORKSTATION_CAN_ID() {
  return WORKSTATION_CAN_ID;
}

const int getWORKSTATION_EEPROM_ADDR() {
  return WORKSTATION_EEPROM_ADDR;
}