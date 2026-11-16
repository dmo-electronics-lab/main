bool toggle = false; //Flag for the current LED status
void setup() {
  pinMode(2, OUTPUT); 
}

void loop() {
  digitalWrite(ledPin, toggle); //Toggle the digital pin
  toggle != toggle;
  delay(500);       //wait 500ms s.t. a period is 1 secont -> corresponds to 1Hz   
}
