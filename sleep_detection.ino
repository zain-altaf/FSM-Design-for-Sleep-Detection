#include <String.h>
#include <math.h>

double PeakPin = 0.00; // will read the heart beat (whether it's a peak or not)
const int sample_interval = 10; // changeable sample interval 
int sample_num = 1; 
const int input_pin = 9; // pin dedicated to reading heart rate 
const int br_pin = 8;

const int ROWS = (int)(1000/sample_interval); //with the current sample interval, it should equal 100
const int COLS = 60; // collects 100 samples every second for 60 seconds
int one_minute_hr_data[ROWS][COLS]; //one column represents 1 second of data and we collect for 60 seconds
int one_minute_br_data[ROWS][COLS];
int prev_index = 0; // helping with signal processing
int next_index = 0; // helping with signal processing
float average_heart_rate = 0.0; // this will store the average heart rate over a period of 1 minute

void setup() {
  // put your setup code here, to run once:
  pinMode(input_pin, INPUT);
  pinMode(br_pin, INPUT);
  Serial.begin(9600);  // initialize serial communication, 9600 is the baud rate

  //This runs only once to collect the heart rate over 1 minute
  average_heart_rate = data_collection_one_minute(sample_interval);
}

void loop() {
  //TODO: implement the peak finding algorithm
  //TODO: implement a way to get a signal from the function generator for breathing rate

  //this for loop goes through at gets rid of any 1's that are adjacent to a peak which might be read as 1
 
}

float* data_collection_one_minute(int interval){
  // collecting data for 1 minute (no signal processing done)
  //returns a pointer to an array that holds [heart_rate, breathing_rate]
  int total_hr = 0;
  int total_br = 0;
  
  for (int row = 0; i < ROWS; i++) {
    //taking 100 samples each second
    for (int column = 0; j < COLS; j++) {
      PeakPin = digitalRead(input_pin);
      BRPin = digitalRead(br_pin);
      one_minute_hr_data[row][column] = PeakPin;
      one_minute_br_data[row][column] = BRPin;
      //Ensuring that any peaks occuring don't have subsequent indices that have 1's read (ie peaks accidentally read around the peak of the PQRS
      if (column - 1 >= 0 && one_minute_hr_data[row][column-1] == 1 && one_minute_hr_data[row][column] == 1) one_minute_hr_data[row][column-1] = 0;
      if (column - 1 >= 0 && one_minute_br_data[row][column-1] == 1 && one_minute_br_data[row][column] == 1) one_minute_br_data[row][column-1] = 0; 
      //We erase past peaks as we find new subsequent ones so we only have one peak per Q complex
      delay(interval);
    }
  }
  //Taking signal processed data and collecting totals to get a value for average heart rate to use
  for (int row = 0; i < ROWS; i++) {
    //start at the index 1 and go until COLS -1 so that you can have a previous and next index value
    for (int column = 1; j < COLS; j++) {
      total_hr = total_hr + one_minute_hr_data[row][column];
      total_br = total_br + one_minute_br_data[row][column];  
    }
  }
  int avg_data[2] = [total_hr/COLS, total_br/60];
  return avg_data; //returning the pointer to the array that holds relevant data
}
//function genrator for breathing and heart rate
// millis method
