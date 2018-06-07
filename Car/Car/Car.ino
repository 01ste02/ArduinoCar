#define trigPin 12
#define echoPin 13

#define trigPin2 10
#define echoPin2 11

#define trigPin3 8
#define echoPin3 7

long duration, distance;
long duration2, distance2;
long duration3, distance3;

int pwm_a = 3;  //PWM control for motor outputs 1 and 2
int pwm_b = 9;  //PWM control for motor outputs 3 and 4
int dir_a = 2;  //direction control for motor outputs 1 and 2
int dir_b = 8;  //direction control for motor outputs 3 and 4

int leftDelay = 415;
int rightDelay = 415;
int rotateDelay = 2 * rightDelay;


void setup() {
  //Serial.begin(9600);

  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);

  analogWrite(pwm_a, 100);  //set both motors to run at (100/255 = 39)% duty cycle (slow)
  analogWrite(pwm_b, 100);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

void loop() {
  checkSensors();
  while (distance > 20) {
    driveForward(1);
    checkSensors();
  }

  if (distance < 21) {
    eStop();
    if (distance2 > distance3) {
      turnRight();
    } else if (distance2 < distance3) {
      turnLeft();
    } else {
      int randInt = random(0, 2);
      switch (randInt) {
        case 0:
          turnLeft();
          break;
        case 1:
          turnRight();
          break;
        case 2:
          turnAround();
          break;
      }
    }
  }
}

void turnLeft() {
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, LOW);

  analogWrite(pwm_a, 100);
  analogWrite(pwm_b, 100);

  delay(leftDelay);
  stopCarLeft();
}

void turnRight() {
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, HIGH);

  analogWrite(pwm_a, 100);
  analogWrite(pwm_b, 100);

  delay(rightDelay);
  stopCarRight();
}

void driveForward(int duration) {
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, LOW);

  analogWrite(pwm_a, 150);
  analogWrite(pwm_b, 150);
  delay(duration);
  //stopCar();
}

void driveReverse(int duration) {
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, HIGH);

  analogWrite(pwm_a, 150);
  analogWrite(pwm_b, 150);

  delay(duration);
  stopCar();
}

void turnAround() {
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, HIGH);

  analogWrite(pwm_a, 70);
  analogWrite(pwm_b, 70);

  delay(rotateDelay);
  stopCar();

}

void stopCar() {
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, HIGH);

  analogWrite(pwm_a, 100);
  analogWrite(pwm_b, 100);

  delay(15);
  analogWrite(pwm_a, 0);
  analogWrite(pwm_b, 0);
}

void stopCarLeft() {
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, HIGH);

  analogWrite(pwm_a, 90);
  analogWrite(pwm_b, 90);

  delay(150);

  analogWrite(pwm_a, 0);
  analogWrite(pwm_b, 0);
}

void stopCarRight() {
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, LOW);

  analogWrite(pwm_a, 90);
  analogWrite(pwm_b, 90);

  delay(150);

  analogWrite(pwm_a, 0);
  analogWrite(pwm_b, 0);
}

void eStop() {
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, HIGH);

  analogWrite(pwm_a, 100);
  analogWrite(pwm_b, 100);

  delay(150);

  analogWrite(pwm_a, 0);
  analogWrite(pwm_b, 0);

}

void checkSensors() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  if (duration > 5820) {
    duration = 5820;
  }
  distance = (duration / 2) / 29.1;

  //-----------------------------------------------------
  //Sensor 2

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  if (duration2 > 5820) {
    duration2 = 5820;
  }
  distance2 = (duration2 / 2) / 29.1;

  //-----------------------------------------------------
  //Sensor 3

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  if (duration3 > 5820) {
    duration3 = 5820;
  }
  distance3 = (duration3 / 2) / 29.1;
}

