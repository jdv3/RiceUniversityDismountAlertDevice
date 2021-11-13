/*********************************************
John David Villarreal
Medium Fidelity Code Prototype
Rice University Dismount Zone Alert Device
*********************************************/

/***
* Setup Variables
*/

unsigned short photo_0, photo_1, photo_2;   //Set Up Registers to hold photoresistor readings
unsigned short force_0, force_1, force_2;   //Set up Registers to hold force sensor readings
                                            //Use an unsigned short to maximize refresh time

const int baud = 9600;                      //Set up a refresh rate for the serial monitor

const short light_threshold = 300;          //Establish a light threshold for the photoresistor array
                                            //The threshold was determined experimentally using the values read from the sensor
                                            
const short force_threshold = 3;            //Establish a force threshold for the force sensor array
                                            //The threshold was determined experimentally using the values read from the sensor

const short photo_led = 2;                  //Assign a short for the Corresponding Physical Digital Pin. This pin corresponds to the net indicator led for the photoresistor
const short force_led_1 = 3;                //Assign a short for the Corresponding Physical Digital Pin. This pin corresponds to a single led
const short force_led_2 = 4;                //Assign a short for the Corresponding Physical Digital Pin. This pin corresponds to a single led
const short force_led_3 = 5;                //Assign a short for the Corresponding Physical Digital Pin. This pin corresponds to a single led
const short force_led = 6;                  //Assign a short for the Corresponding Physical Digital Pin. This pin corresponds to the net indicator led for the force sensor array

/*
 * Setup
 */

void led_setup() {

  pinMode(photo_led, OUTPUT);               //Define the pinmode to the corresponding didgital pin. See code above where the vars were assigned
  pinMode(force_led_1, OUTPUT);             //Define the pinmode to the corresponding didgital pin. See code above where the vars were assigned
  pinMode(force_led_2, OUTPUT);             //Define the pinmode to the corresponding didgital pin. See code above where the vars were assigned
  pinMode(force_led_3, OUTPUT);             //Define the pinmode to the corresponding didgital pin. See code above where the vars were assigned
  pinMode(force_led, OUTPUT);               //Define the pinmode to the corresponding didgital pin. See code above where the vars were assigned
  
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(baud);                       //Begin the serial monitor/plotter readings at the set baud speed
  
}

/***
* Objects
*/

void photo_output() {

  photo_0 = analogRead(A0);                 //Store the reading from the first photoresistor into the corresponding register
  photo_1 = analogRead(A1);                 //Store the reading from the second photoresistor into the corresponding register
  photo_2 = analogRead(A2);                 //Store the reading from the third photoresistor into the corresponding register

  //Perform a logic test. 
  //If any of the photoresistors registers a value greater than the threshold, turn on the photoresistor indicator led on to indicate the reading was successful
  if(photo_0 >= light_threshold || photo_1 >= light_threshold || photo_2 >= light_threshold){
    
    //Serial.println("LED Lights On");      //Write to the serial monitor the lights are turned on
    digitalWrite(photo_led, HIGH);          //Turn on the led while the condition is true
  } else {
    digitalWrite(photo_led, LOW);           //Turn off the led while the condition is false (This logical statement is run over and over, so it refreshes according to the cycle time)
  }
  
}

void comparator() {

  //Perform a logic test.
  //If any of the force sensors registers a value greater than or equal to the threshold, continue with the subsequent logical statements
  if(force_0 >= force_threshold or force_1 >= force_threshold or force_2 >= force_threshold){

    //If two force sensors are equal to each other and they are not equal to each other at zero:
    if(force_0 == force_1 and force_0 != 0 and force_1 != 0) {
      
      digitalWrite(force_led, HIGH);        //Turn on the force indicator led
      
    }
    else if(force_1 == force_2 and force_1 != 0 and force_2 != 0) {
      
      digitalWrite(force_led, HIGH);        //Turn on the force indicator led
      
    }
    else if(force_2 == force_0 and force_2 != 0 and force_0 != 0) {
      
      digitalWrite(force_led, HIGH);        //Turn on the force indicator led
      
    }
    
  } else {
    digitalWrite(force_led, LOW);           //Turn off the led while the condition is false (This logical statement is run over and over, so it refreshes according to the cycle time)
  }
  
}

void force_output() {

  force_0 = analogRead(A3);                 //Store the force sensor reading from the first force sensor into the corresponding register
  force_1 = analogRead(A4);                 //Store the force sensor reading from the second force sensor into the corresponding register
  force_2 = analogRead(A5);                 //Store the force sensor reading from the third force sensor into the corresponding register

  

  //For the following 3 logical statements:
  //If any of the force sensors registers a value above the threshold, turn on their corresponding LED, otherwise keep them off
  if(force_0 >= force_threshold){
    digitalWrite(force_led_1, HIGH);
  } else {
    digitalWrite(force_led_1, LOW);
  }

  if(force_1 >= force_threshold) {
    digitalWrite(force_led_2, HIGH);
  } else {
    digitalWrite(force_led_2, LOW);
  }
  
  if(force_2 >= force_threshold) {
    digitalWrite(force_led_3, HIGH);
  } else {
    digitalWrite(force_led_3, LOW);
  }

  comparator();                             //Execute the comparator function
                                            //The comparator function is what differentiates a pedestrian from a rider
}

/*
 * Loops
 */

void loop() {
  // put your main code here, to run repeatedly:
  photo_output();                           //Execute the photo_output function
                                            //The photo_output function is what conducts the logic for the photoresistors
  force_output();                           //Execute the force_output function
                                            //The force_output function is hwat conducts the logic for the force sensors

  Serial.print("Analog_Force_Value: ");     //For testing, print the force sensor values to the serial monitor and plotter

  Serial.print(force_0);
  Serial.print("\t");
  
  Serial.print(force_1);
  Serial.print("\t");
  
  Serial.print(force_2);
  Serial.println("\t");                     //Use a tab and println to seperate one set of data from the subsequent set of data

}
