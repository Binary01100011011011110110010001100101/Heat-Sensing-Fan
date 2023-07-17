#include <LiquidCrystal.h> // Includes Liquid Crystal library, which allows us to use the LCD Display
#define ENABLE 5 // This line and the next two define pins on the Arduino controller board
#define DIRA 3
#define DIRB 4

int i; // Defines variable i
int tempPin = 0; // Defines variable tempPin
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // Defines LCD pins on the controller board
 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2); // sets up the LCD's number of columns and rows:
}

void loop() {
  digitalWrite(ENABLE,HIGH);
  int tempReading = analogRead(tempPin);
  // This is OK
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */
  // Display Temperature in C
  lcd.setCursor(0, 0);
  lcd.print("Temp         F  ");
  // Display Temperature in F
  //lcd.print("Temp         F  ");
  lcd.setCursor(6, 0);
  // Display Temperature in C
  lcd.print(tempF);
  if (tempF>80) {
    digitalWrite(DIRA,HIGH); // Fan speed is high
  }
  else {
    digitalWrite(DIRA,LOW); // Fan speed is low
  }

  delay(500); // This loop updates every half second
}
