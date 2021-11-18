#include <Servo.h>
#include <Stepper.h>

//Constants
const int pResistor = A0; // Photoresistor
const int signalLED = 9;  // Led pin at Arduino pin 9
const int stepsPerRevolution = 200;  
const int servoPin = 10;


const int SERVO_CLOSED = 0;
const int SERVO_OPEN = 180;

const int STEPS = 100;
const int STEPPER_DELAY = 15;

// Any colour less will be the darker marble
const int COLOUR_RES = 60;


Servo myservo;  
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);

void setup() {
  Serial.begin(9600);
  
  pinMode(signalLED, OUTPUT);  // Set lepPin - 9 pin as an output
  pinMode(pResistor, INPUT);  // Set pResistor - A0 pin as an input 

  myservo.attach(servoPin);  // attaches the servo on pin 10 to the servo object

}

int value = 0;
int totalSorted = 0;

void loop() {
  
  value = analogRead(pResistor);
  int step_direction = 0;
  
  if (value > COLOUR_RES) {
    
    step_direction = 1;
    
  }
  else {
    
    step_direction = -1;
    
  }
  
  int stepCount = 0;
  
  while (stepCount <= STEPS) {
      
      myStepper.step(step_direction);
      delay(STEPPER_DELAY);
      
      stepCount++;
  }

  myservo.write(SERVO_OPEN);
  delay(10);
  myservo.write(SERVO_CLOSED);
  
  for (int x = 0; x < stepCount; x++) {
    
    myStepper.step(step_direction * -1);
    delay(STEPPER_DELAY);
      
  }
  
  totalSorted++;
  
  if (totalSorted >= 5) {
    
    digitalWrite(signalLED, HIGH);
    
  }

  delay(10);
}
