#define pot 33

void setup()
{
  Serial.begin(9600);  // inisialisasi baud rate serial monitor
  pinMode(pot, INPUT); //set pin 33 sebagai input potensiometer
}

void loop()
{
  int value = analogRead(pot); //membaca nilai analog
  Serial.println(value);       //mencetak nilai analog input ke serial monitor
  delay(300);
}
