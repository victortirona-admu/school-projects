int i;
int run1 = 9; // 0 to 255, 255 = max, 0 = stop
int run2 = 10; // 0 to 255, 255 = max, 0 = stop
int dir1 = 8;
int dir2 = 11;
int LS1, LS2, LS3, col1, col2, col3;
void setup() {
  Serial.begin(9600);
  for (i = 2; i <= 7; i = i + 1)
    pinMode(i, INPUT); //sensors
  for (i = 8; i <= 11; i = i + 1) {
    pinMode(i, OUTPUT); //motor control
  }
  delay(10);
  //stop motors
  for (i = 8; i <= 11; i = i + 1)
    digitalWrite(i, LOW);
}
void loop() { //main routine here
  // motor1
  digitalWrite(dir1, HIGH); //direction control of motor1, 1 = forward
  analogWrite(run1, 170); //speed control of motor1, 0 =stop, 255 =fastest RIGHT
  // motor2
  digitalWrite(dir2, HIGH); //direction control of motor2, 1 = forward
  analogWrite(run2, 180); //speed control of motor2, 0 =stop, 255 =fastest LEFT
  delay(10000);
  digitalWrite(dir1, LOW); //direction control of motor1, 1 = forward
  analogWrite(run1, 0); //speed control of motor1, 0 =stop, 255 =fastest
  digitalWrite(dir2, LOW); //direction control of motor1, 1 = forward
  analogWrite(run2, 0); //speed control of motor1, 0 =stop, 255 =fastest
  delay(2000);
  while (1);
}
