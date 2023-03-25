#include <String.h>

double PeakPin = 0.00; // will read the heart beat (whether it's a peak or not)
const int sample_interval = 10; // changeable sample interval 
int sample_num = 1; 
const int input_pin = 9; // pin dedicated to reading heart rate 

const int ROWS = 1.0/sample_interval * exp(-3.0); //with the current sample interval, it should equal 100
const int COLS = 60; // collects 100 samples every second for 60 seconds
new int one_minute_data = [ROWS][COLS]; //one column represents 1 second of data and we collect for 60 seconds
int prev_index = 0; // helping with signal processing
int next_index = 0; // helping with signal processing
float average_heart_rate = 0.0; // this will store the average heart rate over a period of 1 minute

void setup() {
  // put your setup code here, to run once:
  pinMode(input_pin, INPUT);
  Serial.begin(9600);  // initialize serial communication, 9600 is the baud rate

  //This runs only once to collect the heart rate over 1 minute
  average_heart_rate = data_collection_one_minute(sample_interval);
}

void loop() {
  //TODO: implement the peak finding algorithm
  //TODO: implement a way to get a signal from the function generator for breathing rate

  //this for loop goes through at gets rid of any 1's that are adjacent to a peak which might be read as 1
 
}

float data_collection_one_minute(interval){
  // collecting data for 1 minute (no signal processing done)
  for (int row = 0; i < ROWS; i++) {
    //taking 100 samples each second
    for (int column = 0; j < COLS; j++) {
      PeakPin = digitalRead(input_pin);
      one_minute_data[row][column] = PeakPin;
      delay(interval);
    }
  }
  //Ensuring that any peaks occuring don't have subsequent indices that have 1's read (ie peaks accidentally read around the peak of the PQRS
  for (int row = 0; i < ROWS; i++) {
    //start at the index 1 and go until COLS -1 so that you can have a previous and next index value
    for (int column = 1; j < COLS; j++) {
      prev_index_value = one_minute_data[row][column-1];
      next_index_value = one_minute_data[row][column+1];
      if(one_minute_data[row][column] == 1 && (prev_index_value == 1 || next_index_value == 1)){
        one_minute_data[row][column-1] = 0;
        one_minute_data[row][column+1] = 0;
      }
    }
  }
  //Taking signal processed data and collecting totals to get a value for average heart rate to use
  for (int row = 0; i < ROWS; i++) {
    //start at the index 1 and go until COLS -1 so that you can have a previous and next index value
    for (int column = 1; j < COLS; j++) {
      one_second_total_hr = one_second_total_hr + one_minute_data[row][column];  
    }
  }
  return average_heart_rate = one_second_total_hr/COLS;
}


//function genrator for breathing and heart rate
// millis method
