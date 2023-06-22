#include<SPI.h>
#include<SD.h>
File myFile;
const int groundpin=14; //analog input pin 4—ground
const int powerpin=18; //analog input pin 5—voltage
const int xpin=A3; //x-axis of the accelerometer
const int ypin=A2; //y-axis
const int zpin=A1; //z-axis (only on 3-axis models)
int x[2],y[2],z,vec,i;
float thresh=1.4;
class pedometer
{
private:
int vec;
float steps;
float tot;
public:
pedometer()
{
steps=0;
tot=0; 
}
void datacol() //function to collect data
{
for(i=0;i<=2;i++)
{
x[i]=analogRead(xpin);
y[i]=analogRead(ypin);
}
vec=(sqrt(x[1]^2+y[1]^2)-sqrt(x[0]^2+y[0]^2));
if(vec>=0);
else if(vec<0)
{
vec=(0-vec);
}
steps=vec/thresh;
tot=tot+steps;
}
void smdisp() //displaying to serial monitor
{
Serial.print(vec);
Serial.print("\t");
Serial.print(steps);
Serial.print("\t");
Serial.print((int)tot);
Serial.println(); 
}
void file() //printing to sd card
{
if(!SD.begin(4)&&(int)tot%10==0)
{
Serial.println("initialization failed!!");
return;
}
Serial.println("initialization done.");
myFile=SD.open("Data.txt",FILE_WRITE);
if(myFile)
{
Serial.print("Writing to Data.txt...");
myFile.println("Total Steps");
myFile.print((int)tot); 
Serial.print("Done!!");
myFile.close(); //closing of file 
}
else //if the file didn't open,print an error
{
Serial.println("Error opening Data.txt"); 
}
myFile=SD.open("Data.txt");
if(myFile)
{
Serial.println("Data.txt");
while(myFile.available()) //read from the file until there's nothing else in it
{
Serial.write(myFile.read());
myFile.close(); //closing of file
}
}
else //if the file didn't open,print an error
{
Serial.println("Error opening Data.txt"); 
} 
}
}ped;
void setup()
{ //initialize the serial communications
Serial.begin(9600);
//Provide ground & power by using the analog inputs as normal digital pins
//This makes it possible to directly connect the breakout board to the Arduino
//If you use the normal 5V & GND pins on the Arduino
pinMode(groundpin,OUTPUT);
pinMode(powerpin,OUTPUT);
digitalWrite(groundpin,LOW);
digitalWrite(powerpin,HIGH);
}
void loop()
{
ped.datacol();
ped.smdisp();
delay(100);
ped.file();
}
