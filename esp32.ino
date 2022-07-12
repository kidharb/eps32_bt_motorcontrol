//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define PB_DELAY 250

int myPins[] = {5, 18, 19, 21};

void simulate_two_pb(uint8_t pin1, uint8_t pin2) {
  digitalWrite(pin1,LOW);
  digitalWrite(pin2,LOW);
  delay(PB_DELAY);
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
  delay(PB_DELAY);
  digitalWrite(pin1,LOW);
  digitalWrite(pin2,LOW);
}

void simulate_pb(uint8_t pin) {
  digitalWrite(pin,LOW);
  delay(PB_DELAY);
  digitalWrite(pin,HIGH);
  delay(PB_DELAY);
  digitalWrite(pin,LOW);
}

void setup() {
  for (uint8_t i=0; i<sizeof myPins/sizeof myPins[0]; i++) {
    pinMode(myPins[i],OUTPUT);
    digitalWrite(myPins[i],LOW);
  }
  Serial.begin(115200);
  SerialBT.begin("OCD_Systems"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
/*  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);*/
  if (SerialBT.available()) {
    uint8_t state = SerialBT.parseInt();
    switch (state) {
      case 1:
        // Send Open on Relay 1
        simulate_pb(myPins[0]);
        Serial.println("Top1 Open");
        break;
      case 2:
        // Send Close on Relay 1
        simulate_pb(myPins[1]);
        Serial.println("Top1 Close");
        break;
      case 3:
        // Send Open on Relay 2
        simulate_pb(myPins[2]);
        Serial.println("Top2 Open");
        break;
      case 4:
        // Send Close on Relay 2
        simulate_pb(myPins[3]);
        Serial.println("Top2 Close");
        break;
      case 5:
      case 33:
        // Send Open on Relay 1+2
        simulate_two_pb(myPins[0],myPins[2]);
        Serial.println("Top1 + Top2 Open");
        break;
      case 6:
      case 44:
        // Send Close on Relay 1+2
        simulate_two_pb(myPins[1],myPins[3]);
        Serial.println("Top1 + Top2 Close");
        break;
      default:
      // if nothing else matches, do the default
      // default is optional
      break;
    }
  }
}
