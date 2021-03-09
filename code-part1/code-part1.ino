#define PWM_CHANGE_VALUE 10
#define MAX_PWM 255
#define MIN_PWM 0

int in1 = 11;
int in2 = 10;
int en = 9;

int pause_btn = 0;
int v_inc_btn = 1;
int v_dec_btn = 2;
int chdir_btn = 3;

boolean motor_dir = 0;
int current_pwm = MAX_PWM;
int is_paused = 0;


void setup() {
  pinMode(pause_btn, INPUT_PULLUP);
  pinMode(v_inc_btn, INPUT_PULLUP);
  pinMode(v_dec_btn, INPUT_PULLUP);
  pinMode(chdir_btn, INPUT_PULLUP);

  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  set_clock_wise();

  analogWrite(en, MAX_PWM);
}


void loop() {
  control_direction();
  control_speed();
  control_pause();
}

void set_clock_wise(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
}

void set_anti_clock_wise(){
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH);
}

void control_direction(){
    if(!digitalRead(chdir_btn)){
      while(!digitalRead(chdir_btn));
      motor_dir = !motor_dir;
      if(!motor_dir)
        set_clock_wise();
      else 
        set_anti_clock_wise();
  }
}

void control_speed(){
  if(!digitalRead(v_inc_btn)){
    while(!digitalRead(v_inc_btn));
    if(current_pwm + PWM_CHANGE_VALUE >= MAX_PWM){
      current_pwm = MAX_PWM;
    }
    else{
      current_pwm += PWM_CHANGE_VALUE;
    }
    analogWrite(en, current_pwm);
  }
  if(!digitalRead(v_dec_btn)){
    while(!digitalRead(v_dec_btn));
    if(current_pwm - PWM_CHANGE_VALUE <= MIN_PWM){
      current_pwm = MIN_PWM;
    }
    else{
      current_pwm -= PWM_CHANGE_VALUE;
    }
    analogWrite(en, current_pwm);
  }
}

void control_pause(){
  if(!digitalRead(pause_btn)){
    while(!digitalRead(pause_btn));
    if(is_paused){
      if(!motor_dir)
        set_clock_wise();
      else 
        set_anti_clock_wise();
      is_paused = 0;
    }
    else{
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW); 
      is_paused = 1;
    }
  }
}
