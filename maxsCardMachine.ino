
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
  lcd.begin(16, 2);
}
 

int maxBal = 1500;
int dadBal = 1100;

void loop() {
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

    String maxString = getHexId(rfid.uid.uidByte, rfid.uid.size);
    lcd.setCursor(0, 0);
    lcd.print("                 ");
    if (maxString == "61 a1 57 10 ") {
      lcd.setCursor(0, 0);
    lcd.print("Max's Balance:");
    lcd.setCursor(0, 1);
    lcd.print(maxBal);
    maxBal = maxBal - 100;
  } else if (maxString == "52 99 2b 55 ") {
    lcd.setCursor(0, 0);
    lcd.print("Dad's Balance:");
    lcd.setCursor(0, 1);
    lcd.print(dadBal);
    dadBal = dadBal - 100;
  } else {
    lcd.setCursor(0, 0);
     lcd.print("Wrong card!");
  }
  delay(1000);

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

String maxString;
String hexa;
/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
String getHexId(byte *buffer, byte bufferSize) {
    maxString = "";
  for (byte i = 0; i < bufferSize; i++) {
    // Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    // Serial.print(buffer[i], HEX);
    // lcd.print(buffer[i] < 0x10 ? " 0" : " ");
    // lcd.print(buffer[i], HEX);
    hexa = String(buffer[i], HEX);
    maxString = maxString + hexa + " ";
  }
  return maxString;
}

