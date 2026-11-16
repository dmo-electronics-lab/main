bool STAT = true;
unsigned int counter = 0;
float prev_val = 0;

unsigned long prev_mili = 0;
unsigned long prev_mili_10 = 0;

unsigned long interval = 1000;


//distance stuff
int pinSignal = 3;
long duration;
long distanceCm;


//PID values
float PID_integral = 0;
float prev_error = 0;
float sel_val = 15;



//PID parameters
#define KP  0.2
#define KI  0
#define KD  0.0
#define FAN_PWM 3
#define MAG 2


void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(MAG,OUTPUT);


  pinMode(A1,OUTPUT);
  pinMode(A2,INPUT);

  digitalWrite(LED_BUILTIN,HIGH);
  analogWrite(FAN_PWM,255); //fan speed

  analogWrite(A1,255);

  Serial.begin(9600);

}

unsigned int measureDistance()
{

  pinMode(pinSignal, OUTPUT);
  digitalWrite(pinSignal, LOW);
  delayMicroseconds(2);
  digitalWrite(pinSignal, HIGH);
  delayMicroseconds(5); 
  digitalWrite(pinSignal, LOW);

  pinMode(pinSignal, INPUT);
  
  duration = pulseIn(pinSignal, HIGH);

  distanceCm = duration*10 / 29 / 2;

  return distanceCm;
  
}


void collecd_and_send_data()
{

    PID_controller_execution();
      
}

unsigned int PID_controller_execution()
{

    float dt = 0.1; // dt is 100 ms
 
    float dist = 100;
    float error =  dist - sel_val;

    Serial.print(analogRead(A2));
    Serial.println("\t ");

    float P = KP*error;
    
    PID_integral += dt*(error);

    float I = KI*PID_integral;

    float D = KD*(error - prev_error)/dt;
    prev_error = error;

    //Serial.print(error);
    //Serial.print("\t");

    unsigned int Magnet_PWM = (unsigned int)min(max(255*(P + I + D),0),255);

    analogWrite(MAG, Magnet_PWM);

  return Magnet_PWM;

}

void loop() {

    unsigned long currentMillis = millis();
    // collect data every second
    if ((currentMillis - prev_mili) >= interval/100)
    {
      prev_mili = currentMillis;
      collecd_and_send_data();

      
    }
    delay(1);
}
