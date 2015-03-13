#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor0);
FEHMotor left_motor(FEHMotor::Motor1);


void move_forward(int percent, int counts) //using encoders
{
 //Reset encoder counts
 right_encoder.ResetCounts();
 left_encoder.ResetCounts();
 //Set both motors to desired percent
 right_motor.SetPercent(percent);
 left_motor.SetPercent(percent);//13 v15FEB2015, CPH KJW
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


 right_motor.SetPercent(percent);
 left_motor.SetPercent(-1 *percent);

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

 right_motor.SetPercent(-1 * percent);
 left_motor.SetPercent(percent);

 //While the average of the left and right encoder are less than counts,
 //keep running motors

 while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

 //Turn off motors
 right_motor.Stop();
 left_motor.Stop();
}

int main(void)
{
 int motor_percent = 75; //Input power level here
 int turning_motor_percent = 50;
 int expected_counts_14 = 297.09; //Input theoretical counts (14 inches) here
 //Initialize the screen (GO BUCKS!)

 int expected_counts_10 = 212.14;
 int expected_counts_4 = 84.87;
 int expected_turn_counts = 105; //Input theoretical counts here

 LCD.Clear( FEHLCD::Scarlet );
 LCD.SetFontColor( FEHLCD::Gray );

 LCD.WriteLine("Shaft Encoder Lab Test");
 LCD.WriteLine("Press middle button");
 while(!buttons.MiddlePressed()); //Wait for middle button to be pressed
 while(buttons.MiddlePressed()); //Wait for middle button to be unpressed

 move_forward(motor_percent, expected_counts_14); //see function
 Sleep(1.0); //Wait for counts to stabilize


 turn_left(turning_motor_percent, expected_turn_counts);
 Sleep(1.0); //Wait for counts to stabilize

 move_forward(motor_percent, expected_counts_10);
 Sleep(1.0);

 turn_left(turning_motor_percent, expected_turn_counts);
 Sleep(1.0); //Wait for counts to stabilize

 move_forward(motor_percent, expected_counts_4);
 Sleep(1.0);

/*
 //Print out data
 LCD.Write("Theoretical Counts: ");
 LCD.WriteLine(expected_counts);
 LCD.Write("Motor Percent: ");
 LCD.WriteLine(motor_percent);
 LCD.Write("Actual LE Counts: ");
 LCD.WriteLine(right_encoder.Counts());
 LCD.Write("Actual RE Counts: ");
 LCD.WriteLine(left_encoder.Counts());
*/
 return 0;
}
