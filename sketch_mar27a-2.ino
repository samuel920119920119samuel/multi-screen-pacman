const int buttonPin0 = 0;    // the number of the pushbutton pin
const int buttonPin1 = 1;
const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;
const int led = 5 ;

// Variables will change:
int a ;
int ledState = HIGH;         // the current state of the output pin
int buttonState0;             // the current reading from the input pin
int buttonState1;             // the current reading from the input pin
int buttonState2;             // the current reading from the input pin
int buttonState3;             // the current reading from the input pin
int buttonState4;             // the current reading from the input pin
int lastButtonState0 = LOW;   // the previous reading from the input pin
int lastButtonState1 = LOW;   // the previous reading from the input pin
int lastButtonState2 = LOW;   // the previous reading from the input pin
int lastButtonState3 = LOW;   // the previous reading from the input pin
int lastButtonState4 = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int readingled ;
int b = 0;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(led , INPUT) ;
}

void loop() {
  // read the state of the switch into a local variable:
  int reading0 = digitalRead(buttonPin0);
  int reading1 = digitalRead(buttonPin1);
  int reading2 = digitalRead(buttonPin2);
  int reading3 = digitalRead(buttonPin3);
  int reading4 = digitalRead(buttonPin4);
  int readingled = digitalRead(led) ;
  if (readingled == 1)
  { b = 1;
    }
  else
  {
    b = 0 ;
    }
  // If the switch changed, due to noise or pressing:
  if (reading0 != lastButtonState0 || reading1 != lastButtonState1 || reading2 != lastButtonState2 || reading3 != lastButtonState3 || reading4 != lastButtonState4 ) {
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
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      if (buttonState1 == HIGH) {
        a=1;
      }
    }
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      if (buttonState2 == HIGH) {
        a=2;
      }
    }
    if (reading3 != buttonState3) {
      buttonState3 = reading3;

      if (buttonState3 == HIGH) {
        a=3;
      }
    }
    if (reading4 != buttonState4) {
      buttonState4 = reading4;

      if (buttonState4 == HIGH) {
        a=4;
      }
    }
  }


  lastButtonState0 = reading0;
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;
  lastButtonState4 = reading4;
  Serial.println(a);
}
