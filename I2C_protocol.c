/*
A vague attempt in implementing a I2C communication protocol using a memory chip(EEPROM chip).
We try to write and read data from the external chip connected
*/


#include<Wire.h>

//defining the address of the connected device
#define ADDRESS 0x50


/*
|start|1|0|1|0|A2|A1|A0|R/W|ACK|
After the start bit, next 4 bits are constant and we can use a manual to find out. Last three bits i.e A2, A1, A0 can be set based on user design
*/


//main setup function
void setup(){
	Serial.begin(9600); //9600 is the baud rate for transmission

	//Allows the connection between the motherboard and device to take place
	Wire.begin(); 
	
	delay(15); //Delay provided for the device to be operational.
	
	/*
	Write function
	Write function takes in three arguments 
	 a.High Address 	b. Low Address 	c. Data 
	*/

	writeData(0,0,125); 	//High Add = 0 	Low Add= 0 	Data = 125
	delay(5); 		//Allow data to be written to the device

	/*
	Reading data
	Reading data needs High and Low Address locations to where the data was written
	*/
	Serial.println(readData(0,0)); 
}


void loop(){
}

//Write Function
void writeData(byte highAdd, byte lowAdd, byte data){
	//starts the communication between device and motherboard
	Wire.beginTransmission(Address); 

	Wire.write(highAdd); //specifying the high and low address
	Wire.write(lowAdd);
	
	Wire.write(data);//Write Data into the device
	Wire.endTransmission();//End of transmission
}

//Read Function
byte readData(byte highAdd, byte lowAdd){
	//Initialize the communication channel
	Wire.beginTransmission(Address);

	//Specify the high and low address from which data has to be read
	Wire.write(highAdd);
	Wire.write(lowAdd);
	Wire.endTransmission();
	
	/*
	Control Register final bit decides whether data needs to read or written.
	 	If 	
		read then bit is set to 1
		write then bit is set to 0
	*/

	/*
	we make use of requestFrom() to read data.
	This function takes in two arguments. 
	 1. Address of Device		2.Number of bytes to be read
	*/
	
	Wire.requestFrom(Address, 1);
	
	//if data is not available to read
	while(!Wire.available()){
	} 
	//we can achieve this by mutex locks too by using thread in a UNIX env
	
	//return the read data
	return Wire.read();
}
