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

void start_light_2(){

    //defines percent difference for start light
    #define TARGET_DIFF 15
    #define LIGHT_SAMPLES 5
    float percentDiff;
    int i;
    float ambientLightSum = 0;
    float ambientLightAvg = 0;
    float currentLight = 0;

    //Gets avg ambient light avetrage over approximately one seccond.
    for( int i = 0; i < 5; i++){
        ambientLightSum += cdscell.Value();
        Sleep(100);
    }
    ambientLightAvg = ambientLightSum / LIGHT_SAMPLES;

    //Waits for button press and depress.
    while (!buttons.MiddlePressed()){}
    while (buttons.MiddlePressed()){}

    //Reads until cdscell.Value()  is more than TARGET_DIFF % greater than ambientLightAvg.
    do{

        currentLight = cdscell.Value();
        percentDiff = 100. * (ambientLightAvg - currentLight) / currentLight;

        LCD.Clear();
        LCD.WriteLine("WAITING FOR START LIGHT");
        LCD.WriteLine("CURRENT CDS VALUE: " );
        LCD.Write(currentLight);
    } while (percentDiff < TARGET_DIFF);

    //Writes success message to screen
    LCD.Clear();
    LCD.WriteLine("START LIGHT DETECTED");
}


void start_light()
{

while (!buttons.MiddlePressed())
{
}
Sleep(1000);
while (cdscell.Value() > 0.50) //while the cds value shows there is no light on
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

void push_buttons()
{
    int redButtonOrder = RPS.RedButtonOrder();
    int whiteButtonOrder = RPS.WhiteButtonOrder();
    int blueButtonOrder = RPS.BlueButtonOrder();

    int angles[3];
    int buttons[3];


    angles[redButtonOrder - 1] =  0;// insert angle of servo to hit red button
    angles[blueButtonOrder - 1] = 0;//
    angles[whiteButtonOrder - 1] = 0;//
    int buttonsPressed = 0;

    ResetTime();
    while (30 - TimeNowSec() >= 0 ) {
    switch (buttonsPressed){

    case 0:
        servo.SetDegree(angles[0]);
        while (RPS.RedButtonPressed() == 0 && RPS.BlueButtonPressed() == 0 && RPS.WhiteButtonPressed() == 0){

         move_forward(.1, 10);
         Sleep(10);
        }
        if (RPS.RedButtonPressed() == 1)
        LCD.WriteLine("RED BUTTON PRESSED");
        else if (RPS.BlueButtonPressed() == 1)
        LCD.WriteLine("BLUE BUTTON PRESSED");
        else
        LCD.WriteLine("WHITE BUTTON PRESSED");
        buttonsPressed++;
    break;

    case 1:
        servo.SetDegree(angles[1]);
        while (RPS.RedButtonPressed() != 2 && RPS.BlueButtonPressed() != 2 && RPS.WhiteButtonPressed() != 2){

          move_forward(.1, 10);
          Sleep(10);
        }
        if (RPS.RedButtonPressed() == 2)
            LCD.WriteLine("RED BUTTON PRESSED");
        else if (RPS.BlueButtonPressed() == 2)
            LCD.WriteLine("BLUE BUTTON PRESSED");
        else
            LCD.WriteLine("WHITE BUTTON PRESSED");
            buttonsPressed++;
        break;


    case 2:
        servo.SetDegree(angles[2]);
        while (RPS.RedButtonPressed() != 3 && RPS.BlueButtonPressed() != 3 && RPS.WhiteButtonPressed() != 3){

          move_forward(.1, 10);
          Sleep(10);
        }
        if (RPS.RedButtonPressed() == 3)
            LCD.WriteLine("RED BUTTON PRESSED");
        else if (RPS.BlueButtonPressed() == 3)
            LCD.WriteLine("BLUE BUTTON PRESSED");
        else
            LCD.WriteLine("WHITE BUTTON PRESSED");
            buttonsPressed++;
        break;
        }
        }

    }
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
    move_forward(11, 25);
    Sleep(1000);
    turn_left(25, 185); // actual counts needs to be measure
    Sleep(1000);
    move_forward(11, 25);
    Sleep(1000);
    turn_left(25, 185);
    Sleep(1000);
    move_forward(8, 25);
    Sleep(1000);
}
void climb_ramp()
{
    LCD.Clear();
    LCD.WriteLine("ATTEMPTING TO CLIMB RAMP");
    Sleep(100);
    LCD.WriteLine("I THINK I CAN, I THINK I CAN...");
    move_forward(25,50);
    LCD.Clear();
    LCD.Write("WHERE AM I?");

}
int main(void)
{
    start_light_2();
    move_to_Ramp();
    climb_ramp();
    move_forward(15,12.5);

return 0;
}
