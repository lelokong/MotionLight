/* Setup Var */
int lightOnTimer = 300; // in seconds, light on time
int lightPin = 8; // pin held low when light is on

// System Var
int turnOn = 0; // hold current light on (1) or off (0)
int timer = 0; // counter when light is activated

void setup() {
  // turn off build in led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // program running at 250 ms delay, so our timer must be multipy by 4 to get 1 second
  lightOnTimer *= 4;
  
  // PIR on pin 2 through 6
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  
  // Physical Light Switch
  pinMode(7, INPUT_PULLUP);

  // Relay pin for light
  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, 1);
}

void loop() {

  // timing for light on
  timer++;

  // use to detect any light on triggers, PIR or light switch
  int trigger = 0;

  // search for high input on pin 2 thourgh 7
  for (int i = 2; i < 5; i++) {
    if (digitalRead(i) == 1) 
      trigger = 1;
  }

 //  light switch
  if (digitalRead(7) == 0)
    trigger = 1;

  // PIR trigger, turn light on, start counting timer from 0
  if (trigger == 1) {
    turnOn = 1;
    timer = 0;    
    digitalWrite(lightPin, 0);
  }
  else if (timer > lightOnTimer && turnOn == 1) {
    turnOn = 0;
    digitalWrite(lightPin, 1);
  }

  delay(250);
}
