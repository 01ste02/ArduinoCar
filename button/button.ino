int leftButton = A0;
int rightButton = A1;

int buttonStateL = 0;
int buttonStateR = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonStateL = digitalRead(leftButton);
  buttonStateR = digitalRead(rightButton);

  if((buttonStateL == LOW) && (buttonStateR == LOW)) {
    driveForward(10);
    buttonStateL = digitalRead(leftButton);
    buttonStateR = digitalRead(rightButton);
  } else {
    if(buttonStateL == LOW) {
      turnRight(5);
      eStop();
    } else {
      if(buttonStateR == LOW) {
        turnLeft(5);
        eStop();
      }
    }
  }
}

