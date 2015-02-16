#include <FEHUtility.h>
#include <FEHServo.h>

// declare servo arm

FEHServo servo(FEHServo::Servo7);

int main(void)

{

  // calibrate servo
 servo.Calibrate();
 
 // actual values need to be checked
 servo.SetMin(998);
 servo.SetMax(1852);
 servo.
 
}
