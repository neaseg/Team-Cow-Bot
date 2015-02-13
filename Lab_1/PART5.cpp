#include <FEHUtility.h>
#include <FEHServo.h>

// declare servo arm

FEHServo servo(FEHServo::Servo7);

int main(void)

{

  // calibrate servo
 servo.Calibrate();
 
}
