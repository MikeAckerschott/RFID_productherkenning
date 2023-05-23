

byte undetectionCounter;
const byte SS_PIN = 10;
const byte RST_PIN = 9;

String currentUID;

MFRC522 rfid;  // Create instance of the RFID module

void RFID_setup() {
  SPI.begin();
  rfid = MFRC522(SS_PIN, RST_PIN);
  rfid.PCD_Init();  // Initialize the RFID module
  undetectionCounter = 0;
  currentUID = "SETUP";
}

String getCurrentUID() {
  return currentUID;
}

bool isRFIDPresent() {
  bool present = (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial());
  if (present) {
    undetectionCounter = 0;
  } else {
    ++undetectionCounter;
  }
  return present;
}

//must be called after isRFIDPresent;
bool multipleBadgesPresent() {
  bool multipleBadges = rfid.PICC_IsNewCardPresent() && rfid.PICC_IsNewCardPresent();
  rfid.PICC_ReadCardSerial();
  return multipleBadges;
}

String getUID() {
  return "TODO";
}

String getProductName() {  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  rfid.PCD_StopCrypto1();
  String productName = "";
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!rfid.PICC_IsNewCardPresent()) {
    return "NO NEW CARD PRESENT";
  }

  // Select one of the cards
  if (!rfid.PICC_ReadCardSerial()) {
    return "UNABLE TO SELECT CARD";
  }

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(rfid.uid));  //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    return rfid.GetStatusCodeName(status);
  }

  status = rfid.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    return rfid.GetStatusCodeName(status);
  }

  //PRINT FIRST NAME
  for (uint8_t i = 1; i < 16; i++) {
    if (buffer1[i] != 32) {
      char temp = buffer1[i];
      productName += temp;
    }
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  return productName;
}

byte getUndetectionCounter() {
  return undetectionCounter;
}

void setUndetectionCounter(byte newVal) {
  undetectionCounter = newVal;
}

// uint16_t read_card() {
//   uint16_t xor_uid = 0;
//   if (!rfid.PICC_ReadCardSerial()) {  //Okay. This does the same PICC_Select as the previous ReadCardSerial(), but this one fails if there is no card on the reader. Funny.
//     //Seems like we need two Select's in a row to detect card's presence.
//     xor_uid = 0;
//   } else {
//     for (int i = 0; i < rfid.uid.size; i = i + 2) {
//       xor_uid = xor_uid ^ (rfid.uid.uidByte[i] << 8 | rfid.uid.uidByte[i + 1]);
//     }
//   }
//   return xor_uid;
// }