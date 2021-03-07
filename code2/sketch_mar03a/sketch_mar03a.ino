#include <Stepper.h>

#define SPEED_CHANGE_VALUE 1
#define STEPS 36

int pause_btn = 0;
int v_inc_btn = 1;
int v_dec_btn = 2;
int chdir_btn = 3;

boolean motor_dir = 0;
int motor_speed = 10;
int is_paused = 0;

Stepper stepper(STEPS, 13, 12, 9, 8);
 
void setup()
{
  pinMode(pause_btn, INPUT_PULLUP);
  pinMode(v_inc_btn, INPUT_PULLUP);
  pinMode(v_dec_btn, INPUT_PULLUP);
  pinMode(chdir_btn, INPUT_PULLUP);
}
 
int direction_ = 1, speed_ = 0;
 
void loop()
{
  if ( digitalRead(chdir_btn) == 0 )  // if button is pressed
    if ( debounce() )  // debounce button signal
    {
      direction_ *= -1;  // reverse direction variable
      while ( debounce() );
    }
  control_speed();
  if ( speed_ != motor_speed )
  {
    speed_ = motor_speed;
    stepper.setSpeed(speed_);
  }
//  stepper.step(direction_ * (STEPS / 100));
  if(!is_paused) {
    stepper.step(direction_);
  }
  
}

void control_speed(){
  control_pause();
  if(!digitalRead(v_inc_btn)){
    while(!digitalRead(v_inc_btn));
    motor_speed += SPEED_CHANGE_VALUE;
    if(motor_speed > 100) motor_speed = 100;
  }
  if(!digitalRead(v_dec_btn)){
    while(!digitalRead(v_dec_btn));
    motor_speed -= SPEED_CHANGE_VALUE;
    if(motor_speed < 0) motor_speed = 0;
  }
}

bool debounce() {
  byte count = 0;
  for(byte i = 0; i < 5; i++) {
    if (digitalRead(chdir_btn) == 0)
      count++;
    delay(10);
  }
  if(count > 2)  return 1;
  else           return 0;
}

void control_pause() {
  if(!digitalRead(pause_btn)){
    while(!digitalRead(pause_btn));
    if(is_paused) is_paused = 0;
    else          is_paused = 1;
  }
}