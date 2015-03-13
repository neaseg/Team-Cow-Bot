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

void start_light(){
    
    //defines percent difference for start light 
    #define TARGET_DIFF 10;
    #define LIGHT_SAMPLES 5;
    float percentDiff;
    int i;
    float ambientLightSum = 0;
    float ambientLightAvg = 0;

    //Gets avg ambient light avetrage over approximately one seccond.
    for( int i = 0; i < 5; i++){
        ambientLightSum += cdscell.Value();
        Sleep(100);
    }
    ambientLightAvg = AmbientLightSum / LIGHT_SAMPLES;

    //Waits for button press and depress.
    while (!buttons.MiddlePressed()){}
    while (buttons.MiddlePressed()){}
    
    //Reads until cdscell.Value()  is more than TARGET_DIFF % greater than ambientLightAvg.
    do{
        
        LCD.Clear();
        LCD.WriteLine("WAITING FOR START LIGHT");
        LCD.WriteLine("CURRENT CDS VALUE: " );
        LCD.Write(cdscell.Value());
    } while (cdscell.Value() > 3.0);
    
    //Writes success message to screen.
    LCD.Clear();
    LCD.WriteLine("START LIGHT DETECTED");
}


void move_forward(float inches, int percent) //using encoders
{
//Reset encoder counts
right_encoder.ResetCounts();
left_encoder.ResetCounts();
//Calculate corresponding count values
float counts = (inches * 318) / (2.5 * 3.14159);
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
right_motor.SetPercent(percent);
left_motor.SetPercent(0);
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
right_motor.SetPercent(0);
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
move_forward(9, 25);
turn_left(50, 337); // actual counts needs to be measure
move_forward(14, 25);
turn_left(50, 337);
move_forward(4, 25);
}
void climb_ramp()
{
right_encoder.ResetCounts();
left_encoder.ResetCounts();
move_forward(13,25);
}
int main(void)
{
    start_light();
    move_to_Ramp();
    climb_ramp();

return 0;
}
