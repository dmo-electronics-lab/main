
bool t_1 = false; //Toggle flag for LED 1
bool t_2 = false; // Toggle flag for LED 2

#define INT_32_MAX 2147483647 //Maximum value a 32-bit integer can have

unsigned long interval_1 = 500; // interval 1 is 500ms -> corresponds to 1Hz
unsigned long interval_2 = 100; // interval 2 is 100ms -> corresponds to 5Hz
unsigned long prev_mili_1 = 0;
unsigned long prev_mili_2 = 0;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
}

void loop() {
    unsigned long currentMillis = millis();
    //every 500ms this if statements should evaluate to true once. Using this system the main loop is not blocked for extended periods of time
    if ((currentMillis - prev_mili_1) >= interval_1 )
    {
        digitalWrite(2,t_1);
        t_1 = !t_1;
        prev_mili_1 = currentMillis;
    }
    //This inverval should evaluate to true once every 100ms
    if((currentMillis - prev_mili_2)  >= interval_2)
    {
        digitalWrite(3,t_2);
        t_2 = !t_2;
        prev_mili_2 = currentMillis;

    } 

    if(millis() == INT_32_MAX ) //check if the timer is about to overflow
    {
    //resset the milisecond counter
        prev_mili_1 = 0;
        prev_mili_2 = 0;
    }
    delay(1);
}
