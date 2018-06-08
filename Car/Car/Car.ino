#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 70 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(4, 5, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(6, 7, MAX_DISTANCE), 
  NewPing(10, 11, MAX_DISTANCE)
};

long distance[3] = {0, 0, 0};

int pwm_a = 3;  //PWM control for motor outputs 1 and 2
int pwm_b = 9;  //PWM control for motor outputs 3 and 4
int dir_a = 2;  //direction control for motor outputs 1 and 2
int dir_b = 8;  //direction control for motor outputs 3 and 4

int leftDelay = 415;
int rightDelay = 415;
int rotateDelay = 2 * rightDelay;


void setup() {
  Serial.begin(9600);

  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);

  analogWrite(pwm_a, 100);  //set both motors to run at (100/255 = 39)% duty cycle (slow)
  analogWrite(pwm_b, 100);
}

void loop() {
  checkSensors();
  Serial.println(distance[0]);
  if (distance[0] > 20) {
    driveForward(1);
    checkSensors();
    //Serial.println(distance[0]);
  }

  if (distance[0] < 20) {
    eStop();
    if (distance[1] > distance[2]) {
      if (distance[0] < 20) {
        turnRight(5);
        checkSensors();
        Serial.println("1oooooooooooooooooooooooooo");

      }
    } else if (distance[1] < distance[2]) {
      if (distance[0] < 20) {
        turnLeft(5);
        checkSensors();
        Serial.println("roooooooooooooooooooo");

      }
    } else {
      int randInt = random(0, 2);
      switch (randInt) {
        case 0:
          while (distance[0] < 20) {
            turnLeft(15);
            //Serial.println(distance[0]);
            Serial.println("Case 0");
            checkSensors();
          }
          break;
        case 1:
          while (distance[0] < 20) {
            turnRight(15);
            //Serial.println(distance[0]);
            Serial.println("Case 1");
            checkSensors();
          }
          break;
        case 2:
          //turnAround();
          //Serial.println(distance);

          break;
      }
    }
  }
}

void turnLeft(int turnTime) {
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, LOW);

  analogWrite(pwm_a, 90);
  analogWrite(pwm_b, 90);

  delay(turnTime);
  //stopCarLeft();
}

void turnRight(int turnTime) {
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, HIGH);

  analogWrite(pwm_a, 90);
  analogWrite(pwm_b, 90);

  delay(turnTime);
  //stopCarRight();
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
for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(29); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i);
    Serial.print("=");
    Serial.print(distance[i]);
    Serial.print("cm ");
    distance[i] = sonar[i].ping_cm();
  }
  Serial.println();
}

