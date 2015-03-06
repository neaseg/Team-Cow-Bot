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
    /* MOVEMENTS BY INDEX
    0 Start Light.
    1 Forward 11 inches at 25 percent power.
    2 Turn Left 185 at 25 percent power.
    3 Forward 11 inches at 25 percent power.
    4 Turn Left 185 at 25 percent power.
    5 Forward 8 inches at 25 percent  power.
    6 Forward 25 inches at 50 percent power (climbing ramp).
    7 Forward 15 inches at 12.5 percent power ( moving to crank).
    8 ...
    */
    
    #define NUMBER_OF_OPERATIONS 8
    char operationsArray[] = { 's', 'f', 'l', 'f', 'l', 'f', 'f' };
    float paramOneArray[] = { 0, 11, 185, 11, 185, 8, 25, 15 };
    float paramTwoArray[] = { 0, 25, 25, 25, 25, 25, 50, 12.5};
    
    for(int i = 0; i < NUMBER_OF_OPERATIONS; i++){
        
        switch ( operationsArray[i] ){
            
            case s:
                start_light();
                break;
                
            case f:
                move_forward(paramOneArray[i], paramTwoArray[i]);
                break;
                
            case b:
                move_backward(paramOneArray[i], paramTwoArray[i]);
                break;
                
            case l:
                turn_left(paramOneArray[i], paramTwoArray[i]);
                break;
                
            case r:
                turn_right(paramOneArray[i], paramTwoArray[i]);
                break;
                
            case p:
                push_buttons();
                break;
                
            case t:
                toggle_switch();
                break;
                
            defualt:
                break;
        }
    }
    


return 0;
}
