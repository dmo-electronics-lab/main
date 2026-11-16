const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k

unsigned long prev_mili = 0;
unsigned long interval = 1000;

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);

  pinMode(A0,INPUT);
  
  Serial.begin(9600);

}

void collecd_and_send_data()
{
    int a = analogRead(A0);

    float R = (1023.0 / a) - 1.0;
    R = R0*R;
    float temperature = 1.0 / (log(R/ R0) / B + 1.0 / 298.15) - 273.15;
    Serial.println(temperature);
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
