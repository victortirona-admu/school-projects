#include <Servo.h>
//defining Servos
Servo servoHorizontal;
int servoh = 0;
int servohLimitHigh = 180; //highest possible horizontal rotation
int servohLimitLow = 0; ////lowest possible horizontal rotation
Servo servoVertical;
int servov = 0;
int servovLimitHigh = 120; //highest possible vertical rotation
int servovLimitLow = 40; //lowest possible vertical rotation
//Assigning LDRs
int ldrtopLeft = 2; //top left LDR green
int ldrtopRight = 1; //top right LDR yellow
int ldrbotLeft = 3; // bottom left LDR blue
int ldrbotRight = 0; // bottom right LDR orange
void setup ()
{
  Serial.begin(9600);
  servoHorizontal.attach(9);
  servoHorizontal.write(0);
  servoVertical.attach(10);
  servoVertical.write(0);
  delay(500);
}
void loop()
{
  servoh = servoHorizontal.read();
  servov = servoVertical.read();
  //capturing analog values of each LDR
  int topLeft = analogRead(ldrtopLeft);
  int topRight = analogRead(ldrtopRight);
  int botLeft = analogRead(ldrbotLeft);
  int botRight = analogRead(ldrbotRight);
  Serial.print("top left: ");
  Serial.println(topLeft);
  Serial.print("top right: ");
  Serial.println(topRight);
  Serial.print("bottom left: ");
  Serial.println(botLeft);
  Serial.print("bottom right: ");
  Serial.println(botRight);
  Serial.println("-------------");
  // calculating average
  int avgtop = (topLeft + topRight) / 2; //average of top LDRs
  int avgbot = (botLeft + botRight) / 2; //average of bottom LDRs
  int avgleft = (topLeft + botLeft) / 2; //average of left LDRs
  int avgright = (topRight + botRight) / 2; //average of right LDRs
  if (avgtop < avgbot)
  {
    servoVertical.write(servov + 1);
    if (servov > servovLimitHigh)
    {
      servov = servovLimitHigh;
      servoVertical.write(servov);
      Serial.println("HIGH HAS BEEN BREACHED");
    }
    delay(5);
  }
  else if (avgbot < avgtop)
  {
    servoVertical.write(servov - 1);
    if (servov < servovLimitLow)
    {
      servov = servovLimitLow;
      servoVertical.write(servov);
    }
    delay(5);
  }
  else
  {
    servoVertical.write(servov);
  }
  if (avgleft > avgright)
  {
    servoHorizontal.write(servoh - 1);
    if (servoh > servohLimitHigh)
    {
      servoh = servohLimitHigh;
    }
    delay(5);
  }
  else if (avgright > avgleft)
  {
    servoHorizontal.write(servoh + 1);
    if (servoh <
