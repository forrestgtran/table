#include<Wire.h>

#define ADDR 0x08

int motor_back_right_dir = 2;
int motor_back_right_pwm = 3;

int motor_back_left_dir = 4;
int motor_back_left_pwm = 5;

int motor_front_right_dir = 7;
int motor_front_right_pwm = 6;

int motor_front_left_dir = 8;
int motor_front_left_pwm = 9;

char dir;

String inString="";

int max_speed =255;
int speeds = 255; // set the speed of all motors (range 0-255)

void setup() {
    pinMode(motor_back_right_dir, OUTPUT);
    pinMode(motor_back_right_pwm , OUTPUT);
    
    pinMode(motor_back_left_dir , OUTPUT);
    pinMode(motor_back_left_pwm , OUTPUT);
    
    pinMode(motor_front_right_dir , OUTPUT);
    pinMode(motor_front_right_pwm , OUTPUT);
    
    pinMode(motor_front_left_pwm , OUTPUT);
    pinMode(motor_front_left_dir , OUTPUT);
    
    Serial.begin(9600);
    Wire.begin(ADDR);

    Wire.onReceive(receiveData);

    Serial.println("Arduino 3 ready!");
}

void loop() {

  if(inString != "") {
    Serial.print("dir: "); Serial.println(dir);
  }

  switch (dir) {
    case 'f': //forward
        digitalWrite(motor_back_right_dir, HIGH);
        digitalWrite(motor_back_left_dir, LOW);
        digitalWrite(motor_front_right_dir, HIGH);
        digitalWrite(motor_front_left_dir, LOW);
        set_all_motor_speeds(speeds);
        break;
    case 'b': //backward
        digitalWrite(motor_back_right_dir, LOW);
        digitalWrite(motor_back_left_dir, HIGH);
        digitalWrite(motor_front_right_dir, LOW);
        digitalWrite(motor_front_left_dir, HIGH);
        set_all_motor_speeds(speeds);
        break;
    case 'r': //right
        digitalWrite(motor_back_right_dir, HIGH);
        digitalWrite(motor_back_left_dir, HIGH);
        digitalWrite(motor_front_right_dir, LOW);
        digitalWrite(motor_front_left_dir, LOW);
        set_all_motor_speeds(speeds);
        break;
    case 'l': //left
        digitalWrite(motor_back_right_dir, LOW);
        digitalWrite(motor_back_left_dir, LOW);
        digitalWrite(motor_front_right_dir, HIGH);
        digitalWrite(motor_front_left_dir, HIGH);
        set_all_motor_speeds(speeds);
        break;
    case 'c': //clockwise
        digitalWrite(motor_back_right_dir, HIGH);
        digitalWrite(motor_back_left_dir, HIGH);
        digitalWrite(motor_front_right_dir, HIGH);
        digitalWrite(motor_front_left_dir, HIGH);
        set_all_motor_speeds(speeds);
        break;
    case 'o': //counterclockwise
        digitalWrite(motor_back_right_dir, LOW);
        digitalWrite(motor_back_left_dir, LOW);
        digitalWrite(motor_front_right_dir, LOW);
        digitalWrite(motor_front_left_dir, LOW);
        set_all_motor_speeds(speeds);
        break;
    case 's': //stop
        stop_all_motors();
        break;
    case '0':
        speeds = max_speed * 1.0;
        set_all_motor_speeds(speeds);
        break;
    case '1':
        speeds = max_speed * 0.1;
        set_all_motor_speeds(speeds);
        break;
    case '2':
        speeds = max_speed * 0.2;
        set_all_motor_speeds(speeds);
        break;
    case '3':
        speeds = max_speed * 0.3;
        set_all_motor_speeds(speeds);
        break;
    case '4':
        speeds = max_speed * 0.4;
        set_all_motor_speeds(speeds);
        break;
    case '5':
        speeds = max_speed * 0.5;
        set_all_motor_speeds(speeds);
        break;
    case '6':
        speeds = max_speed * 0.6;
        set_all_motor_speeds(speeds);
        break;
    case '7':
        speeds = max_speed * 0.7;
        set_all_motor_speeds(speeds);
        break;
    case '8':
        speeds = max_speed * 0.8;
        set_all_motor_speeds(speeds);
        break;
    case '9':
        speeds = max_speed * 0.9;
        set_all_motor_speeds(speeds);
        break;
    default:
        stop_all_motors();
        break;
    }

    inString = "";
    delay(100); // For proper i2c timing
}

void set_all_motor_speeds(int value) {
  analogWrite(motor_back_right_pwm, value);
  analogWrite(motor_back_left_pwm, value);
  analogWrite(motor_front_right_pwm, value);
  analogWrite(motor_front_left_pwm, value);
}

void stop_all_motors() {
  analogWrite(motor_back_right_pwm, 0);
  analogWrite(motor_back_left_pwm, 0);
  analogWrite(motor_front_right_pwm, 0);
  analogWrite(motor_front_left_pwm, 0);
}

void receiveData(int byteCount) {
    int inChar;

    while (Wire.available()){
      inChar = Wire.read();
      inString += char(inChar);
  }

  dir = inString[1];
  
}
