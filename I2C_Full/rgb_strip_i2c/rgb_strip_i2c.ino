#include<Wire.h>

#define ADDR 0x06

int red_cathode_pwm = 3; 
int green_cathode_pwm = 5;
int blue_cathode_pwm = 6;

int red_analog = A1;
int green_analog = A6;
int blue_analog = A7;

//char color;
boolean ledEnable = false;

int red_pot_voltage;
int green_pot_voltage;
int blue_pot_voltage;

int red_intensity;
int green_intensity;
int blue_intensity;

String hexColor;

String inString = "";
boolean isReceived = false;



void setup() {
  pinMode(red_cathode_pwm, OUTPUT);
  pinMode(green_cathode_pwm, OUTPUT);
  pinMode(blue_cathode_pwm, OUTPUT);
  Serial.begin(9600);

  Wire.begin(ADDR);
  Wire.onReceive(receiveData);

  Serial.println("Arduino 2 ready!");

}

void loop() {

  if (isReceived) {
    Serial.print("String received: ");
    Serial.println(inString);
    isReceived = false;
  }


  if (inString == "serial") {
    ledEnable = true;
  } 
  else if (inString == "potent") {
    ledEnable = false;
  } 
  else if(inString != "") {
    inString = inString.substring(inString.length()-6,inString.length());
    if(inString != "serial") {
      hexColor = inString;
      if(hexColor != "") {
        Serial.print("hexColor: "); 
        Serial.println(hexColor);
      }
    }
  }

  if (ledEnable) {
    controlLeds();
  } 
  else {
    controlPots();
  }
  //inString = "";
  delay(10); // For correct i2c timing
}

void controlLeds() {

  int red = hexToRGB(hexColor[0], hexColor[1]);
  int green = hexToRGB(hexColor[2], hexColor[3]);
  int blue = hexToRGB(hexColor[4], hexColor[5]);

  analogWrite(red_cathode_pwm, red);
  analogWrite(green_cathode_pwm, green);
  analogWrite(blue_cathode_pwm, blue);

  if(hexColor != "") {
    Serial.print("r :"); 
    Serial.print(red);
    Serial.print(" g :"); 
    Serial.print(green);
    Serial.print(" b :"); 
    Serial.println(blue); 
  }

}

void controlPots() {
  red_pot_voltage = analogRead(red_analog);
  green_pot_voltage = analogRead(green_analog);
  blue_pot_voltage = analogRead(blue_analog);
  red_intensity = map(red_pot_voltage, 0, 1023, 0, 255);
  green_intensity = map(green_pot_voltage, 0, 1023, 0, 255);
  blue_intensity = map(blue_pot_voltage, 0, 1023, 0, 255);

  analogWrite(red_cathode_pwm, red_intensity);
  analogWrite(green_cathode_pwm, green_intensity);
  analogWrite(blue_cathode_pwm, blue_intensity);


}

int hexToDec(char hexChar) {
  if (hexChar < 58 && hexChar > 47) {
    return (hexChar - 48);
  } 
  else if (hexChar < 103 && hexChar > 96) {
    return (hexChar - 87);
  } 
  else {
    return 0;
  }
}

int hexToRGB(char hex1, char hex2) {
  return 16 * hexToDec(hex1) + hexToDec(hex2);
}

void receiveData(int byteCount) {
  int inChar;

  isReceived = false;
  //inString = "";

  while (Wire.available()) {
    inChar = Wire.read();
    inString += char(inChar);
  }

  isReceived = true;
}



