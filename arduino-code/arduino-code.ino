#define SPEED_CHANGE_VALUE 10

int in1 = 11;
int in2 = 10;
int en = 9;

int pause_btn = 0;
int v_inc_btn = 1;
int v_dec_btn = 2;
int chdir_btn = 3;

boolean motor_dir = 0;
int motor_speed = 0;
int is_paused = 0;


void setup() {
  // Set all the motor control pins to outputs
  pinMode(pause_btn, INPUT_PULLUP);
  pinMode(v_inc_btn, INPUT_PULLUP);
  pinMode(v_dec_btn, INPUT_PULLUP);
  pinMode(chdir_btn, INPUT_PULLUP);

  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(en, motor_speed);
}

void loop() {
  control_direction();
  control_speed();
  control_pause();
}

void control_direction(){
    if(!digitalRead(chdir_btn)){                // If direction button is pressed
    while(!digitalRead(chdir_btn));           // Wait until direction button released
    motor_dir = !motor_dir;                // Toggle direction variable
    if(motor_dir){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    }
    else {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW); 
    }
  }
}

void control_speed(){
  if(!digitalRead(v_inc_btn)){
    while(!digitalRead(v_inc_btn));
    motor_speed += SPEED_CHANGE_VALUE;
    analogWrite(en, motor_speed);
  }
  if(!digitalRead(v_dec_btn)){
    motor_speed -= SPEED_CHANGE_VALUE;
    analogWrite(en, motor_speed);
  }
}

void control_pause(){
  if(!digitalRead(pause_btn)){
    while(!digitalRead(pause_btn));
    if(is_paused){
      analogWrite(en, motor_speed);
      is_paused = 0;
    }
    else{
      analogWrite(en, 0);
      is_paused = 1;
    }
  }
}
