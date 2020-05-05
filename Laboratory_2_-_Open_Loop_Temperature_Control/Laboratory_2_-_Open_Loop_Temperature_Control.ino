#include <OneWire.h>
#include <DallasTemperature.h>
// constants for DS18B20 temp sensor
#define ds18Sig 4
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ds18Sig);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature tempDS18(&oneWire);
int relay = 2;
int ds18Vcc = 3;
int ds18Gnd = 5;
float temp = 0.0;
float tempTarget = 90.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (relay, OUTPUT);
  pinMode (ds18Vcc, OUTPUT);
  pinMode (ds18Gnd, OUTPUT);
  pinMode (ds18Sig, INPUT);
  digitalWrite(ds18Vcc, HIGH);
  digitalWrite(ds18Gnd, LOW);
}
void loop() {
  temp = readTempDS18();
  Serial.print (tempTarget);
  Serial.print (" ");
  Serial.print (temp);
  //HEAT UP
  if (temp < tempTarget) {
    Serial.println(" HEAT");
    digitalWrite (relay, HIGH);
    delay(100);
    digitalWrite (relay, LOW);
    delay(50);
  }
  //COOL DOWN
  else if (temp > tempTarget) {
    Serial.println(" COOL");
    digitalWrite (relay, LOW);
    delay(100);
  }
  // read the temperature
}
float readTempDS18() {
  tempDS18.requestTemperatures();
  delay(150);
  return tempDS18.getTempCByIndex(0);
}
