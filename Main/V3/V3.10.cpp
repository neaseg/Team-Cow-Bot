#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P0_2);
DigitalEncoder left_encoder(FEHIO::P0_0);
FEHMotor right_motor(FEHMotor::Motor0);
FEHMotor left_motor(FEHMotor::Motor1);
FEHServo liftServo(FEHServo::Servo7);
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

void check_x_plus(float x_coordinate) //use RPS to check x location while robot is facing the +x direction
{

    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(-10);
            left_motor.SetPercent(10);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);

        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(10);
            left_motor.SetPercent(-10);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
    }
}

void check_x_minus(float x_coordinate) //use RPS to check x location while robot is facing the +x direction
{

    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(10);
            left_motor.SetPercent(-10);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);

        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(-10);
            left_motor.SetPercent(10);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
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
                right_motor.SetPercent(-10);
                left_motor.SetPercent(10);
                Sleep(100);
                right_motor.SetPercent(0);
                left_motor.SetPercent(0);
            }
            else if(RPS.Y() < y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction
                right_motor.SetPercent(10);
                left_motor.SetPercent(-10);
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
            right_motor.SetPercent(10);
            left_motor.SetPercent(-10);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(-10);
            left_motor.SetPercent(10);
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
    float currentHeading = RPS.Heading();

    if (heading < 358 || heading > 2 ){
    while(currentHeading < heading - 2 || currentHeading > heading + 2)
    {
        LCD.Clear();
        LCD.WriteLine(RPS.Heading());
        if (currentHeading <= 1)
            currentHeading += 360;


        if(currentHeading > heading)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(-10);
            left_motor.SetPercent(-10);
            Sleep(25);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
        else if(currentHeading < heading)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(10);
            left_motor.SetPercent(10);
            Sleep(25);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
        currentHeading = RPS.Heading();
    }
    }
    else
        while (currentHeading < 2 || currentHeading > 358) {
            if(currentHeading > 2 && currentHeading > 180)
            {
                //pulse the motors for a short duration in the correct direction
                right_motor.SetPercent(-10);
                left_motor.SetPercent(-10);
                Sleep(25);
                right_motor.SetPercent(0);
                left_motor.SetPercent(0);
            }
            else if(currentHeading < 358 && currentHeading > 180)
            {
                //pulse the motors for a short duration in the correct direction
                right_motor.SetPercent(10);
                left_motor.SetPercent(10);
                Sleep(25);
                right_motor.SetPercent(0);
                left_motor.SetPercent(0);
            }
            currentHeading = RPS.Heading();
        }
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

void move_backwards(float inches, int percent) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    //Calculate corresponding count values
    float counts = (inches * 318) / (3.0 * 3.14159);
    //Set both motors to desired percent
    right_motor.SetPercent(-1*percent);
    left_motor.SetPercent(percent);
    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void move_forward_time(float timeMsec, int percent) //using encoders
{

    right_motor.SetPercent(percent);
    left_motor.SetPercent(-1 * percent);
    ResetTime();
    while(timeMsec - TimeNowMSec() >=0 );

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void move_backwards_time(float timeMsec, int percent) //using encoders
{
    right_motor.SetPercent(-1 * percent);
    left_motor.SetPercent(percent);
    ResetTime();
    while(timeMsec - TimeNowMSec() >=0 );

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_right(int percent, int degrees) //using encoders
{
    float counts = 210/90.0 * degrees;
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
void turn_left(int percent, int degrees) //using encoders
{
    float counts = 210/90.0 * degrees;
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


void turn_left_degrees(int percent, float degrees)
{
    float currentHeading = RPS.Heading();
    float endHeading = currentHeading + degrees;

    if (endHeading <= 358)
    {
        while (RPS.Heading() <= endHeading + 1.9 || RPS.Heading() >= endHeading - 1.9) {
        right_motor.SetPercent(percent);
        left_motor.SetPercent(percent);
        }
    }
    else if (endHeading >= 360)
    {
        endHeading -= 360;
        while (RPS.Heading() < 360)
        {
            right_motor.SetPercent(percent);
            left_motor.SetPercent(percent);

        }

        Sleep(250);

        while (RPS.Heading() <= endHeading + 1.9 || RPS.Heading() >= endHeading - 1.9)
        {
            right_motor.SetPercent(percent);
            left_motor.SetPercent(percent);

        }
    }


}

void turn_right_degrees(int percent, float degrees)
{
    float currentHeading = RPS.Heading();
    float endHeading = currentHeading - degrees;

    if (endHeading >= 2)
    {
        while (RPS.Heading() <= endHeading + 1.9 || RPS.Heading() >= endHeading - 1.9) {
        right_motor.SetPercent(-percent);
        left_motor.SetPercent(-percent);
        }

    }
    else if (endHeading <= 0)
    {
        endHeading += 360;
        while (RPS.Heading() >= 0)
        {
            right_motor.SetPercent(-percent);
            left_motor.SetPercent(-percent);

        }

        Sleep(250);

        while (RPS.Heading() <= endHeading + 1.9 || RPS.Heading() >= endHeading - 1.9)
        {
            right_motor.SetPercent(percent);
            left_motor.SetPercent(percent);

        }
    }


}


void push_buttons()
{
    int redButtonOrder = RPS.RedButtonOrder();
    int whiteButtonOrder = RPS.WhiteButtonOrder();
    int blueButtonOrder = RPS.BlueButtonOrder();

    LCD.Clear();
    LCD.WriteLine("Red Button Order: ");
    LCD.WriteLine(redButtonOrder);
    LCD.WriteLine("White Button Order: ");
    LCD.WriteLine(whiteButtonOrder);
    LCD.WriteLine("Blue Button Order: ");
    LCD.WriteLine(blueButtonOrder);
    Sleep(1000);
    int angles[3];


    angles[redButtonOrder - 1] =  110;// insert angle of servo to hit red button
    angles[blueButtonOrder - 1] = 137;//
    angles[whiteButtonOrder - 1] = 121;//
    int buttonsPressed = 0;
    LCD.Clear();

    liftServo.SetMin(500);
    liftServo.SetMax(2500);

   /* TEST
    liftServo.SetDegree(angles[0]);
    Sleep(1000);

    liftServo.SetDegree(angles[1]);
    Sleep(1000);
    liftServo.SetDegree(angles[2]);
    LCD.WriteLine("Finished");

    */


    ResetTime();
    bool done = false;
    while (30 - TimeNowSec() >= 0 && done == false ) {
    switch (buttonsPressed){

    case 0:
        liftServo.SetDegree(angles[0]);
        Sleep(100);


         move_backwards_time(1200, 20);

         Sleep(100);
         move_forward(1,15);

        if (RPS.RedButtonPressed() == 1) {
        LCD.WriteLine("RED BUTTON PRESSED");
        }
        else if (RPS.BlueButtonPressed() == 1) {
        LCD.WriteLine("BLUE BUTTON PRESSED");
        }
        else if (RPS.WhiteButtonPressed() == 1){
        LCD.WriteLine("WHITE BUTTON PRESSED");
        }
        else
            LCD.WriteLine("NO BUTTON PRESSED");

        move_forward(5, 10);
        turn_right(10, 8); //accounting for not driving straight
        buttonsPressed++;
    break;

    case 1:
        liftServo.SetDegree(angles[1]);
          move_backwards_time(2000, 20);


          Sleep(10);
        move_forward(1,15);
        if (RPS.RedButtonPressed() == 2) {
            LCD.WriteLine("RED BUTTON PRESSED");
        }
        else if (RPS.BlueButtonPressed() == 2){
            LCD.WriteLine("BLUE BUTTON PRESSED");
        }
        else if (RPS.WhiteButtonPressed() == 2){
            LCD.WriteLine("WHITE BUTTON PRESSED");
        }
        else{
            LCD.WriteLine("NO BUTTON PRESSED");
        }
            move_forward(5, 10);
            turn_right(10, 8); //accounting for not driving straight

            buttonsPressed++;
        break;


    case 2:
        liftServo.SetDegree(angles[2]);


          move_backwards_time(2000, 20);


          Sleep(10);
          move_forward(1,15);
          turn_right(10, 13); //accounting for not driving straight


        if (RPS.RedButtonPressed() == 3)
            LCD.WriteLine("RED BUTTON PRESSED");
        else if (RPS.BlueButtonPressed() == 3)
            LCD.WriteLine("BLUE BUTTON PRESSED");
        else if (RPS.WhiteButtonPressed() == 3)
            LCD.WriteLine("WHITE BUTTON PRESSED");
        else
            LCD.WriteLine("NO BUTTON PRESSED");

            move_forward(5, 10);
            done = true;
        break;

    default:
        LCD.Clear();
        LCD.Write("YOU DONE MESSED UP A - A RON");
        }
        }
    LCD.WriteLine("BUTTONS PRESSED SUCCESSFULLY OR TIME EXPIRED");

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
    move_backwards(27,50);
    LCD.Clear();
    LCD.Write("WHERE AM I?");
    check_y_plus(50);
    check_heading(360);



}

void calibrate_scoop_servo()
{
    liftServo.Calibrate();
   /* liftServo.SetMin(500);
    liftServo.SetMax(2119);

     for (int i = 140; i >= 0 ; i--) {
     liftServo.SetDegree(i);
     LCD.Clear();
     LCD.WriteLine("SERVO ANGLE IS SET AT:");
     LCD.Write(i);
     Sleep(200);

     }
*/
}


void scoop_salt()
{
    liftServo.SetMin(500);
    liftServo.SetMax(2182);
    liftServo.SetDegree(90);
    Sleep(1000);
    liftServo.SetDegree(180);
    move_backwards(3, 25);
    Sleep(500);

    move_backwards(3, 25);
    Sleep(500);
    //back up to raise servo
    move_forward(2, 25);
    liftServo.SetDegree(145);
    turn_left(10, 120);

    //head almost to ramp
    move_backwards(11, 25);

    turn_left(10, 20);
    check_heading(360);


    /*
    move_forward(3, 10);
    liftServo.SetDegree(145);
    move_forward(4, 25);
    */


}

void deposit_salt()
{
    turn_left(20, 30);
    check_heading(30);
  //  liftServo.SetDegree(168);
  //  Sleep(1000);
    move_backwards(10, 25);
    check_heading(30);
    //check_x_plus(12.5);
    //move_forward(2.5, 25);
    turn_left(20, 60);
    check_heading(90);
    move_backwards(13, 25);

    int bang = 0;
    while (bang < 10)
{
        turn_right(25, 5);
        turn_left(15, 3);
        bang++;
    }
    /*turn_right(10, 45);
    check_heading(45);
    move_backwards(6, 25);
    liftServo.SetDegree(140);
    move_forward(6, 25);
    */
}

int main(void)
{

/*
    move_backwards(15, 25);
    Sleep(1000);
    move_forward(15,25);
    Sleep(1000);
    move_backwards_time(3000, 25);
    Sleep(1000);
    move_forward_time(3000, 25);
*/

   // start_light_2();
   // move_to_Ramp();
   // climb_ramp();
   // move_forward(15,12.5);
   // calibrate_scoop_servo();
    //Sleep(10000);
    //scoop_salt();
    //push_buttons();

    /*
   //PERFORMANCE TEST 3
    RPS.InitializeMenu();
    climb_ramp();
    turn_left(25, 105);
    move_backwards(11, 25);
   push_buttons();
    */

    /*// RPS heading test
     RPS.InitializeMenu();
     while (!buttons.MiddlePressed()){
     LCD.WriteLine(RPS.Heading());
     LCD.WriteLine(RPS.X());
     LCD.WriteLine(RPS.Y());
     Sleep(250);
     LCD.Clear();
     }
     */


    liftServo.SetMin(500);
    liftServo.SetMax(2182);
    //PERFORMANCE TEST 4
    RPS.InitializeMenu();
    liftServo.SetDegree(45);
    Sleep(1000);
  //  start_light_2();
    move_backwards(12, 25);
    check_heading(180);
    turn_left(20, 40);// may need to revert to 105
    check_heading(220);
    move_backwards(9, 25);
    check_heading(220);

    scoop_salt();
    climb_ramp();
    deposit_salt();



return 0;
}
