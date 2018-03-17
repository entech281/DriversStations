#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
        JOYSTICK_DEFAULT_BUTTON_COUNT, JOYSTICK_DEFAULT_HATSWITCH_COUNT,
        /* includeXYZAxes */ true, true, true,
        /* includeRxRyRzAxes */ false, false, false,
        /* includeThrottle, Accelerator, Brake, Steering */ false, false, false, false);

#define NUM_BUTTONS 13
int lastButtonState[NUM_BUTTONS];

void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<NUM_BUTTONS; i++) {
      pinMode(i, INPUT_PULLUP);
      lastButtonState[i] = 0;
  }    
  Joystick.begin();
}


void loop() {
  // put your main code here, to run repeatedly:
  for (int index = 0; index < 13; index++)
  {
    int currentButtonState = !digitalRead(index);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  Joystick.setXAxis(analogRead(A0));
  Joystick.setYAxis(analogRead(A1));
  Joystick.setZAxis(analogRead(A2));
  Joystick.setRudder(analogRead(A3));

  delay(10);
}
