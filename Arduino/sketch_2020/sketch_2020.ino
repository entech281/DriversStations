#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
                   /* JOYSTICK_DEFAULT_BUTTON_COUNT (32) */ 16,
                   /* JOYSTICK_DEFAULT_HATSWITCH_COUNT (2) */ 0,
                   /* includeXYZAxes */     true, true, true,
                   /* includeRxRyRzAxes */  false, false, false,
                   /* includeThrottle, Accelerator, Brake, Steering */ false, false, false, false);

int lastButtonState[16];

void setup() {
   for (int index=0; index < 16; ++index) {
      pinMode(index, INPUT_PULLUP);
      lastButtonState[index] = 0;
   }

   Joystick.begin();
}

void loop() {
   for (int index = 0; index < 16; ++index) {
      int currentButtonState = !digitalRead(index);
      if (currentButtonState != lastButtonState[index]) {
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
