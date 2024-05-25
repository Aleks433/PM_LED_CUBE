const uint8_t input_pin = 2;
const uint8_t display_data_pin = 3;
const uint8_t display_latch_pin = 4;
const uint8_t display_clock_pin = 5;
uint8_t led_state = LOW;
uint8_t numbers_dot[] = {191, 134, 219, 207, 230, 237, 253, 135, 255, 239};
uint8_t numbers[] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
uint8_t digits[] = {14, 13, 11, 7, 0};
uint8_t led_anodes[] = {6, 7, 8};
uint8_t led_cathodes[] = {9, 10, 11, 12, 13, A0, A1, A2, A3};
int digit = 0;
int number = 0;
uint16_t buffer;
double timer = 0;
unsigned long start_time;

void setup() {
  // put your setup code here, to run once:
  // pinMode(led_pin, OUTPUT);
  pinMode(input_pin, INPUT);
  pinMode(display_latch_pin, OUTPUT);
  pinMode(display_clock_pin, OUTPUT);
  pinMode(display_data_pin, OUTPUT);
  Serial.begin(9600);
  for(int i=0; i < 3;i++) {
    pinMode(led_anodes[i], OUTPUT);
    digitalWrite(led_anodes[i], HIGH);
  }
  for(int i=0; i < 9; i++) {
    pinMode(led_cathodes[i], OUTPUT);
    digitalWrite(led_cathodes[i], LOW);
  }
  start_time = millis();
}
void shift(uint8_t digit, uint8_t buffer) {
  digitalWrite(display_latch_pin, LOW);
  shiftOut(display_data_pin, display_clock_pin, MSBFIRST, digit);
  shiftOut(display_data_pin, display_clock_pin, MSBFIRST, buffer);
  digitalWrite(display_latch_pin, HIGH);
}
void loop() {
  // helikopter(400, 10);
  // layers(400);
  // LEDs_on();
  // delay(300);
  // LEDs_off();
  // delay(300);
  // LEDs_off();
  // delay(300);
  
  //main code here, to run repeatedly:
  unsigned long now_time = millis();
  double elapsed_time =((double) (now_time - start_time)) / 10x 00;
  if(digitalRead(input_pin) == HIGH) {
    timer += 5;
    shift(0, 0);
    start_time = now_time;
    delay(500);
  }
  layers(150);
  if(timer <= 0) {
    // shift(digits[4], numbers[0]);
    shift(0, 0);
    timer = 0;
    start_time = now_time;
    return;
  }
  timer -= elapsed_time;
  int time_left = (int)ceil(timer);
  int minutes = time_left / 60;
  int seconds = time_left % 60;

  shift(digits[3], numbers[seconds % 10]);
  delay(1);
  shift(digits[2], numbers[seconds / 10]);
  delay(1);
  shift(digits[1], numbers_dot[minutes % 10]);
  delay(1);
  shift(digits[0], numbers[minutes / 10]);
  delay(1);
  start_time = now_time;
}

void LEDs_on() {
  for(int i = 0; i < 9; i++) {
    digitalWrite(led_cathodes[i], LOW);
  }
  for(int i = 0 ;i < 3;i++) {
    digitalWrite(led_anodes[i], HIGH);
  }
}

void LEDs_off() {
  for(int i = 0; i < 9; i++) {
    digitalWrite(led_cathodes[i], HIGH);
  }
  for(int i = 0 ;i < 3;i++) {
    digitalWrite(led_anodes[i], LOW);
  }
}

void flicker(int speed) {
  LEDs_on();
  delay(speed);
  LEDs_off();
  delay(speed);
}

void layers(int speed) {
  LEDs_off();
  for(int i = 0;i < 9; i++) {
    digitalWrite(led_cathodes[i], LOW);
  }
  for(int i=0; i < 3;i++) {
    digitalWrite(led_anodes[i], HIGH);
    delay(speed);
    digitalWrite(led_anodes[i], LOW);
  }
}

void columns(int speed) {
  LEDs_off();

}
void X_shape(int speed) {
  for(int i = 0;i < 9;i++) {
    digitalWrite(led_cathodes[i], i%2);
  }
  for(int i = 0; i < 3;i++) {
    digitalWrite(led_anodes[i], HIGH);
  }
  delay(speed);
}

void helikopter(int speed, int seconds) {
  double start_time = millis()/1000;
  double crt_time = start_time;
  while(crt_time - start_time < seconds) {
    LEDs_off();
    for(int i=0 ; i < 9;i++) {
      digitalWrite(led_cathodes[i], i%2);
    }
    for(int i=0; i < 3; i++) {
      digitalWrite(led_anodes[i], HIGH);
    }
    delay(speed);
    for(int i=0; i < 9; i++) {
      digitalWrite(led_cathodes[i], (i%2 == 0));
    }
    delay(speed);
    crt_time = millis()/1000;

  }
  LEDs_off();
}