#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
                   /* JOYSTICK_DEFAULT_BUTTON_COUNT (32) */ 16,
                   /* JOYSTICK_DEFAULT_HATSWITCH_COUNT (2) */ 0,
                   /* includeXYZAxes */     true, true, true,
                   /* includeRxRyRzAxes */  false, false, false,
                   /* includeThrottle, Accelerator, Brake, Steering */ false, false, false, false);

int lastButtonState[16];
int lastRawButtonState[16];
int currentRawButtonState[16];
int inputType[16];

#define TYPE_BUTTON    0
#define TYPE_ENCODER   1

#define ENCODER_1_CLK  2
#define ENCODER_1_DT   3
#define ENCODER_2_CLK  4
#define ENCODER_2_DT   5

void setup() {
   for (int index=0; index < 16; ++index) {
      inputType[index] = TYPE_BUTTON;
      pinMode(index, INPUT_PULLUP);
      lastButtonState[index] = 0;
      lastRawButtonState[index] = digitalRead(index);
   }
   inputType[ENCODER_1_CLK] = TYPE_ENCODER;
   inputType[ENCODER_1_DT ] = TYPE_ENCODER;
   inputType[ENCODER_2_CLK] = TYPE_ENCODER;
   inputType[ENCODER_2_DT ] = TYPE_ENCODER;

   Joystick.begin();
}

void loop() {
   int currentButtonState;

   // Do the buttons first
   for (int index = 0; index < 16; ++index) {
      currentRawButtonState[index] = digitalRead(index);
      if (inputType[index] == TYPE_BUTTON) {
         currentButtonState = !digitalRead(index);
         if (currentButtonState != lastButtonState[index]) {
            Joystick.setButton(index, currentButtonState);
            lastButtonState[index] = currentButtonState;
         }
      }
   }

   // Handle Analog inputs
   Joystick.setXAxis(analogRead(A0));
   Joystick.setYAxis(analogRead(A1));
   Joystick.setZAxis(analogRead(A2));
   Joystick.setRudder(analogRead(A3));

   // Now for each encoder (note the raw button states were read while handling the buttons
   if ((currentRawButtonState[ENCODER_1_CLK] != lastRawButtonState[ENCODER_1_CLK]) && (currentRawButtonState[ENCODER_1_CLK])) {
      if (currentRawButtonState[ENCODER_1_DT] == HIGH) {
         // CCW: Button press on CLK pin
         currentButtonState = !lastButtonState[ENCODER_1_CLK];
         Joystick.setButton(ENCODER_1_CLK, currentButtonState);
         lastButtonState[ENCODER_1_CLK] = currentButtonState;
         if (lastButtonState[ENCODER_1_DT]) {
             Joystick.setButton(ENCODER_1_DT, 0);
             lastButtonState[ENCODER_1_DT] = 0;
         }
      } else {
         // CW: Button press on DT pin
         currentButtonState = !lastButtonState[ENCODER_1_DT];
         Joystick.setButton(ENCODER_1_DT, currentButtonState);
         lastButtonState[ENCODER_1_DT] = currentButtonState;
         if (lastButtonState[ENCODER_1_CLK]) {
             Joystick.setButton(ENCODER_1_CLK, 0);
             lastButtonState[ENCODER_1_CLK] = 0;
         }
      }
   }
   if ((currentRawButtonState[ENCODER_2_CLK] != lastRawButtonState[ENCODER_2_CLK]) && (currentRawButtonState[ENCODER_2_CLK])) {
      if (currentRawButtonState[ENCODER_2_DT] == HIGH) {
         // CCW: Button press on CLK pin
         currentButtonState = !lastButtonState[ENCODER_2_CLK];
         Joystick.setButton(ENCODER_2_CLK, currentButtonState);
         lastButtonState[ENCODER_2_CLK] = currentButtonState;
         if (lastButtonState[ENCODER_2_DT]) {
             Joystick.setButton(ENCODER_2_DT, 0);
             lastButtonState[ENCODER_2_DT] = 0;
         }
      } else {
         // CW: Button press on DT pin
         currentButtonState = !lastButtonState[ENCODER_2_DT];
         Joystick.setButton(ENCODER_2_DT, currentButtonState);
         lastButtonState[ENCODER_2_DT] = currentButtonState;
         if (lastButtonState[ENCODER_2_CLK]) {
             Joystick.setButton(ENCODER_2_CLK, 0);
             lastButtonState[ENCODER_2_CLK] = 0;
         }
      }
   }

   // transfer raw button state
   for (int index = 0; index < 16; ++index) {
      lastRawButtonState[index] = currentRawButtonState[index];
   }
}
