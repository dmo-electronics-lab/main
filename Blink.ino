bool toggle = false; //Flag for the current LED status
void setup() {  
  pinMode(LED_BUILTIN, OUTPUT); 
}

void loop() {
  digitalWrite(LED_BUILTIN, toggle); //Toggle the digital pin
  toggle != toggle;
  delay(500);       //wait 500ms s.t. a period is 1 secont -> corresponds to 1Hz   
}
