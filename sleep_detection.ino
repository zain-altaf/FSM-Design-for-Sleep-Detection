#include <String.h>

int peak_pin_hr; // will read the heart beat (whether it's a peak or not)
int peak_pin_br;
const int sample_interval = 10; // changeable sample interval 
int sample_num = 1; 
const int hr_pin = 9; // pin dedicated to reading heart rate 
const int br_pin = 8;
float avg_data[2];


//const int rows = (int)(1000/sample_interval); //with the current sample interval, it should equal 100
const int initial_t_int = 10; // collects 100 samples every second for 60 seconds
const int state_t_int = 6; //we have 1 column for every second of data we collect
//int one_minute_hr_data[rows][initial_t_int]; //one column represents 1 second of data and we collect for 60 seconds
//int one_minute_br_data[rows][initial_t_int];
//int prev_index = 0; // helping with signal processing
//int next_index = 0; // helping with signal processing
//float average_heart_rate = 0.0; // this will store the average heart rate over a period of 1 minute

void setup() 
{
  // put your setup code here, to run once:
  pinMode(hr_pin, INPUT);
  pinMode(br_pin, INPUT);
  Serial.begin(9600);  // initialize serial communication, 9600 is the baud rate

  //This runs only once to collect the heart rate over 1 minute
  //average_heart_rate = data_collection_one_minute(sample_interval);
}

void loop() 
{ 
  collect_data(initial_t_int, sample_interval); //data_60 is a pointer to an array of length 2 of 2D array pointers
  Serial.println(avg_data[0]);
  //TODO: implement the peak finding algorithm
  //TODO: implement a way to get a signal from the function generator for breathing rate

  //this for loop goes through at gets rid of any 1's that are adjacent to a peak which might be read as 1
 
}

void collect_data(int t_int, int sample_interval) //t_int is the interval in seconds that we want to collect data for and t_delay is the delay time between two samples
{
  const int rows = (int)(1000/sample_interval);//with the current sample interval, it should equal 100
  bool one_minute_hr_data[rows]; //one column represents 1 second of data and we collect for 60 seconds
  bool one_minute_br_data[rows];
  int total_br = 0;
  int total_hr = 0;

  for (int i = 0; i < t_int; i++)
  {
    for (int row = 0; row < rows; row++) 
    {
      //taking 100 samples each second
        peak_pin_hr = digitalRead(hr_pin);
        peak_pin_br = digitalRead(br_pin);
        //Serial.println(peak_pin_hr);
        one_minute_hr_data[row] = peak_pin_hr;
        one_minute_br_data[row] = peak_pin_br;
        //Ensuring that any peaks occuring don't have subsequent indices that have 1's read (ie peaks accidentally read around the peak of the PQRS
        if (row - 1 >= 0 && one_minute_hr_data[row] == 1 && one_minute_hr_data[row-1] == 1) one_minute_hr_data[row-1] = 0;
        if (row - 1 >= 0 && one_minute_br_data[row] == 1 && one_minute_br_data[row-1] == 1) one_minute_br_data[row-1] = 0; 
        //We erase past peaks as we find new subsequent ones so we only have one peak per Q complex
        delay(sample_interval);
    } 
    
    for (int row = 0; row < rows; row++) 
    {
      //taking 100 samples each second
     
        total_hr = total_hr + (int)one_minute_hr_data[row];
        total_br = total_br + (int)one_minute_br_data[row]; 
    } 
  }
  
  avg_data[0] = (total_hr/(float)t_int)*60;
  avg_data[1] = (total_br/(float)t_int)*60;
  
  return;
}
