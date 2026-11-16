
const int B = 4275;            // B value of the thermistor
const int R0 = 100000;            // R0 = 100k

const int B_2 = 4000;            // B value of the thermistor
const int R0_2 = 10000;            // R0 = 100k

unsigned int edge_counter = 0;


bool STAT = true;
unsigned int counter = 0;
float prev_val = 0;

unsigned long prev_mili = 0;
unsigned long prev_mili_10 = 0;

unsigned long interval = 1000;

//PID values
float PID_integral = 0;
float prev_error = 0;


int pinSignal = 3;

//PID parameters
#define KP  0.1
#define KI  0.0005
#define KD  0.0
#define FAN_PWM 3

#define SELEC_TEMP 25


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
    Serial.println(PID_controller_execution());
      
}

unsigned int PID_controller_execution()
{

    float dt = 0.1; // dt is 100 ms
    int a_second = analogRead(A1);

    float R_2 = (1023.0 / a_second) - 1.0;
    R_2 = R0_2*R_2;
    float temperature_2 = 1.0 / (log(R_2 / R0_2) / B_2 + 1.0 / 298.15) - 273.15;
  
    float error = temperature_2 - SELEC_TEMP;

    float P = KP*error;
    
    PID_integral += dt*(error);

    float I = KI*PID_integral;

    float D = KD*(error - prev_error)/dt;
    prev_error = error;

    unsigned int controller_speed = (unsigned int)min(max(255*(P + I + D),0),255);

    analogWrite(FAN_PWM, controller_speed);

  return controller_speed;

}

void loop() {

    unsigned long currentMillis = millis();
    // collect data every second
    if ((currentMillis - prev_mili) >= interval/10)
    {
      prev_mili = currentMillis;
      collecd_and_send_data();

      edge_counter = 0;

    }
    else if((currentMillis - prev_mili_10)  >= interval / 100)
    {
      prev_mili_10 = currentMillis;

      PID_controller_execution();
    }


    float current = analogRead(A2);
    if(abs(prev_val -  current) > 500)
    {
      edge_counter ++;
    }
    prev_val = current;

    delay(1);
}
