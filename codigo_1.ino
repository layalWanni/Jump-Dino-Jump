// include the library code:
//titulo em cima (50, 10)



// initialize the library with the numbers of the interface pins
#define TFT_DC    7
#define TFT_RST   8 
#define SCR_WD   240
#define SCR_HT   240   // 320 - to allow access to full 240x320 frame buffer
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>
Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);


void setup() {
 
  lcd.init(SCR_WD, SCR_HT);
  lcd.print("rama");
  //lcd.clear();
  delay(1000);
  lcd.fillScreen(BLACK);
  lcd.drawRect(0,0,240,240,BLACK);
  lcd.setTextColor(YELLOW);
  lcd.setTextSize(3.7);
  lcd.setCursor(45,10);
  lcd.println("RUN");
  delay(1000);
  lcd.setTextColor(GREEN);
  lcd.setCursor(93,45);
  lcd.println("DINO");
  delay(1000);
  lcd.setTextColor(RED);
  lcd.setCursor(150,10);
  lcd.println("RUN");
  delay(1000);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2.3);
  lcd.setCursor(65,90);
  lcd.println("-> Jogar");
  delay(1000);
  lcd.setCursor(65,120);
  lcd.println("-> Ranking");
  delay(1000);
  lcd.setCursor(65,150);
  lcd.println("-> Creditos");
  delay(1000);
  lcd.setCursor(65,180);
  lcd.println("-> Sair");
}
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
}
