
// TaISLAb 
// https://github.com/TaISLab/dummyarm
//
// DAQ for the dummy ARM
// Use Arduino Mega
//


// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

long nextt, t;

#define periodo 10
#define DOF 6

int input[DOF]; // ADC input readings
double angle[DOF]; // Joint angle values

int    inputmin[DOF] = {    444,   83,    176,  537,   180,  335};
double anglemin[DOF] = {     0,    0,    0,    0,  -90,  -45};
int    inputmax[DOF] = { 795, 452,   893,  175,  874, 652};
double anglemax[DOF] = {   90,  90,   180,   90,   90,   45};

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(250000);
  nextt=millis();
}


double fmap(double input, double inputmin, double inputmax, double outputmin, double outputmax)
{
  return outputmin+((input-inputmin)/(inputmax-inputmin))*(outputmax-outputmin); 
}



void loop() {

  while ((t=millis())<nextt);
  nextt+=periodo; 
  int n;
  // read the analog in value:
  input[0] = analogRead(A6);
  input[1] = analogRead(A4);
  input[2] = analogRead(A5);
  input[3] = analogRead(A0);
  input[4] = analogRead(A2);
  input[5] = analogRead(A1);
  // map it to the range of the analog out:
  for (n=0; n<DOF; n++) angle[n] = fmap(input[n], inputmin[n], inputmax[n], anglemin[n], anglemax[n]);
  // change the analog out value:
  
  Serial.print(t);    // Timestamp
  for (n=0; n<DOF; n++) {
    Serial.print(",     ");
   // Serial.print(input[n]);
    Serial.print(angle[n]);
  }
  Serial.println("");


}
