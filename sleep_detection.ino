#include <String.h>

double PeakPin = 0.00;                // input pin that reads the voltage drop across the rubber wire, can be any of the analog pins A0-A5
const int sample_interval = 10;
int sample_num = 1;
const int input_pin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(input_pin, INPUT);
  Serial.begin(9600);  // initialize serial communication, 9600 is the baud rate
}

void loop() {
  // put your main code here, to run repeatedly:
  //This reads the signal from the function generator: possible values = 0 (no hear beat or not max) and 1 (heart beat peak detected)
  PeakPin = digitalRead(input_pin);
  //TODO: implement the peak finding algorithm
  //TODO: implement a way to get a signal from the function generator for breathing rate

  
  Serial.print('\n');  // starts the program on a new line in the serial monitor
  Serial.print(PeakPin); // prints the column headings
  Serial.print('\t');
  Serial.println(sample_num++);  
  delay(sample_interval);
}

//function genrator for breathing and heart rate
// millis method
