   
#define FAN_PWM 3

unsigned int edge_counter = 0;

void setup() {

  pinMode(FAN_PWM,OUTPUT);
  analogWrite(FAN_PWM,255); //fan speed

  pinMode(A2,INPUT);

  Serial.begin(9600);

}


void collecd_and_send_data()
{
    Serial.println(edge_counter*600);
      
}

unsigned long prev_mili =0;
unsigned long interval = 100;

float prev_val = 0;
float current = 0;


void loop() {

    unsigned long currentMillis = millis();
    // collect data every 100ms
    if ((currentMillis - prev_mili) >= interval)
    {
      prev_mili = currentMillis;

      collecd_and_send_data();
     
      edge_counter = 0;

    }
   

    float current = analogRead(A2);
    if(abs(prev_val -  current) > 500)
    {
      edge_counter ++;
    }
    prev_val = current;

    delay(1);
}
