#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <MFRC522.h>

#define SS_PIN 4
#define RST_PIN 5

int pinCS = 9;
int numberOfHorizontalDisplays = 2; // теперь у нас по-горизонтали 6 матриц
int numberOfVerticalDisplays = 4; // а по-вертикали, по-прежнему, одна

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

String tape = "welcome"; // текст, который будет плыть
int wait = 100; // время между крайними перемещениями букв

int spacer = 2; // расстояние между буквами
int width = 5 + spacer; // размер шрифта
void setup() {
 SPI.begin();   // Init SPI bus
 mfrc522.PCD_Init(); // Init MFRC522 card
 Serial.println("Scan PICC to see UID and type...");
  matrix.setIntensity(15); // яркость
        matrix.setRotation(1); 
    matrix.setRotation(0, 2);
    matrix.setRotation(1, 2);
    matrix.setRotation(2, 2);
    matrix.setRotation(3, 2);
    matrix.setRotation(4, 0);
    matrix.setRotation(5, 0);
    matrix.setRotation(6, 0);
    matrix.setRotation(7, 0);
    matrix.setPosition(0, 6, 0);
    matrix.setPosition(3, 0, 0); 
    matrix.setPosition(1, 4, 0);
    matrix.setPosition(6, 5, 0);
    matrix.setPosition(5, 3, 0);  
    matrix.setPosition(4, 1, 0);
  

}

void loop() {
  byte uidCard[4] = {0x45, 0x47, 0xC8, 0x73}; 
  
 if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;
 }

 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;
 }
          
        for (byte i = 0; i < 4; i++) {
          if (uidCard[i] != mfrc522.uid.uidByte[i])
            return;           
        }


        

        
  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
        matrix.fillScreen(LOW);

        int letter = i / width;
        int x = (matrix.width() - 1) - i % width;
        int y = (matrix.height() - 8) / 2; // center the text vertically

        while ( x + width - spacer >= 0 && letter >= 0 ) {
            if ( letter < tape.length() ) {
                matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
            }
            letter--;
            x -= width;
        }

        matrix.write();
        delay(wait);

          Serial.println("OPEN");
  // digitalWrite(); 
  delay(1000);
  // digitalWrite();    
  Serial.println("close");
  // digitalWrite(); 
  delay(1000);
  // digitalWrite();  
    }

}
