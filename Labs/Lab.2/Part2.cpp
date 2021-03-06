/*Written By: Krishna Ganesan and Maxwell Powell*/
/*Date Created: 2/18/15*/
/*Revision: 0*/
/*Date Revised: 2/19/15*/
/*Program Function: Runs Motors to Move Forward and Turn on Command.*/

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

void check_x_plus(float x_coordinate) //use RPS to check x location while robot is facing the +x direction
{

    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(100);
            left_motor.SetPercent(100);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);

        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(-100);
            left_motor.SetPercent(-100);
            Sleep(100);
            right_motor.SEtPercent(0);
            left_motor.SEtPercent(0);
        }
    }
}

void check_y_minus(float y_coordinate)//use RPS to check y location while robot is facing the -y direction
{
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
        {
            if(RPS.Y() > y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction
                right_motor.SetPercent(100);
                left_motor.SetPercent(100);
                Sleep(100);
                right_motor.SetPercent(0);
                left_motor.SetPercent(0);
            }
            else if(RPS.Y() < y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction
                right_motor.SetPercent(-100);
                left_motor.SetPercent(-100);
                Sleep(100);
                right_motor.SetPercent(0);
                left_motor.SetPercent(0);
            }
        }
}

void check_y_plus(float y_coordinate) //use RPS to check y location while robot is facing the +y direction
{
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
    {
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(100);
            left_motor.SetPercent(100);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(-100);
            left_motor.SetPercent(-100);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
    }
}

void check_heading(float heading) //using RPS
{
    //you will need to fill out this one yourself and take into account
    //the edge conditions (when you want the robot to go to 0 degrees
    //or close to 0 degrees and you are at an angle like 357 degrees)

    //check whether the robot is within an acceptable range
    while(RPS.Heading() < heading - 1 || RPS.Heading() > heading + 1)
    {
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(100);
            left_motor.SetPercent(100);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(-100);
            left_motor.SetPercent(-100);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
    }
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

 float x_coordinate_A = 18.3;
 float y_coordiante_A =  31;
 float x_coordinate_B = 18.4;
 float y_coordiante_B =  16.8;
 float x_coordinate_C = 26;
 float y_coordiante_C =  13.6;
 float x_coordinate_D = 28.9;
 float y_coordiante_D = 18.1;

 float heading_A = 2.4;
 float heading_B = 2.4;
 float heading_C = 91;
 float heading_D = 182;

         //Initialize RPS and declare any variables you might need
 move_forward(percent ,expected_counts_14); //drive 14 inches in –y direction

 check_y_minus(y_coordinate_B); //check that we are at the y coordinate of point B +/- 1 inch

 turn_left(turning_motor_percent ,expected_turn_counts; //turn left 90 degrees

 check_heading(heading_A); //check that the heading is actually correct +/- 2 degrees

 move_forward(motor_percent ,expected_counts_10); //drive 10 inches in +x direction

 check_x_plus(x_coordinate_C); //check that we are at the x coordinate of point C +/- 1 inch

 turn_left(percent ,expected_turn_counts); //turn left 90 degrees

 check_heading(heading + 90); //check that the heading is actually correct +/- 2 degrees

 move_forward(motor_percent ,expected_counts_4); //drive 4 inches in +y direction

 check_y_plus(y_coordinate_D); //check that we are at the y coordinate of point D +/- 1 inch

 check_heading( heading + 180)





 return 0;
}
