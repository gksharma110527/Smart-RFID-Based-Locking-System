
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// RFID pins
#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
Servo lockServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Component pins
#define SERVO_PIN 6
#define GREEN_LED 5
#define RED_LED 4
#define BUZZER 3

// Only authorized CARD UID
byte authorizedCard[] = {0x7D, 0xEF, 0x2F, 0x07};

void setup() {
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  lockServo.attach(SERVO_PIN);
  lockServo.write(0);  // Locked position

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Smart RFID Lock");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");

  Serial.println("System Ready");
  delay(2000);

  lcd.clear();
  lcd.print("Scan Your Card");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  // Display scanned UID
  Serial.print("Card UID: ");

  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10)
      Serial.print("0");

    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }

  Serial.println();

  // Check ONLY authorized card
  bool authorized = (rfid.uid.size == 4);

  for (byte i = 0; i < 4 && authorized; i++) {
    if (rfid.uid.uidByte[i] != authorizedCard[i]) {
      authorized = false;
    }
  }

  if (authorized) {
    // ACCESS GRANTED
    Serial.println("ACCESS GRANTED");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    lcd.setCursor(0, 1);
    lcd.print("Welcome!");

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    tone(BUZZER, 1000, 200);

    lockServo.write(90);  // Unlock
    delay(10000);         // Stay unlocked for 10 seconds

    lockServo.write(0);   // Lock again

    digitalWrite(GREEN_LED, LOW);

  } else {
    // ACCESS DENIED
    Serial.println("ACCESS DENIED");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    lcd.setCursor(0, 1);
    lcd.print("Invalid Card");

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    tone(BUZZER, 300, 700);

    delay(1500);

    digitalWrite(RED_LED, LOW);
  }

  lcd.clear();
  lcd.print("Scan Your Card");

  // Stop RFID communication
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(500);
}


