/*Written By: Krishna Ganesan*/
/*Date Created: 2/13/15*/
/*Revision: 0*/
/*Date Revised: 2/15/15*/
/*Program Function: Changes the position of the servo based on the cds cell value.*/

#include <FEHUtility.h>
#include <FEHServo.h>

// declare servo arm and cdscell

FEHServo servo(FEHServo::Servo7);
AnalogInputPin cdscell(FEHIO::P1_0);
int main(void)

{

  // calibrate servo
 servo.Calibrate();
 
 // sets the values of the minimum and maximum allowed angle
 //calculated from the calibration process
 servo.SetMin(998);
 servo.SetMax(1852);
 
 //while loop that runs indefinately
 while (1)
 {
   //Changes the angle of the servo based on the value of the cds cell
 servo.SetAngle(cdscell.Value() * (180/3.3));
 }
}
