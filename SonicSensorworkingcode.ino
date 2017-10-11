int echo = 11;                                           // Define the echo pin as a constant integer, so it cant be changed
int trig = 10;                                           // Define the trigger pin as a constant integer, so it cant be changed
int led = 7;
int led2 = 8;
int led3 = 6;
int led4 = 5;

int maxRange = 200;                                           // Set maximum range to 200 cm
int minRange = 0;                                              // Set minimum range to 0 cm
int threshold = 100;
int threshold2 = 50;
//int i = 0, j = 0;                                             // Counters
long distance1;
long distance2;
long duration;                                      // create long variables for distance and duration
// Uncomment when we are filtering : https://dsp.stackexchange.com/questions/20333/how-to-implement-a-moving-average-in-c-without-a-buffer
//long displacement[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};       // creates an array of 10 elements of distance to be used as a buffer for the displacement values
//long sum, average, time1 = 0, time2 = 0, sp;    

void setup() {                                                // Setup Loop
  /*What Is a baud rate? How does the serial communication work?*/
  Serial.begin(9600);                                         // initialize serial communication at baud rate: 9600:
  pinMode(trig,OUTPUT);                                       // Set Trigger Pin to output
  pinMode(echo,INPUT);                                        // Set Echo Pin to input
  pinMode(led,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  
}

void loop() {                                                 // begin loop after all variables have been declared and initialized

 digitalWrite(trig, LOW);                                     // Write trigger to low for
 delayMicroseconds(2);                                        // 2 us

 digitalWrite(trig, HIGH);                                    // Write trigger to high for 
 delayMicroseconds(10);                                       // 10 us
 
 digitalWrite(trig, LOW);                                     // Write trigger back to low

/*
 * Resultin wave at trigger pin:
 * Voltage (V)
 * HIGH (3.3V)         ______________________________
 *                    |                              |      |
 *                    |                              |      |
 *                    |                              |      |
 * LOW (0V)     ______|                              |______|
 *                    2                              12     14  time(us)
 *                    
 * The square wave resulting from the above commands (maybe discussion about duty cylce can be inserted here) 
 */

 
 duration = pulseIn(echo, HIGH);                              // Measures duration of the pulse at the echo pin
 //time1 = time2;                                               // take times right after the measurement has been taken
 //time2 = millis();
 //if (duration >= maxRange * 58.2 || duration <= minRange *58.2){   // Checks if distance is within the range 
 //distance1 = distance2;                                                        
 distance2 = duration/58.2;                                   // Calculate the distance (in cm) based on the speed of sound.
  if (distance2 < threshold && distance2 > threshold){
    digitalWrite(led, HIGH);
    digitalWrite(led2,HIGH);
    
  }

  else if(distance2 < threshold2){
    digitalWrite(led,OUTPUT);
    digitalWrite(led2,OUTPUT);
    digitalWrite(led3,OUTPUT);
    digitalWrite(led4,OUTPUT);
    
  }
    else {
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    
    }
  /* How can signal processing be employed to filter the results from noise? How can the speed of an object be discovered? */

/*FILTERING:
  * An averaging filter implements a buffer and counts the average of an amount of previous measurments specified by the buffer size
  * 
  * An averaging filter is essentially a low pass filter as it cuts out high frequency noise and "smoothens" the result
  */
  
  //displacement[i] = duration/58.2;
  //sum = 0;
  //for(j = 0; j < 10; j++){
  // sum = sum + displacement[j];
  //}
  //average = sum/10; 

 /*SPEED:
  * Speed is a measure of how much distance is covered within a certain amount of time.
  * 
  * What is the distance covered and how can we find out the time that has been taken? 
  * (Note the variable "duration" only measures the duration of the pulse)
  * the time between two measurements can be simplified to 
  */
  //sp = (distance2 - distance1)/(time2 - time1);
  //if (i < 0) {
  //  sp = (displacement[i] - displacement[i - 1])/(time2 -time1);
  //}
  //else {
  //  sp = (displacement[i] - displacement[i - 1])/(time2 -time1);
  //}
  
  /* Send the distance to the computer using Serial protocol */
  Serial.println(distance2);                                   // Sends the distance in cm to the serial monitor if it is within range
  //Serial.println("average is: " + average);
  //Serial.print("speed is: ");
  //Serial.print(sp);
  //Serial.println(" cm/s");
 //}
 //else {
 // Serial.println("Out of bounds");
 //}

  

  delay(100);                                                 // Delay for 100 ms, so that the serial monitor shows distance every 100 ms
  //i++;                                                      // increment buffer count by 1
  //if(i == 10)
  //  i = 0;
}
