int buzzerr = 32;

void setup() {
  pinMode(buzzerr, OUTPUT); //inisialisasi pin 2 sebagai output
}

void loop() {
  digitalWrite(buzzerr, HIGH);    //buzzer berbunyi
  delay(1000);              //berbunyi selama 1 detik
  digitalWrite(buzzerr, LOW);     //buzzer mati
  delay(1000);
}
