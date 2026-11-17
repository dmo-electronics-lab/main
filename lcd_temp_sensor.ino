#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k

unsigned long prev_mili = 0;
unsigned long interval = 1000;


void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);

  pinMode(A0,INPUT);

  //Note: the lcd code is copied from the example on the grove website
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
    
  lcd.setRGB(colorR, colorG, colorB);
    
  delay(1000);
  Serial.begin(9600);

}

void collecd_and_send_data()
{
    int a = analogRead(A0);

    float R = (1023.0 / a) - 1.0;
    R = R0*R;
    float temperature = 1.0 / (log(R/ R0) / B + 1.0 / 298.15) - 273.15;
    Serial.println(temperature);
    
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(temperature);

    delay(100);
}

void loop() {

    unsigned long currentMillis = millis();
    // collect data every second
    if ((currentMillis - prev_mili) >= interval)
    {
      prev_mili = currentMillis;
      collecd_and_send_data();
    }
    
    delay(1);
} 
