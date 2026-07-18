#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonPin = 8;
bool isJumping = false;
int score = 0;
int cactusPos = 15;

// Define custom character for Dino
byte dino[8] = { B00111, B00101, B00111, B00110, B01111, B01110, B01010, B01010 };
// Define custom character for Cactus
byte cactus[8] = { B00100, B00101, B10101, B10111, B11101, B00101, B00100, B00100 };

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Use internal resistor
  lcd.begin(16, 2);
  lcd.createChar(0, dino);
  lcd.createChar(1, cactus);
}

void loop() {
  // Check if button is pressed (LOW because of INPUT_PULLUP)
  if (digitalRead(buttonPin) == LOW) {
    isJumping = true;
  } else {
    isJumping = false;
  }

  // Draw Dino (Top row if jumping, bottom if not)
  lcd.clear();
  if (isJumping) {
    lcd.setCursor(1, 0);
  } else {
    lcd.setCursor(1, 1);
  }
  lcd.write(byte(0));

  // Draw and move Cactus
  lcd.setCursor(cactusPos, 1);
  lcd.write(byte(1));

  // Collision Logic
  if (cactusPos == 1 && !isJumping) {
    lcd.clear();
    lcd.print("GAME OVER!");
    lcd.setCursor(0, 1);
    lcd.print("Score: "); lcd.print(score);
    delay(3000);
    score = 0;
    cactusPos = 15;
  }

  cactusPos--;
  if (cactusPos < 0) {
    cactusPos = 15;
    score++;
  }

  delay(200); // Speed of the game
}
