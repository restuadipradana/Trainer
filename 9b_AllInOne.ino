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

int pot = 33;
int atas = 34;
int bawah = 35;
int kiri = 36;
int kanan = 39;
String kondisi = "";

void setup() {
  Serial.begin(9600);

  
  pinMode(pot, INPUT); //set pin 33 sebagai input potensiometer
  pinMode(atas, INPUT);
  pinMode(bawah, INPUT);
  pinMode(kiri, INPUT);
  pinMode(kanan, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
 
}

void loop() {

  int value = analogRead(pot); //membaca nilai analog
  int up = digitalRead(atas); //membaca nilai input saat tombol up ditekan
  int down = digitalRead(bawah);
  int left = digitalRead(kiri);
  int right = digitalRead(kanan);
  DateTime now = rtc.now();

  display.clearDisplay();

  // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.println(now.second(), DEC);
  display.println(daysOfTheWeek[now.dayOfTheWeek()]);
  display.print(now.day(), DEC);
  display.print('/');
  display.print(now.month());
  display.print('/');
  display.print(now.year(), DEC);
  display.println();
  display.print("Suhu: ");
  display.print(bmp.readTemperature());
  display.println(" C");
  display.print("Tekanan: ");
  display.print(bmp.readPressure());
  display.println(" Pa");
  display.print("Analog input: ");
  display.println(value);
  display.println("Tombol yang ditekan: ");
  if (up == HIGH)
  {
    kondisi = "UP";
  }
  else if (down == HIGH)
  {
    kondisi = "DOWN";
  }
  else if (left == HIGH)
  { 
    kondisi = "LEFT";
  }
  else if (right == HIGH)
  {  
    kondisi = "RIGHT";
  }

  display.println(kondisi);
  
  display.display();
  delay(250);
  display.clearDisplay();
}
