
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 7
#define RST_PIN 6
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

void setup() { 
  // Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  lcd.begin(16, 2); // Init LCD display
}
 
// Init balances
int maxBal = 1500;
int dadBal = 1100;

void loop() {
    // Tell reader to scan the card if there is none detected
    lcd.setCursor(0, 0);
    lcd.print("Scan Card       ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;
    
    String maxString = getHexId(rfid.uid.uidByte, rfid.uid.size); // get the hexadecimal uid
    lcd.setCursor(0, 0);
    lcd.print("                 "); // reset the lcd
    if (maxString == "61 a1 57 10 ") { // if it's Max's card...
      // tell me my balance
      lcd.setCursor(0, 0);
      lcd.print("Max's Balance:");
      lcd.setCursor(0, 1);
      lcd.print(maxBal);
      // charge me for the use of the machine
      maxBal = maxBal - 100;
  } else if (maxString == "52 99 2b 55 ") { // if it's Daddy's card...
      // tell me my balance
      lcd.setCursor(0, 0);
      lcd.print("Dad's Balance:");
      lcd.setCursor(0, 1);
      lcd.print(dadBal);
      // charge me for the use of the machine
      dadBal = dadBal - 100;
  } else {
     lcd.setCursor(0, 0);
     lcd.print("Wrong card!");
  }
  delay(1000); // otherwise it would just go straight back to scan card and you wouldn't be able to read it

  // Halt PICC (no idea what this does but it doesn't work without it so I will roll with it)
  rfid.PICC_HaltA();

  // Stop encryption on PCD (same as above)
  rfid.PCD_StopCrypto1();
}

String maxString;
String hexa;

// just reads the uid and sends it off
String getHexId(byte *buffer, byte bufferSize) {
  maxString = "";
  for (byte i = 0; i < bufferSize; i++) {
    hexa = String(buffer[i], HEX);
    maxString = maxString + hexa + " ";
  }
  return maxString;
}

