
#define BUTTONPIN  0

// Button default state.  NC - LOW, NO - HIGH
#define BUTTONDEFAULT LOW
#define DEBOUNCEDELAY 50

int buttonState;
int buttonCurrRead;
int buttonPrevRead;
long debounceStart;
boolean buttonPressed = false;

void setup() {
  pinMode(BUTTONPIN, INPUT);
  pinMode(BUTTONPIN, INPUT_PULLUP);
}

void loop() {

  buttonCurrRead = digitalRead(BUTTONPIN);
  
  // has the button changed states?  If so lets start counting
  if (buttonCurrRead != buttonPrevRead) {
    debounceStart = millis();
  } 
  
  // has out count exceeded our delay? If so change set buttonState
  if ((millis() - debounceStart) > DEBOUNCEDELAY) {
    buttonState = buttonCurrRead;
  }

  // keep track of current read value for next pass
  buttonPrevRead = buttonCurrRead;

  // Is our button state different than our button default and have we sent key press?
  if ((buttonState != BUTTONDEFAULT) && !buttonPressed) {

   //  press USB key(s)
    Keyboard.set_modifier(MODIFIERKEY_GUI);
    Keyboard.set_key1(KEY_L);
    Keyboard.send_now();

    // immediate USB key release. Only do this once, either here or below.
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    
    // keep track if we have sent keypress
    buttonPressed = true;
  }
  
  // if state changes make sure we "unpress" button
  if (buttonState == BUTTONDEFAULT && buttonPressed) {

    // Button is no longer pressed
    buttonPressed = false;
    
    // release USB key when button released. Only this once either here or above
    // Keyboard.set_modifier(0);
    // Keyboard.set_key1(0);
    // Keyboard.send_now();
  }
}
