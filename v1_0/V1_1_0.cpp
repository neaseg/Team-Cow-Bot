#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_2);
FEHMotor right_motor(FEHMotor::Motor0);
FEHMotor left_motor(FEHMotor::Motor1);
FEHServo servo(FEHServo::Servo7);
AnalogInputPin cdscell(FEHIO::P1_0);

void start_light()
{
while (!buttons.MiddlePressed())
{
}
Sleep(1000);
while (cdscell.Value() > 0.60) //while the cds value shows there is no light on
{
LCD.Clear();
LCD.WriteLine("WAITING FOR START LIGHT");
LCD.WriteLine("CURRENT CDS VALUE: " );
LCD.Write(cdscell.Value());
}
LCD.Clear();
LCD.WriteLine("START LIGHT DETECTED");
Sleep(1000);
}
void move_forward(float inches, int percent) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    //Calculate corresponding count values
    float counts = (inches * 318) / (3.0 * 3.14159);
    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-1 * percent);
    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_right(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    //Set both motors to desired percent
    //hint: set right motor forward, left motor backward
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(-percent);
    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    //Set both motors to desired percent
    //hint: set right motor forward, left motor backward
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);
    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void move_to_Ramp()
{
    move_forward(5, 25);
    Sleep(500);
    turn_left(25, 96); // actual counts needs to be measure
    Sleep(500);
    move_forward(6, 25);
    Sleep(500);
    turn_left(25, 96);
    Sleep(500);
    move_forward(4, 25);
    Sleep(500);
}
void climb_ramp()
{
    LCD.Clear();
    LCD.WriteLine("ATTEMPTING TO CLIMB RAMP");
    Sleep(100);
    //move_forward(13,25);
}
int main(void)
{
    start_light();
    move_to_Ramp();
    climb_ramp();

return 0;
}
