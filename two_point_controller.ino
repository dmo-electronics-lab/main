const int B = 4275;            // B value of the thermistor
const int R0 = 100000;         // R0 = 100k

const int B_2 = 4000;            // B value of the thermistor
const int R0_2 = 10000;          // R0 = 100k

#define FAN_PWM 3

unsigned long prev_mili = 0;

unsigned long interval = 1000;

int pinSignal = 3;

#define TEMP_TH_MIN 24
#define TEMP_TH_MAX 31


void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
    
  digitalWrite(2,HIGH);
  analogWrite(FAN_PWM,0); //fan speed

  Serial.begin(9600);

}


void collecd_and_send_data()
{

    int a = analogRead(A0);
    int a_second = analogRead(A1);

    float R = (1023.0 / a) - 1.0;
    R = R0*R;
    float temperature = 1.0 / (log(R/ R0) / B + 1.0 / 298.15) - 273.15;
    Serial.print(temperature);
    Serial.print("\t ");
    
    float R_2 = (1023.0 / a_second) - 1.0;
    R_2 = R0_2*R_2;
    float temperature_2 = 1.0 / (log(R_2 / R0_2) / B_2 + 1.0 / 298.15) - 273.15;
  
    Serial.print(temperature_2);
    Serial.print("\t ");

    if(temperature_2 >= TEMP_TH_MAX)
    {
        analogWrite(FAN_PWM,255);
        Serial.println(1);
    }
    else if(temperature_2 <= TEMP_TH_MIN)
    {
        analogWrite(FAN_PWM,0);
        Serial.println(0);
    }
}

void loop() {

    unsigned long currentMillis = millis();
    // collect data every second
    if ((currentMillis - prev_mili) >= interval/10)
    {
      prev_mili = currentMillis;
      collecd_and_send_data();

    }

    delay(1);
}
