#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP085.h>
#include "RTClib.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   23
#define OLED_CLK   18
#define OLED_DC    4
#define OLED_CS    5
#define OLED_RESET 15
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

Adafruit_BMP085 bmp;
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

const int pot = 33;
const int atas = 34;
const int bawah = 35;
const int kiri = 36;
const int kanan = 39;
const int leds = 2;

int a = 1;
int menu = 1;


void setup() {
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    for(;;); // Don't proceed, loop forever
  }
  if (!bmp.begin()) {
    while (1) {}
  }
  if (! rtc.begin()) {
    while (1);
  }
  
  display.display();
  delay(1000);
  display.clearDisplay();
  
  pinMode(pot, INPUT);
  pinMode(atas, INPUT);
  pinMode(bawah, INPUT);
  pinMode(kiri, INPUT);
  pinMode(kanan, INPUT);
  pinMode(leds, OUTPUT);
}

void loop() {
  
  int left = digitalRead(kiri);
  int right = digitalRead(kanan);

  if (right == HIGH)
  {
    menu++;
  }
  else if (left == HIGH)
  {
    menu--;
  }

  if (menu > 6){
    menu = 1;
  }
  else if (menu < 1){
    menu = 6;
  }

  display.clearDisplay();

  // Display Text
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(3,0);

  switch (menu) {
  case 1:
    jam();
    break;
  case 2:
    tanggal();;
    break;
  case 3:
    suhu();
    break;
  case 4:
    tekanan();
    break;
  case 5:
    ai();
    break;
  case 6:
    led();
    break;
    
  default:
    // if nothing else matches, do the default
    // default is optional
    break;
  }
  
  
  
  delay(210);

}

void jam(void) {
  DateTime now = rtc.now();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("     <  TIME   >     ");
  display.println("---------------------");
  display.setTextSize(3);
  display.setCursor(10,28);
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.setTextSize(1);
  display.print(':');
  display.println(now.second(), DEC);
  display.setCursor(0,58);
  display.println("    - - - * - - -    ");
  display.display();
}

void tanggal(void) {
  DateTime now = rtc.now();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("     <  DATE   >     ");
  display.println("---------------------");
  display.setTextSize(3);
  //display.setCursor(0,18);
  display.println(daysOfTheWeek[now.dayOfTheWeek()]);
  display.setTextSize(2);
  //display.setCursor(0,43);
  display.print(now.day(), DEC);
  display.print('/');
  display.print(now.month());
  display.print('/');
  display.println(now.year(), DEC);
  display.setTextSize(1);
  display.setCursor(0,58);
  display.println("    - - - - * - -    ");
  display.display();
}

void suhu(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("     <  TEMP   >     ");
  display.println("---------------------");
  display.setTextSize(3);
  display.setCursor(6,28);
  display.print(bmp.readTemperature());
  display.setTextSize(2);
  display.println(" C");
  display.setTextSize(1);
  display.setCursor(0,58);
  display.println("    - - - - - * -    ");
  display.display();
}

void ai(void) {
  int value = analogRead(pot);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("     <  VALUE  >     ");
  display.println("---------------------");
  display.setTextSize(3);
  display.setCursor(27,28);
  display.print(value);
  display.setTextSize(1);
  display.setCursor(0,58);
  display.println("    - - * - - - -    ");
  display.display();
}

void tekanan(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("     <BAROMETER>     ");
  display.println("---------------------");
  display.setTextSize(2);
  display.setCursor(8,28);
  display.print(bmp.readPressure());
  display.println(" Pa");
  display.setTextSize(1);
  display.setCursor(0,58);
  display.println("    - * - - - - -    ");
  display.display();
}

void led(void) {
  int up = digitalRead(atas);
  int down = digitalRead(bawah);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("     <   LED   >     ");
  display.println("---------------------");
  if (up == HIGH)
  {
    a++;
  }
  else if (down == HIGH)
  {
    a--;
  }

  if (a > 2){
    a = 1;
  }
  else if (a < 1){
    a = 2;
  }

  if (a == 2){
    display.setTextSize(3);
    display.setCursor(47,28);
    display.println("ON");
    digitalWrite(leds, HIGH);
  }
  else if (a == 1){
    display.setTextSize(3);
    display.setCursor(40,28);
    display.println("OFF");
    digitalWrite(leds, LOW);
  }
  
  display.setTextSize(1);
  display.setCursor(0,58);
  display.println("    - - * * - - -    ");
  display.display();
}
