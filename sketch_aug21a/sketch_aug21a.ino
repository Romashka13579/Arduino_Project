#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 9;
int numberOfHorizontalDisplays = 2; // теперь у нас по-горизонтали 6 матриц
int numberOfVerticalDisplays = 4; // а по-вертикали, по-прежнему, одна

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "welcome"; // текст, который будет плыть
int wait = 100; // время между крайними перемещениями букв

int spacer = 2; // расстояние между буквами
int width = 5 + spacer; // размер шрифта

void setup() {
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


        
    }
}
