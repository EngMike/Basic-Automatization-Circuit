/*
 * Tutorials:
 * https://arduinogetstarted.com/tutorials/arduino-temperature-humidity-sensor-lcd
 * https://arduinogetstarted.com/tutorials/arduino-temperature-humidity-sensor-lcd
 * https://arduinogetstarted.com/tutorials/arduino-4-channel-relay-module
 * https://arduinogetstarted.com/tutorials/arduino-button-relay
 */

#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
#define PIN_RELAY_1  3 // the Arduino pin, which connects to the IN1 pin of relay module
#define PIN_RELAY_2  4 // the Arduino pin, which connects to the IN2 pin of relay module
#define PIN_RELAY_3  5 // the Arduino pin, which connects to the IN3 pin of relay module
#define PIN_RELAY_4  6 // the Arduino pin, which connects to the IN4 pin of relay module
const int BUTTON_PIN_1 = 7; // Button Module 1
const int BUTTON_PIN_2 = 8; // Button Module 2

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x3F, 16 column and 2 rows
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  
  dht.begin();     // initialize the sensor
  lcd.init();      // initialize the lcd
  lcd.backlight(); // open the backlight

  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP); 

  // initialize digital pin as an output for relays
  pinMode(PIN_RELAY_1, OUTPUT);
  pinMode(PIN_RELAY_2, OUTPUT);
  pinMode(PIN_RELAY_3, OUTPUT);
  pinMode(PIN_RELAY_4, OUTPUT);
}

void loop()
{
  delay(500); // wait a few seconds between measurements

  float humi  = dht.readHumidity();    // read humidity
  float tempC = dht.readTemperature(); // read temperature

  lcd.clear();
  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed");
  } else {
    lcd.setCursor(0, 0);  // start to print at the first row
    lcd.print("Temp: ");
    lcd.print(tempC);     // print the temperature
    lcd.print((char)223); // print ° character
    lcd.print("C");

    lcd.setCursor(0, 1);  // start to print at the second row
    lcd.print("Umid: ");
    lcd.print(humi);      // print the humidity
    lcd.print("%");
  }

  // Relay modules button command
   int buttonState1 = digitalRead(BUTTON_PIN_1); // read button 1 state
   int buttonState2 = digitalRead(BUTTON_PIN_2); // read button 2 state
  
  //----Module 1----//
  if (buttonState1 == LOW) {
  digitalWrite(PIN_RELAY_1, HIGH);
  digitalWrite(PIN_RELAY_2, HIGH);
  }
  else
  if (buttonState1 == HIGH) {
  digitalWrite(PIN_RELAY_1, LOW);
  digitalWrite(PIN_RELAY_2, LOW);
  //delay(2000); // delay if necesary
  }
 
  //----Module 2----//
  if (buttonState2 == LOW) {
  digitalWrite(PIN_RELAY_3, HIGH);
  digitalWrite(PIN_RELAY_4, HIGH);
  }
  else
  if (buttonState2 == HIGH) {
  digitalWrite(PIN_RELAY_3, LOW);
  digitalWrite(PIN_RELAY_4, LOW);
  //delay(2000); // delay if necesary
  }
}
