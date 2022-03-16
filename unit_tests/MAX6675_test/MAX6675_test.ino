const byte MAX_SCK = A1;
const byte MAX_CS = 9;
const byte MAX_SO = A0;


void setup() {
  setupMAX6675(MAX_SCK, MAX_CS, MAX_SO);
  Serial.begin(9600);
  Serial.println("\nMAX6675 Test");
}


void loop() {
  Serial.println(readTemperature(MAX_SCK, MAX_CS, MAX_SO));
  delay(1000);
}
