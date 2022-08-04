//CODE WRITTEN BY Bode-Okunade Abdulsalam and Olatunde Anointed both Robotics and Automation Developers at... 
//...Robotics and Artificial Intelligence Nigeria (R.A.I.N)


#include <SPI.h>  //the communication interface with the modem
#include "RF24.h" //the library which helps us to control the radio modem

//define the data pins
int joyX = A1;
int joyY = A2;

//define variable values
int dataX;
int dataY;

//setting the array
int data[2];

RF24 radio(7, 8); //7 and 8 are a digital pin numbers to which signals CE and CSN are connected

const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the NRF24L01, that will receive data from Arduino


void setup(void){
  Serial.begin(9600);
  radio.begin();                      //it activates the modem
  radio.openWritingPipe(pipe);        //sets the address of the receiver to which the program will send data
}

void loop(){
  //Send signal data
  dataX = analogRead(joyX);           //collecting the joystick X-axis data and saving to dataX
  dataY = analogRead(joyY);           //collecting the joystick Y-axis data and saving to dataY
  
  data[0] = dataX;                    //saving dataX to the data[0] array
  data[1] = dataY;                    //saving dataY to the data[1] array

  
#if 0 //Set 0 to 1 to activate
  Serial.print("Data X:"); Serial.println(dataX); 
  Serial.print("Data Y:"); Serial.println(dataY);
  
#endif

  
  radio.write(data, sizeof(data));    //transmitting the full data to the receiver using the NRF.
  
}
