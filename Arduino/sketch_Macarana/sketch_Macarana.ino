#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
        JOYSTICK_DEFAULT_BUTTON_COUNT, JOYSTICK_DEFAULT_HATSWITCH_COUNT,
        /* includeXYZAxes */ true, true, true,
        /* includeRxRyRzAxes */ false, false, false,
        /* includeThrottle, Accelerator, Brake, Steering */ false, false, false, false);

void setup() {
  // put your setup code here, to run once:
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
    
  Joystick.begin();
}

int lastButtonState[13] = {0,0,0,0,0,0,0,0,0,0,0,0};

void loop() {
  // put your main code here, to run repeatedly:
  for (int index = 0; index < 13; index++)
  {
    int currentButtonState = !digitalRead(index);
    if ((index == 12) || (lastButtonState[index-1])) {
      currentButtonState = !currentButtonState;
    }
    if ((index == 10) || (lastButtonState[index-1])) {
      currentButtonState = !currentButtonState;
    }
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
