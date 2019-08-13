int atas = 34;
int bawah = 35;
int kiri = 36;
int kanan = 39; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(atas, INPUT);
  pinMode(bawah, INPUT);
  pinMode(kiri, INPUT);
  pinMode(kanan, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int up = digitalRead(atas);
  int down = digitalRead(bawah);
  int left = digitalRead(kiri);
  int right = digitalRead(kanan);
  if (up == HIGH)
  {
    Serial.println("UP");
  }
  if (down == HIGH)
  {
    Serial.println("DOWN");
  }
  if (left == HIGH)
  {
    Serial.println("LEFT");
  }
  if (right == HIGH)
  {
    Serial.println("RIGHT");
  }
  delay(150);
}
