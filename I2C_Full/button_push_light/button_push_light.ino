#include <Servo.h>
#include<Wire.h>

#define ADDR 0x04


Servo servoup;
Servo servodown;

int right = A7;
int left = A6;
int r = 0;
int l = 0;
int j = 0;
int sum_r = 0;
int sum_l = 0;
int normal_r = 0;
int normal_l = 0;

int mode = 0;

int servopin_up = 10;
int servopin_down = 9;
int off_pos_up = 180; //angle when idle
int off_pos_down = 0;
int on_pos_up = 50; //angle when pushing button
int on_pos_down = 130;
int command = 0;
int amount = 0;
int switch_delay = 500;
int incoming = 0;
int amount1 = 0;
//int i = 0;
int number = 0;
String value;
char in = '0';

String inString = "";
boolean isReceived = false;

void setup() {
  pinMode(right, INPUT);
  pinMode(left, INPUT);
  servoup.attach(servopin_up);
  servoup.write(off_pos_up);
  servodown.attach(servopin_down);
  servodown.write(off_pos_down);

  Serial.begin(9600);
  Wire.begin(ADDR);

  Wire.onReceive(receiveData);
  Serial.println("Arduino 1 ready!");
}

void loop() {

  if (isReceived) {
    Serial.print("String received: ");
    Serial.println(inString);
    isReceived = false;
  }

  while (millis() < 3000) {
    j += 1;
    sum_r = sum_r + analogRead(right);
    sum_l = sum_l + analogRead(left);
    delay(100);
    if (millis() > 3000) {
      normal_r = sum_r / j;
      normal_l = sum_l / j;
      Serial.print(normal_r);
      Serial.print(normal_l);
      delay(2000);
    }
  }

  if(inString == "5light") {
    mode = 0;
  } 
  else if (inString == "6serial"){
    mode = 1;
  }
  
  
  if (mode == 0) {
    light_control();
  }
  else {
    serial_control();
  }


 // Serial.print(command);
  inString = "";
  delay(100);

}



int light_control() {

  if ((analogRead(right) * 1.3) < normal_r) {
   // Serial.print("up");
   // Serial.println(analogRead(right));
    if (command != 1) {
      command = 1;
      servodown.write(off_pos_down);
      delay(1000);
      servoup.write(on_pos_up);
    }
  }
  else if ((analogRead(left) * 1.3) < normal_l) {
    Serial.print("down");
    Serial.println(analogRead(left));
    if (command != -1) {
      command = -1;
      servoup.write(off_pos_up);
      delay(1000);
      servodown.write(on_pos_down);
    }
  }
  else if (command != 0) {
    command = 0;
    servoup.write(off_pos_up);
    servodown.write(off_pos_down);
    delay(1000);
  }

  //Serial.print(command);

//  if (Serial.available() > 0) {
//    in = Serial.read();
//    if (in == 's') {
//      mode = 1; //switch to serial control
//    }
//  }
}



int serial_control() {
  //Serial.println("serial");
  int maxIndex = inString[0] - 48;

  for (int i = maxIndex - 2; i >= 0; i--) {
    incoming += pow(10, i) * (inString[maxIndex - i] - 48);
  }

  if (inString[1] == 'd' && incoming < 48) {
    command = 1; //up
  }
  else if (inString[1] == 'u' && incoming < 48) {
    command = -1; //down
  }


  amount = map(incoming, 0, 48, 0, 17000);
  incoming = 0; //reset to zero to avoid repeat commands
  //}

  if (command == 1) {
    servoup.write(on_pos_up);
    delay(amount); //time to press button

    servoup.write(off_pos_up);
    delay(switch_delay);
    command = 0; //reset to zero
    amount = 0;

  }
  else if (command == -1) {
    servodown.write(on_pos_down);
    delay(amount);
    servodown.write(off_pos_down);
    delay(switch_delay);
    command = 0;
    amount = 0;
  }
}


void receiveData(int byteCount) {
  int inChar;

  isReceived = false;

  while (Wire.available()) {
    inChar = Wire.read();
    inString += char(inChar);
  }

  isReceived = true;
}
