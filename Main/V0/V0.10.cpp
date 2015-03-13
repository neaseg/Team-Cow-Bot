#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>

ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
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

    while (cdscell.Value() > .85) //while the cds value shows there is no light on
    {
        LCD.Clear();
        LCD.WriteLine("WAITING FOR START LIGHT");
    }

    LCD.Clear();
    LCD.WriteLine("START LIGHT DETECTED");


}

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


void move_to_Ramp()
{

}

void climb_ramp()
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

}

int main(void)
{
    ButtonBoard buttons( FEHIO::Bank3 );

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    while( true )
    {
        if( buttons.MiddlePressed() )
        {
            LCD.WriteLine( "Hello World!" );
            Sleep( 100 );
        }
    }
    return 0;
}

