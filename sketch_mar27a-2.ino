const int buttonPin0 = 0;    // the number of the pushbutton pin
const int buttonPin1 = 1;
const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int led = 5 ;

// Variables will change:
int a = -1 ;
int ledState = HIGH;         // the current state of the output pin
int buttonState0;             // the current reading from the input pin
int buttonState1;             // the current reading from the input pin
int buttonState2;             // the current reading from the input pin
int buttonState3;             // the current reading from the input pin
int b ;
int pre_a = -1 ;
int lastButtonState0 = LOW;   // the previous reading from the input pin
int lastButtonState1 = LOW;   // the previous reading from the input pin
int lastButtonState2 = LOW;   // the previous reading from the input pin
int lastButtonState3 = LOW;   // the previous reading from the input pin


unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int readingled ;

unsigned long delaytime = 2000 ;
unsigned long lasttime = 0 ;

void setup() {
  Serial.begin(2000000);
  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(led , INPUT) ;
}

void loop() {
  // read the state of the switch into a local variable:
  int reading0 = digitalRead(buttonPin0);
  int reading1 = digitalRead(buttonPin1);
  int reading2 = digitalRead(buttonPin2);
  int reading3 = digitalRead(buttonPin3);
  int readingled = digitalRead(led) ;
  if (readingled == 1 && b == 0)
  { 
    b = 1;
    delay(50);
    Serial.println("A");
    pre_a = -1; 
    a = -1 ;
    }
  else if(readingled == 1 && b== 1)
  {
    b = 1;
    }
  else if(readingled == 0 && b ==0 )
  {
    b = 0;
    }
  else 
  {
    b = 0 ;
    delay(50) ;
    Serial.println("B");
    }
  
    
  // If the switch changed, due to noise or pressing:
  if (reading0 != lastButtonState0 || reading1 != lastButtonState1 || reading2 != lastButtonState2 || reading3 != lastButtonState3 ) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading0 != buttonState0) {
      buttonState0 = reading0;
      if (buttonState0 == HIGH) {
        a=0;
      }
    }
    else if (reading1 != buttonState1) {
      buttonState1 = reading1;

      if (buttonState1 == HIGH) {
        a=1;
      }
    }
    else if (reading2 != buttonState2) {
      buttonState2 = reading2;

      if (buttonState2 == HIGH) {
        a=2;
      }
    }
    else /*(reading3 != buttonState3)*/ {
      buttonState3 = reading3;

      if (buttonState3 == HIGH) {
        a=3;
      }
    }
  }

  lastButtonState0 = reading0;
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;

  
  if(pre_a == a){
      if(lasttime == 0){
          lasttime = millis() ;
        }
      else
        lasttime = lasttime ;
    }
  else{
      lasttime = 0;
    }


  
  if(pre_a != a){
    Serial.println(a);
    }
  else{
    a = a;
    pre_a = pre_a ;
    if((millis() - lasttime) > delaytime) {Serial.println(a); lasttime = 0 ;}
    else {a = a;pre_a = pre_a ;}
    }
    
  pre_a = a ;
}