/*Written By: Krishna Ganesan*/
/*Date Created: 2/13/15*/
/*Revision: 0*/
/*Date Revised: 2/15/15*/
/*Program Function: Changes the position of the servo based on the cds cell value.*/

#include <FEHUtility.h>
#include <FEHServo.h>

// declare servo arm

FEHServo servo(FEHServo::Servo7);
AnalogInputPin cdscell(FEHIO::P1_0);
int main(void)

{

  // calibrate servo
 servo.Calibrate();
 
 // actual values need to be checked
 servo.SetMin(998);
 servo.SetMax(1852);
 
 while (1)
 {
 servo.SetAngle(cdscell.Value() * (180/3.3));
 }
}
