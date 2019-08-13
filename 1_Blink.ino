void setup() {
  pinMode(2, OUTPUT); //inisialisasi pin 2 sebagai output
}

void loop() {
  digitalWrite(2, HIGH);    //menyalakan LED pada pin no 2 (HIGH yaitu level tegangan)
  delay(1000);              //jeda 1000 mili second (1 detik)
  digitalWrite(2, LOW);     //mematikan LED pada dengan mengubah level tegangan ke LOW
  delay(1000);
}
