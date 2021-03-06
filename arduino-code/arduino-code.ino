int in1 = 11;
int in2 = 10;
int en = 9;

int stop_btn = 0;
int v_inc_btn = 1;
int v_dec_btn = 2;
int chdir_btn = 3;

boolean motor_dir = 0;
int motor_speed = 0;


void setup() {
  // Set all the motor control pins to outputs
  pinMode(stop_btn, INPUT_PULLUP);
  pinMode(v_inc_btn, INPUT_PULLUP);
  pinMode(v_dec_btn, INPUT_PULLUP);
  pinMode(chdir_btn, INPUT_PULLUP);

  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(en, 100);

}

void loop() {
  if(!digitalRead(stop_btn)){                // If direction button is pressed
    while(!digitalRead(stop_btn));           // Wait until direction button released
    motor_dir = !motor_dir;                // Toggle direction variable
    if(motor_dir)
      digitalWrite(in2, LOW);
    else
      digitalWrite(in1, LOW);
  }
}
