/*
*
*   This version is for the head to head final competition.
*   Shit is going to go sooooo fast
*
*/

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>
#include <stdlib.h>
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P2_7);
DigitalEncoder left_encoder(FEHIO::P2_0);
FEHMotor right_motor(FEHMotor::Motor0);
FEHMotor left_motor(FEHMotor::Motor1);
FEHServo liftServo(FEHServo::Servo6);\
FEHServo crankServo(FEHServo::Servo4);
AnalogInputPin cdscell(FEHIO::P0_0);

//CAN GAIN ONE SECOND BY TAKING DIRECT SAMPLE
//EVERYTHING UNNECESSARY HAS BEEN TAKEN OUT
void start_light_2(){

    //defines percent difference for start light
    #define TARGET_DIFF 30
    #define LIGHT_SAMPLES 5
    float percentDiff;
    float ambientLight = 0;
    float currentLight = 0;

    //STRAIGHT READS IN THE FLIPPIN LIGHT
    ambientLight = cdscell.Value();

    //Reads until cdscell.Value()  is more than TARGET_DIFF % greater than ambientLightAvg.
    do{
        currentLight = cdscell.Value();
        percentDiff = 100. * (ambientLight - currentLight) / currentLight;
    } while (percentDiff < TARGET_DIFF);
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
                Sleep(30);
                right_motor.SetPercent(0);
                left_motor.SetPercent(0);
                Sleep(30);
            }
            else if(RPS.Y() < y_coordinate)
            {
                //pulse the motors for a short duration in the correct direction
                right_motor.SetPercent(10);
                left_motor.SetPercent(-10);
                Sleep(30);
                right_motor.SetPercent(0);
                left_motor.SetPercent(0);
                Sleep(30);
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

    if (heading < 359 && heading > 1 ){
    while(currentHeading < heading - 1 || currentHeading > heading + 1)
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
        while (currentHeading > 2  && currentHeading < 358) {
            if(currentHeading > 2 && currentHeading < 180)
            {
                //pulse the motors for a short duration in the correct direction
                right_motor.SetPercent(-10);
                left_motor.SetPercent(-10);
                Sleep(25);
                right_motor.SetPercent(0);
                left_motor.SetPercent(0);
            }
            else //if(currentHeading < 358 && currentHeading > 180)
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
    float perkent = percent;
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    //Calculate corresponding count values
    float counts = (inches * 318) / (3.0 * 3.14159);
    //Set both motors to desired percent
    right_motor.SetPercent(perkent - 2.25 );
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
    float currentHeading = RPS.Heading();
    float endHeading = RPS.Heading();
    if (currentHeading + degrees <= 360)
    {
         endHeading = currentHeading + degrees;
    }
    else
    {
        endHeading = abs(int(currentHeading + degrees - 360));
    }
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

    //check_heading(endHeading);





}
void turn_left(int percent, int degrees) //using encoders
{

    float currentHeading = RPS.Heading();
    float endHeading = currentHeading;
    if (currentHeading + degrees < 360)
    {
         endHeading = currentHeading + degrees;
    }
    else
    {
         endHeading = abs(int(currentHeading + degrees - 360));
    }
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

    //check_heading(endHeading);
}

//NEW AND IMPROVED!!!
//SPEED IS CONTROLLED BY A CONSTANT
//WE'LL MAKE IT FAST AS POSSIBLE
//CHANGES:
// 1 - WE AIN'T WRITING SHIT TO THE SCREEN NO MORE
// 2 - TOOK OUT SOME COMMENTED THINGS
// 3 - ADDED CONSTANTS
// 4 - MADE SOME STUFF MOAR PRETTY
// 5 - REMOVED UNUSED VARIABLES
void push_buttons()
{
    #define sleepRate 10 //PREVIOUS WAS EQUIVALENT TO (sleepRate = 50)
    int redButtonOrder = RPS.RedButtonOrder();
    int whiteButtonOrder = RPS.WhiteButtonOrder();
    int blueButtonOrder = RPS.BlueButtonOrder();
    int angles[3];
    int currentAngle = 118; //NOT SURE WHERE THIS COMES FROM >> KINDA SCARED

    angles[redButtonOrder - 1] =  94;// insert angle of servo to hit red button
    angles[blueButtonOrder - 1] = 120;//
    angles[whiteButtonOrder - 1] = 107;//
    
    liftServo.SetMin(500);
    liftServo.SetMax(2500);

    for(int i = 0; i < 3; i++){

        while (currentAngle != angles[i]) {
               if (angles[i] < currentAngle)
            {
               liftServo.SetDegree(currentAngle - 1);
               Sleep(sleepRate);
               currentAngle -= 1;
            }
               else
        {
               liftServo.SetDegree(currentAngle + 1);
               Sleep(sleepRate);
               currentAngle += 1;

    }
    }
    //REMOVED 1SEC SLEEP HERE
        ResetTime();

         move_backwards_time(900, 20); //WAS 1050 (going into buttons)
         move_forward(3, 50); //WAS (3.5, 15) (backing up)
         check_heading(45); //VERIGYING THAT ALL IS GUCCI
    }
}

//CHANGES:
// 1 - REMOVED 5SEC OF SLEEP
// 2 - MADE MOVEMENTS TWICE AS FAST
// NOTE: NO RPS CHECKS ARE MADE >> WE SHOULD MEASURE POINTS VIA SLOW CODE AND CHECK HERE
void move_to_Ramp()
{
    move_forward(11, 50); //WAS (11, 25)
    //REMOVED ONE SECOND SLEEP
    turn_left(25, 90); // actual counts needs to be measure
    //REMOVED ONE SECOND SLEEP
    move_forward(11, 50); //WAS (11, 25)
    //REMOVED ONE SECOND SLEEP
    turn_left(25, 90);
    //REMOVED ONE SECOND SLEEP
    move_forward(8, 50); //WAS (8, 25)
    //REMOVED ONE SECOND SLEEP
}

//CHANGES:
// 1 - REMOVED UNNESSACARY 'SHIT'
// 2 - REMOVED A LITTLE SLEEP
// 3 - SPEED IT UP
void climb_ramp()
{
    check_heading(360);
    //REMOVED SLEEP100
    move_backwards(20.5,50);
    check_heading(360);
    move_backwards(2.5, 50);//WAS (2.5, 25)
    check_heading(360);

}

//NEED TO WORK ON THIS
//FULL POINTS MAY MAKE OR BREAK THE HEAD TO HEAD
//NOT SURE WHAT'S HAPPENING WHERE
//REMOVED LIKE 1.5SEC SLEEP
void hit_pump_switch(){
    
   move_backwards(36, 30);
   check_y_minus(21.5);
   check_heading(180);
//REMOVED SLEEP 1SEC

   turn_right(30, 90);
   check_heading(90);

  // if (RPS.OilDirec() == 1){
   liftServo.SetDegree(165);
   move_backwards(18, 30);
   check_heading(90);
   check_x_plus(10);
   turn_left(20, 90);
   liftServo.SetDegree(110);
   Sleep(500);
   move_backwards(4, 20);
  // }


}

//SPEEDING THIS GUY UP
//OMG WHYYYY DID YOU NOT USE CONSTANTS?? :'(
void turn_crank1() {
    check_heading(180);
    crankServo.SetMax(2337);
    crankServo.SetMin(517);
    move_forward_time(500, 10);

    bool blue = false;

    if (cdscell.Value() > .15){
        blue = true;
    }

    if (!blue) { // if red
        move_backwards(1, 10);
        check_heading(180);
        crankServo.SetDegree(0); //Set servo at minimum angle
        Sleep(750); //WAS 1250

        //FIRST TURN
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(750); //WAS 1000
        crankServo.SetDegree(180); //ACTUALLY TURNING CRANK
        Sleep(750); //WAS 1250
        right_motor.Stop();
        left_motor.Stop();

        //FIRST BACK UP
        move_backwards(.25, 20); //(.5, 10)
        check_heading(180);

        //RESET SERVO
        crankServo.SetDegree(0);
        Sleep(750); //WAS 1250

        //SECOND TURN >>SAME VALUES CHANGED<<
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(750);
        crankServo.SetDegree(180); //ACTUALLY TURNING CRANK
        Sleep(750);
        right_motor.Stop();
        left_motor.Stop();

        //SECOND BACK UP >>SAME VALUES CHANGED<<
        move_backwards(.25, 20);
        check_heading(180);

        //RESET SERVO >>SAME VALUES CHANGED<<
        crankServo.SetDegree(0);
        Sleep(750);

        //THIRD TURN >>SAME VALUES CHANGED<<
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(750);
        crankServo.SetDegree(90); //ACTUALLY TURNING CRANK
        Sleep(500);
        right_motor.Stop();
        left_motor.Stop();
    }
    else {//counterclockwise = blue
        move_backwards(1, 10);
        check_heading(180);
        crankServo.SetDegree(180); //Set servo at minimum angle
        Sleep(750); //WAS 1250

        //FIRST TURN
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(750); //WAS 1000
        crankServo.SetDegree(0); //ACTUALLY TURNING CRANK
        Sleep(750); //WAS 1250
        right_motor.Stop();
        left_motor.Stop();

        //FIRST BACK UP
        move_backwards(.25, 20); //(.5, 10)
        check_heading(180);

        //RESET SERVO
        crankServo.SetDegree(180);
        Sleep(750); //WAS 1250

        //SECOND TURN >>SAME VALUES CHANGED<<
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(750);
        crankServo.SetDegree(0); //ACTUALLY TURNING CRANK
        Sleep(750);
        right_motor.Stop();
        left_motor.Stop();

        //SECOND BACK UP >>SAME VALUES CHANGED<<
        move_backwards(.25, 20);
        check_heading(180);

        //RESET SERVO >>SAME VALUES CHANGED<<
        crankServo.SetDegree(180);
        Sleep(750);

        //THIRD TURN >>SAME VALUES CHANGED<<
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(750);
        crankServo.SetDegree(90); //ACTUALLY TURNING CRANK
        Sleep(500);
        right_motor.Stop();
        left_motor.Stop();
    }
}

void calibrate_scoop_servo()
{
   // liftServo.Calibrate();

    liftServo.SetMin(500);
    liftServo.SetMax(2500);
    liftServo.SetDegree(140);
    int currentDegree = 140;
    while (1)
    {
        if (buttons.LeftPressed())
    {
            LCD.Clear();

            liftServo.SetDegree(currentDegree - 1 );
             currentDegree -= 1;
             LCD.WriteLine(currentDegree);



     }
        else if (buttons.RightPressed()){
            LCD.Clear();
            liftServo.SetDegree(currentDegree + 1 );
             currentDegree += 1;
             LCD.WriteLine(currentDegree);

        }


}

}

void scoop_salt()
{
    liftServo.SetMin(500);
    liftServo.SetMax(2500);

    liftServo.SetDegree(120);
    Sleep(1000);
    liftServo.SetDegree(150);// to pick up salt, 150
    move_backwards(3, 28);
    Sleep(500);

    move_backwards(3, 28);
    Sleep(500);
    //back up to raise servo
    move_forward(2, 28);
    liftServo.SetDegree(118);
    turn_left(20, 110);

    //head almost to ramp
    move_backwards(12, 25);
    //check_y_minus(22);
    check_x_minus(28.5);//was 28.5
    turn_left(10, 20);

    // check_heading(360);



    /*
    move_forward(3, 10);
    liftServo.SetDegree(145);
    move_forward(4, 25);
    */


}

void move_to_buttons() {


    move_backwards(2, 25);

    check_y_plus(50);
    turn_left(15, 45);
    check_heading(45);
    move_backwards(5, 25);
    check_heading(45);
    move_backwards(6, 25);
    check_heading(45);

}

void move_to_salt() {

    liftServo.SetDegree(85); //was 65
    move_backwards(12, 23);
    check_heading(180);
    turn_left(20, 40);
    check_heading(220);
    move_backwards(8, 25);
    check_heading(220);

}

void deposit_salt()
{
    check_y_plus(60);
    turn_left(10, 45);
    check_heading(90);


    //liftServo.SetDegree(100);
    liftServo.SetDegree(123);// drops salt
    liftServo.SetDegree(154);
    move_forward(1.5, 10);
  //  Sleep(1000);
    check_heading(90);
    liftServo.SetDegree(140);
    move_backwards(8, 30);// 15
    check_x_plus(11);
    check_heading(90);
    liftServo.SetDegree(123);
    Sleep(300);
    move_forward(2, 10);
    turn_left(25, 30);
    check_heading(120);
    move_backwards(3, 15);
    liftServo.SetDegree(142);
    Sleep(300);
    turn_right(20, 60);
    turn_left(20, 20);
    check_heading(90);
    move_forward(1, 25);
    check_heading(90);


    /*
    int bang = 0;
    int currentDegree = 155;
    while (bang < 10)
{
        liftServo.SetDegree(currentDegree);
        turn_right(25, 5);
        liftServo.SetDegree(currentDegree + 5);
        turn_left(15, 3);

        bang++;
    }
    /*
    //check_x_plus(12.5);
    //move_forward(2.5, 25);
    turn_left(20, 60);
    check_heading(90);
    move_backwards(11.5, 25);

    int bang = 0;
    int currentDegree = 155;
    while (bang < 10)
{
        liftServo.SetDegree(currentDegree);
        turn_right(25, 5);
        liftServo.SetDegree(currentDegree + 5);
        turn_left(15, 3);

        bang++;
    }

    liftServo.SetDegree(180);
    Sleep(500);
    move_forward(3.5, 10);
    turn_left(35, 15);
    check_heading(100);
    liftServo.SetDegree(170);
    Sleep(500);
    move_backwards(5, 25);
    turn_right(20, 80);
    move_forward(4, 25);


    /*turn_right(10, 45);
    check_heading(45);
    move_backwards(6, 25);
    liftServo.SetDegree(140);
    move_forward(6, 25);
    */
}

void mooove_to_crank()
{
    move_forward(2, 15); // moving away from garage
    liftServo.SetDegree(100);// lift servo above snow
    //Sleep(500);took this out to save time
    check_heading(90);
    turn_left(25, 180); // 180 degree turn //turned faster to save time
    check_heading(270);
    liftServo.SetDegree(150);
    move_backwards(1, 25);
    check_heading(270);
    turn_right(20, 60); // pushing snow out of the way
    turn_left(15, 55);//changed to 55 from 60
    check_heading(270);
    move_backwards(5, 15);
    //check_x_minus();
    turn_right(15, 30);
    liftServo.SetDegree(45);
    check_heading(240);
    move_backwards(6, 20); // move towards east wall

    check_x_minus(30);
    turn_right(20, 75); // turn to align with east wall towards crank
    check_heading(165);
    move_forward(2.5, 20);
    turn_left(20, 15);
    check_heading(180);

    while(RPS.Y() < 58.5) // move into crank turning position
    {
        move_forward_time(150, 10);
        check_heading(180);
    }

}

int main(void)
{
    RPS.InitializeMenu();
    start_light_2(); //turbo
    move_to_salt(); 
    scoop_salt();
    climb_ramp(); //turbo
    move_to_buttons();
    push_buttons(); //turbo
    deposit_salt();
    mooove_to_crank();
    turn_crank1(); //turbo
    hit_pump_switch();
}
