#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2,1,0,4,5,6,7,3, POSITIVE);

int x;

void setup() {
  lcd.begin(20,4);    // Set up display. 20 character in 4 rows
  lcd.clear();        //Clear the display
  lcd.print("hello world!");
  lcd.setCursor(0,1); // Moves to start of second line
  lcd.print("Savo");

  delay(1000);
}

void loop() {
  // Runs an 'x' across the screen
  
  for (int i = 0; i<4; i++){
    for (int j = 0; j<20;j++) {
      lcd.clear();
      lcd.setCursor(j,i);
      lcd.print('x');
      delay(200);
    }
  }

}
