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

void start_light(){

    //defines percent difference for start light
    #define TARGET_DIFF 30
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
    
    //Keep motors running for the desired time
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
    // get the number of counts to turn desired degrees
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


void push_buttons()
{
    int redButtonOrder = RPS.RedButtonOrder();
    int whiteButtonOrder = RPS.WhiteButtonOrder();
    int blueButtonOrder = RPS.BlueButtonOrder();

   
    int angles[3];

    angles[redButtonOrder - 1] =  94;// The measured servo angles to hit the buttons
    angles[blueButtonOrder - 1] = 120;//
    angles[whiteButtonOrder - 1] = 107;//
    int currentAngle = 118;

   
    liftServo.SetMin(500);
    liftServo.SetMax(2500);


    for(int i = 0; i < 3; i++){
        
        //While loop to slowly change the angle of the servo to the next button position
        while (currentAngle != angles[i]) {
               if (angles[i] < currentAngle)
            {
               liftServo.SetDegree(currentAngle - 1);
               Sleep(50);
               currentAngle -= 1;
            }
               else
        {
               liftServo.SetDegree(currentAngle + 1);
               Sleep(50);
               currentAngle += 1;

    }
    }

        Sleep(1000);
        ResetTime();

        //move into the wall for some time
         move_backwards_time(1050, 20); 

        //move away from the wall so there is space to move the lift
         move_forward(3.5,15);
         check_heading(45);

    }



void move_to_Ramp()
{
    move_forward(11, 25);
    Sleep(1000);

    turn_left(25, 90); // actual counts needs to be measure
    Sleep(1000);
    move_forward(11, 25);
    Sleep(1000);
    turn_left(25, 90);
    Sleep(1000);
    move_forward(8, 25);
    Sleep(1000);
}

void climb_ramp()
{
    check_heading(360);
    LCD.Clear();
    LCD.WriteLine("ATTEMPTING TO CLIMB RAMP");
    Sleep(100);
    LCD.WriteLine("I THINK I CAN, I THINK I CAN...");
    move_backwards(20.5,50);
    check_heading(360);
    move_backwards(5, 24);//was 2.5
    check_heading(360);
    LCD.Clear();

    //check_y_plus(50);
    // check_heading(360);



}

void hit_pump_switch(){
   move_backwards(36, 30);
   check_y_minus(21.5);
   check_heading(180);
   Sleep(1000);


   turn_right(30, 90);
   check_heading(90);


   if (RPS.OilDirec() == 1){
   liftServo.SetDegree(165);
   move_backwards(18, 30);
   check_heading(90);
   check_x_plus(10);
   turn_left(20, 90);
   liftServo.SetDegree(110);
   Sleep(500);
   move_backwards(7, 20);
   }

   else{
       liftServo.SetDegree(50);
       move_backwards(15, 30);
       check_heading(90);
       check_x_plus(13);
       turn_left(20, 70);
       check_heading(165);
       move_backwards(6.25,15);
        check_y_minus(15);
       liftServo.SetDegree(65);
       Sleep(500);

       left_motor.SetPercent(-50);
       //move_forward(2, 30);
   }


}

float check_light()  {
    double crankLightSum = 0;
    for( int i = 0; i < 10; i++){
        crankLightSum += cdscell.Value();
        Sleep(100);
    }

     double averageLight = crankLightSum / 10;

    return averageLight;
}



void turn_crank1() {
    check_heading(180);
    crankServo.SetMax(2337);
    crankServo.SetMin(517);
    move_forward_time(500, 10);
   // Sleep(1000);
    float lightValue = check_light();
    LCD.Clear();
    LCD.WriteLine("LIGHT VALUE =   ");
    LCD.Write(lightValue);
   // Sleep(5000);

    bool blue = true;

    if (lightValue > .15)
        blue = true;
    else
        blue = false;

    if (!blue) { // if red
        move_backwards(1, 10);
        check_heading(180);
        crankServo.SetDegree(0); //Set servo at minimum angle
        Sleep(1250);

        //first turn
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(1000);
        right_motor.SetPercent(30); //WORKING VALUE = 30, -30
        left_motor.SetPercent(-30);
        crankServo.SetDegree(180); // turn servo motor to maximum angle while slowly moving into wall for 1 second
        Sleep(1250);


        move_backwards(.75, 10);
        //check_heading(180);

        //resetting servo
        crankServo.SetDegree(0);
        Sleep(1250); //wait for servo to turn back to angle 0

        //second turn
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(1000);
        right_motor.SetPercent(30);
        left_motor.SetPercent(-30);
        crankServo.SetDegree(180); // turn servo motor while slowly moving into wall for 1 second
        Sleep(1250);
        right_motor.Stop();
        left_motor.Stop();

        move_backwards(.75, 10);// was .5
        check_heading(180);

        //resetting servo
        crankServo.SetDegree(0);
        Sleep(1250); //wait for servo to turn back to angle 0

        //third turn
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(1000);
        right_motor.SetPercent(30);
        left_motor.SetPercent(-30);
        crankServo.SetDegree(65); // turn servo motor while slowly moving into wall for 1 second
        Sleep(1250);
        right_motor.Stop();
        left_motor.Stop();
    }
    else {//counterclockwise = blue
        move_backwards(1, 10);
        check_heading(180);
        crankServo.SetDegree(180); //Set servo at minimum angle
        Sleep((1250));

        //first turn
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(1000);
        right_motor.SetPercent(30);
        left_motor.SetPercent(-30);
        crankServo.SetDegree(0); // turn servo motor to maximum angle while slowly moving into wall for 1 second
        Sleep(1250);


        move_backwards(.75, 10);
        check_heading(180);

        //resetting servo
        crankServo.SetDegree(180);
        Sleep(1250); //wait for servo to turn back to angle 0

        //second turn
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(1000);
        right_motor.SetPercent(30);
        left_motor.SetPercent(-30);
        crankServo.SetDegree(0); // turn servo motor while slowly moving into wall for 1 second
        Sleep(1250);
        right_motor.Stop();
        left_motor.Stop();


        move_backwards(.75, 10);
        check_heading(180);


        //resetting servo
        crankServo.SetDegree(180);
        Sleep(1250); //wait for servo to turn back to angle 0

        //third turn
        right_motor.SetPercent(20);
        left_motor.SetPercent(-20);
        Sleep(1000);
        right_motor.SetPercent(30);
        left_motor.SetPercent(-30);
        crankServo.SetDegree(115); // turn servo motor while slowly moving into wall for 1 second
        Sleep(1250);
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
        // If left pressed, decrease servo angle, otherwise if right pressed, increase 
        if (buttons.LeftPressed()) {
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
    liftServo.SetDegree(150);//put the lift down to pick up salt
    move_backwards(3, 28); //move onto salt platform
    Sleep(500);

    move_backwards(3, 28);
    Sleep(500);
    //back up to raise servo
    move_forward(2, 28);
    //raise lift to secure salt
    liftServo.SetDegree(118);
    turn_left(20, 110);

    //head almost to ramp
    move_backwards(12, 25);
    //position to face up the ramp
    turn_left(10, 20);

}

void move_to_buttons() {


    move_backwards(1.75, 25);

    check_y_plus(48.5);//was 50
    turn_left(15, 45);
    check_heading(45);
    move_backwards(5, 25);
   // check_heading(45);
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


    liftServo.SetDegree(123);// drops salt
    liftServo.SetDegree(154);
    move_forward(1.5, 10);
    check_heading(90);
    liftServo.SetDegree(140); 
    move_backwards(8, 30);// pushes salt into garage area
    check_x_plus(11);
    check_heading(90);
    liftServo.SetDegree(123);
    move_forward(2, 10);
    turn_left(25, 30);
    check_heading(120);
    move_backwards(3, 15);
    liftServo.SetDegree(142);
    Sleep(300);
    turn_right(20, 60); // turns to fully move salt into garage
    turn_left(20, 20);
    check_heading(90);
    move_forward(1, 25);
    check_heading(90);


}

void move_to_crank()
{
    move_forward(2, 15); // moving away from garage
    liftServo.SetDegree(100);// lift servo above snow
    //Sleep(500);took this out to save time
    check_heading(90);
    turn_left(13, 180); // 180 degree turn //turned faster to save time
    check_heading(270);
    liftServo.SetDegree(150);
    move_backwards(1, 25);
    check_heading(270);
    turn_right(15, 60); // pushing snow out of the way
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

    //PERFORMANCE TEST 2
    
    /*
    start_light_2();
    move_to_Ramp();
    climb_ramp();
    move_forward(15,12.5);
    calibrate_scoop_servo();
    Sleep(10000);
    scoop_salt();
    push_buttons();
    */

    /*
   //PERFORMANCE TEST 3
    RPS.InitializeMenu();
    climb_ramp();
    turn_left(25, 105);
    move_backwards(11, 25);
   push_buttons();
    */

 

    // PERFORMANCE TEST 4
    /*
    liftServo.SetMin(500);
    liftServo.SetMax(2182);
    RPS.InitializeMenu();
    Sleep(1000);
    start_light_2();
    liftServo.SetDegree(45);
    move_backwards(12, 25);
    check_heading(180);
    turn_left(20, 40);
    check_heading(220);
    move_backwards(9, 25);
    check_heading(220);
    scoop_salt();
    climb_ramp();
    deposit_salt();
    */

    //PERFORMANCE TEST 5

/*
    move_forward(20, 25);
    Sleep(1000);
    move_backwards(20, 25);
    Sleep(1000);
    move_forward(20, 25);
   // RPS.InitializeMenu();
   // turn_crank();
    liftServo.SetMin(500);
    liftServo.SetMax(2182);
    RPS.InitializeMenu();
    start_light_2();
    liftServo.SetDegree(45);
    move_backwards(12, 23);
    check_heading(180);
    turn_left(20, 40);
    check_heading(220);
    move_backwards(8, 25);
    check_heading(220);
    scoop_salt();
    climb_ramp();
    turn_crank();
    hit_pump_switch();    
 */

    //INDIVIDUAL COMPETITION (FINAL RUN)

    RPS.InitializeMenu();

    start_light_2();
    move_to_salt();
    scoop_salt();
    climb_ramp();
    move_to_buttons();
    push_buttons();
    deposit_salt();
    move_to_crank();
    turn_crank1();
    hit_pump_switch();



}
