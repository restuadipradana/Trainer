#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

//pastikan DIP switch untuk button diposisi ON 
int atas = 34;
int bawah = 35;
int kiri = 36;
int kanan = 39;

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  pinMode(atas, INPUT);
  pinMode(bawah, INPUT);
  pinMode(kiri, INPUT);
  pinMode(kanan, INPUT);

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, WHITE);


  display.display();
  delay(2000);
 
}

void loop() {

  int up = digitalRead(atas);
  int down = digitalRead(bawah);
  int left = digitalRead(kiri);
  int right = digitalRead(kanan);

  display.clearDisplay();

  // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Tombol yang ditekan: ");
  if (up == HIGH)
  {
    display.println("UP");
  }
  else if (down == HIGH)
  {
    display.println("DOWN");
  }
  else if (left == HIGH)
  {
    display.println("LEFT");
  }
  else if (right == HIGH)
  {
    display.println("RIGHT");
  }





  display.display();
  delay(150);
  display.clearDisplay();
}
