//CODE WRITTEN BY Bode-Okunade Abdulsalam and Olatunde Anointed both Robotics and Automation Developers at... 
//...Robotics and Artificial Intelligence Nigeria (R.A.I.N)

#include <SPI.h>      //the communication interface with the modem
#include "RF24.h"     //the library which helps us to control the radio modem (nRF24L)

//Motor A
const int RightMotorsCW = 2;    // IN1
const int RightMotorsCCW = 3;   // IN2

//Motor B
const int LeftMotorsCW = 4;     // IN3
const int LeftMotorsCCW = 5;    // IN4

//CW = Forward; CCW = Backward

int data[2];

RF24 radio(7, 8); //7 and 8 are a digital pin numbers to which signals CE and CSN are connected

const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem,that will receive data from the Arduino


void setup() {
  Serial.begin(9600);
  pinMode(RightMotorsCW, OUTPUT);
  pinMode(LeftMotorsCW, OUTPUT);
  pinMode(RightMotorsCCW, OUTPUT);
  pinMode(LeftMotorsCCW, OUTPUT);

  radio.begin();                    //it activates the modem
  radio.openReadingPipe(1, pipe);   //determines the address of our modem which receive data
  radio.startListening();           //enable receiving data via modem
}

void loop() {
  if (radio.available()) {
    radio.read(data, sizeof(data));

    //data X
    if (data[0] > 550) {
      digitalWrite(RightMotorsCW, HIGH);
      digitalWrite(RightMotorsCCW, LOW);
      digitalWrite(LeftMotorsCW, LOW);
      digitalWrite(LeftMotorsCCW, HIGH);
      Serial.println("FORWARD");
    }

    //data X
    if (data[0] < 400) {
      digitalWrite(LeftMotorsCW, HIGH);
      digitalWrite(LeftMotorsCCW, LOW);
      digitalWrite(RightMotorsCW, LOW);
      digitalWrite(RightMotorsCCW, HIGH);
      Serial.println("BACKWARD");
    }

    //data Y
    if (data[1] > 550 ) {
      digitalWrite(RightMotorsCW, LOW);
      digitalWrite(RightMotorsCCW, LOW);
      digitalWrite(LeftMotorsCW, LOW);
      digitalWrite(LeftMotorsCCW, HIGH);
      Serial.println("TURN RIGHT");
    }

    //data Y
    if (data[1] < 400 ) {
      digitalWrite(RightMotorsCW, HIGH);
      digitalWrite(RightMotorsCCW, LOW);
      digitalWrite(LeftMotorsCW, LOW);
      digitalWrite(LeftMotorsCCW, LOW);
      Serial.println("TURN LEFT");
    }

    if (data[0] < 550 && data[0] > 400 && data[1] < 550 && data[1] > 400) {
      digitalWrite(RightMotorsCW, LOW);
      digitalWrite(RightMotorsCCW, LOW);
      digitalWrite(LeftMotorsCW, LOW);
      digitalWrite(LeftMotorsCCW, LOW);
      Serial.println("STOP");
    }

  }
}
