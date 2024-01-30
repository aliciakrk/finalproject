#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define I2C_ADDR 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS 4

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

const byte ROW_NUM    = 4; 
const byte COLUMN_NUM = 4; 

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};  
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2};  

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Guess the number");
  lcd.setCursor(0, 1);
  lcd.print("1. Easy");
  lcd.print("             ");  
  lcd.print("2. Medium");
  delay(2000);

  lcd.clear();
  lcd.print("3. Dificult"); 
  lcd.print("         "); 
  lcd.print("4. Finish");
  delay(2000);
  lcd.clear();
}

void play(int dificulty) {
  lcd.clear();
  lcd.print("Dificulty: ");

  switch (dificulty) {
    case 1:
      lcd.print("Easy");
      break;
    case 2:
      lcd.print("Medium");
      break;
    case 3:
      lcd.print("Dificult");
      break;
  }

  delay(1000);
  lcd.clear();

  int random_number = random(1, 11);
  int user_try = 0;

  lcd.setCursor(0, 0);
  lcd.print("Your number:");

  while (1) {
    lcd.setCursor(0, 1);
    lcd.print("              ");  
    lcd.setCursor(0, 1);

    char key = keypad.getKey();
    if (key) {
      if (key >= '0' && key <= '9') {
        user_try = user_try * 10 + (key - '0');
        lcd.print(key);
      } else if (key == '#') {
        // Verify the try of the user
        if (user_try == random_number) {
          lcd.clear();
          lcd.print("You guessed it!");
          delay(2000);
          lcd.clear();
          break;
        } else {
          lcd.print("Try again");
          delay(1000);
          lcd.setCursor(0, 1);
          lcd.print("              ");  
          user_try = 0;
        }
      } else if (key == '*') {
        lcd.clear();
        lcd.print("You gave up");
        delay(2000);
        lcd.clear();
        lcd.print("Correct number:");
        lcd.setCursor(0, 1);
        lcd.print(random_number);
        delay(2000);
        lcd.clear();
        break;
      }
    }
  }
}

void loop() {
  int option;

  lcd.setCursor(0, 0);
  lcd.print("Select level:");

  // Read option of the user
  while (1) {
    lcd.setCursor(0, 1);
    lcd.print("              ");  
    lcd.setCursor(0, 1);

    char key = keypad.getKey();
    if (key) {
      option = key - '0';  // Convert caracter to number
      // Verify the option
      if (option >= 1 && option <= 3) {
        play(option);
        break;
      } else if (option == 4) {
        lcd.clear();
        lcd.print("Good bye!");
        delay(2000);
        lcd.clear();
        while (1) {}  
      } else {
        lcd.print("Invalid option");
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.print("              ");  
      }
    }
  }
}
