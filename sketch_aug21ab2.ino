#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <MFRC522.h>

#define RST_PIN 5
#define SS_PIN 4
int pinCS = 9;
int numberOfHorizontalDisplays = 2;
int numberOfVerticalDisplays = 4;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int wait = 100;

int spacer = 2; // расстояние между буквами
int width = 5 + spacer; // размер шрифта

MFRC522 mfrc522(SS_PIN, RST_PIN);

unsigned long uidDec, uidDecTemp;  // для храниения номера метки в десятичном формате

void setup() {
  Serial.begin(9600);
  Serial.println("Waiting for card...");
  SPI.begin(); // инициализация SPI / Init SPI bus.
  mfrc522.PCD_Init(); // инициализация MFRC522 / Init MFRC522І
  matrix.setIntensity(5); // яркость
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
  // Поиск новой метки
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Выбор метки
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  uidDec = 0;
  // Выдача серийного номера метки.
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec * 256 + uidDecTemp;
  }
  Serial.println("Card UID: ");
  Serial.println(uidDec); // Выводим UID метки в монитор порта
  if (uidDec == 1717958175) // Сравниваем Uid метки, если он равен заданному, то загорается зеленый светодиод, иначе красный
  {
    String tape = "Welcome home)";
    for ( int i = 0 ; i < width * tape.length() + matrix.width() - spacer; i++ ) {
      matrix.fillScreen(LOW);

      int letter = i / width;
      int x = (matrix.width() - 1) - i % width;
      int y = (matrix.height() - 6) / 2; // center the text vertically

      while ( x + width - spacer >= 0 && letter >= 0 ) {
        if ( letter < tape.length() ) {
          matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
        }
        letter--;
        x -= width;
      }

      matrix.write();
      delay(wait);
    }
  }
  else if (uidDec == 1162332275) // Сравниваем Uid метки, если он равен заданному, то загорается зеленый светодиод, иначе красный
  {
    String tape = "Hello friend)";
    for ( int i = 0 ; i < width * tape.length() + matrix.width() - spacer; i++ ) {
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
    }
  }
  else {
    return;
  }
  delay(1000);
}
