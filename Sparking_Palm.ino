
/*Microphone connections:
A0 = A0
G = GND
+ = 5V
D0 = "No need to connect"

Relay INPUT connections:
VCC = 5V
GND = GND
INT = pin 8

Relay OUTPUT:
-Rotate relay until all OUTPUT connections are on your right
-Now count OUTPUTS from top to bottom. Connect first cable to 4th and another to 5th OUTPUT of the relay. Doesn't matter which way.
*/
#define RELAY1  8
int previous_round = 0; //Was relay on during previous round?
int current_round = 0; //Is relay on this round?

int sensorPin = A0; // select the input pin for the potentiometer
int ledPin = 13; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
int sensorValue_reference = 270; //I use 270 as reference preference here. You have to adjust your potentiometer on your mic to the same value aswell.
//It seems that the value of the sensor is rising over time if you keep it on for a longer time. This variable sets it always to certain point when resetting the Arduino.


 
void setup () 
{
  pinMode(RELAY1, OUTPUT);   
  digitalWrite(RELAY1,HIGH);          // Turns Relay Off 
  pinMode (ledPin, OUTPUT);
  Serial.begin (9600);
  int sensorValue_reference1 = analogRead (sensorPin);//reading the reference value
  delay(100);
  int sensorValue_reference2 = analogRead (sensorPin);//reading the reference value
  delay(100);
  int sensorValue_reference3 = analogRead (sensorPin);//reading the reference value
  delay(100);
  int sensorValue_reference4 = analogRead (sensorPin);//reading the reference value
  delay(100);
  int sensorValue_reference5 = analogRead (sensorPin);//reading the reference value
  delay(100);
  sensorValue_reference = (sensorValue_reference1 + sensorValue_reference2 + sensorValue_reference3 + sensorValue_reference4 + sensorValue_reference5)/5; 
  Serial.println ("Reference sensor value:");
  Serial.println (sensorValue_reference, DEC);
  delay(1000);
  Serial.println("Moving to void loop...");
  delay(1000);
  Serial.println("These are sensor values in real time: ");
}
 
void loop () 
{
  previous_round = current_round;
  sensorValue = analogRead (sensorPin);
  delay (sensorValue);
  //delay (sensorValue);
  Serial.print ("Sensor value: ");
  Serial.println (sensorValue, DEC);
  trigger(sensorValue_reference - 5, sensorValue_reference + 5);//NOTE: When measured value change +-5 compared to reference value relay willl be triggered. //NOTE: This value (5) varies a lot because of unideal components. Try to find a right value for yourself. Mine have been between 2 and 10.
  check_relay_current_and_previous_status();
}

void trigger(int limit2, int limit1){ //Triggers the relay and LED on Arduino board when value read from mic changes
  if (sensorValue > limit1 or sensorValue < limit2) {
    Serial.println("Relay on");
    digitalWrite (ledPin, HIGH);
    digitalWrite(RELAY1,LOW);           // Turns ON Relays 1
    delay(500);
    Serial.print("Reference value: ");
    Serial.println(sensorValue_reference);
    current_round = 1;
    }
  else if (sensorValue <= limit1 or sensorValue >= limit2){
    //Serial.println("Relay off");
    digitalWrite (ledPin, LOW);
    digitalWrite(RELAY1,HIGH);          // Turns Relay Off 
    delay(500);
    current_round = 0;
  }
  }

void check_relay_current_and_previous_status(){//Mic's values drop about 57 when relay is on. To compensate that we have to make a function that increases and decreases by 57 when needed.
  if (previous_round == 1 and current_round == 0){
    sensorValue_reference = sensorValue_reference + 57; //NOTE: This value (57) varies a lot because of unideal components. Try to find a right value for yourself. Mine have been between 10 and 60.
    Serial.print("Reference value: ");
    Serial.println(sensorValue_reference);}
  else if (previous_round == 0 and current_round == 1){
    sensorValue_reference = sensorValue_reference - 57;
    }
   
  }
