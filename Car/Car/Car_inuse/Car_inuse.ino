#define trigPin 12 // fram
#define trigPin2 11 // höger
#define trigPin3 7 // vänster
#define echoPin 13 // fram echopin
#define echoPin2 10 // vänster echopin
#define echoPin3 6 // höger echopin

long duration, distance; // fram
long duration2, distance2; // höger
long duration3, distance3; // vänster

int pwm_a = 3;  //PWM control for motor outputs 1 and 2 
int pwm_b = 9;  //PWM control for motor outputs 3 and 4 
int dir_a = 2;  //direction control for motor outputs 1 and 2 
int dir_b = 8;  //direction control for motor outputs 3 and 4 

int leftDelay = 30;
int rightDelay = 30;
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
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
//  turnRight();
//  //driveForward(250);
//  delay(1000);
  checkSensors();
  //Serial.println(distance);
  while (distance > 30) {
    delay(50);
    driveForward(10);
    checkSensors();
    //Serial.println(distance);
  }

  if (distance < 30) { // hinder framför
    Serial.println("Hinder");
    if((distance < 30) && (distance3 < 30)) { // om hinder vänster, svänger höger
      Serial.println("Höger sväng");
      turnRight();
      eStop();
    } else {
      if((distance < 30) && (distance2 < 30)) { // om hinder höger, svänger vänster
        Serial.println("Vänster sväng");
        turnLeft();
        eStop();
      } else {
        Serial.println("Vänder"); // vänder
        turnAround();
        eStop();
      }
    }
  }
}

void turnLeft() {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, LOW);  
  
  analogWrite(pwm_a, 70);  
  analogWrite(pwm_b, 70);

  delay(leftDelay);
  stopCarLeft();
}

void turnRight() {
  digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, HIGH);  
  
  analogWrite(pwm_a, 70);  
  analogWrite(pwm_b, 70);

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
  
  analogWrite(pwm_a, 70);  
  analogWrite(pwm_b, 70);

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
  
  analogWrite(pwm_a, 40);  
  analogWrite(pwm_b, 40);

  delay(15);

  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
}

void stopCarRight() {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, LOW);  
  
  analogWrite(pwm_a, 40);  
  analogWrite(pwm_b, 40);

  delay(15);

  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
}

void eStop() {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH);  
  
  analogWrite(pwm_a, 100);  
  analogWrite(pwm_b, 100);

  delay(15);

  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
  
}

void checkSensors() {
  digitalWrite(trigPin, LOW); // fram
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);

  digitalWrite(trigPin2, LOW); // höger
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin2, LOW);

  digitalWrite(trigPin3, LOW); // vänster
  delayMicroseconds(2);

  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin3, LOW);
  
  duration = pulseIn(echoPin, HIGH); // fram
  if (duration > 5820) {
    duration = 5820;
  }
  distance = (duration/2) / 29.1;

  duration2 = pulseIn(echoPin2, HIGH); // höger
  if(duration2 < 5820) {
    duration2 = 5820;
  }
  distance2 = (duration2/2) / 29.1;

  duration3 = pulseIn(echoPin3, HIGH); // vänster
  if(duration3 < 5820) {
    duration3 = 5820;
  }
  distance3 = (duration3/2) / 29.1;
}


