#define trigPin 13
#define echoPin 12

int pwm_a = 3;  //PWM control for motor outputs 1 and 2 
int pwm_b = 9;  //PWM control for motor outputs 3 and 4 
int dir_a = 2;  //direction control for motor outputs 1 and 2 
int dir_b = 8;  //direction control for motor outputs 3 and 4 

int leftDelay = 500;
int rightDelay = 500;
int rotateDelay = 2 * rightDelay;


void setup() {
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
  
  analogWrite(pwm_a, 100);  //set both motors to run at (100/255 = 39)% duty cycle (slow)
  analogWrite(pwm_b, 100);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  turnRight();
  driveForward(250);
}

void turnLeft() {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, LOW);  
  
  analogWrite(pwm_a, 255);  
  analogWrite(pwm_b, 255);

  delay(leftDelay);
  stopCar();
}

void turnRight() {
  digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, HIGH);  
  
  analogWrite(pwm_a, 255);  
  analogWrite(pwm_b, 255);

  delay(rightDelay);
  stopCar();
}

void driveForward(int duration) {
  digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, LOW);  
  
  analogWrite(pwm_a, 255);  
  analogWrite(pwm_b, 255);
  delay(duration);
  stopCar();
}

void driveReverse(int duration) {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH);  
  
  analogWrite(pwm_a, 255);  
  analogWrite(pwm_b, 255);

  delay(duration);
  stopCar();
}

void turnAround() {
  digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, HIGH);  
  
  analogWrite(pwm_a, 255);  
  analogWrite(pwm_b, 255);

  delay(rotateDelay);
  stopCar();

}

void stopCar() {
  digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, LOW);  
  
  
  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
  
}

void checkSensors() {
  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
}

