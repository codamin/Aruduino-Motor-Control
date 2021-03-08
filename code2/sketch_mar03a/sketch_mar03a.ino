#include <Stepper.h>
#define STEPS 36

int pause_btn = 0;
int clw_btn = 1;
int cclw_btn = 2;

boolean motor_dir = 0;
int motor_speed = 8;
int is_paused = 0;

Stepper stepper(STEPS, 13, 12, 9, 8);
void setup()
{
  pinMode(pause_btn, INPUT_PULLUP);
  pinMode(clw_btn, INPUT_PULLUP);
  pinMode(cclw_btn, INPUT_PULLUP);
stepper.setSpeed(motor_speed);
}

int direction_ = -1, speed_ = 0;
 
void loop()
{
  if(!digitalRead(clw_btn)) {
    while(!digitalRead(clw_btn));
    direction_ = -1;
    is_paused = 0;
  }
  if(!digitalRead(cclw_btn)) {
    while(!digitalRead(cclw_btn));
    direction_ = 1;
    is_paused = 0;
  }
  control_pause();
  if(!is_paused)  stepper.step(direction_);
}

void control_pause() {
  if(!digitalRead(pause_btn)){
    while(!digitalRead(pause_btn));
    is_paused = 1;
  }
}
