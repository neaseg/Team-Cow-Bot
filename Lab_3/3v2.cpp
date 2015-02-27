//Rev 1: Garrett Nease
//2.27.15
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

//THREE OPTOSENSOR CODE
//DEFINE STATES
#define LEFT_ON_LINE  0
#define LEFT_TWO_ON_LINE  1
#define ON_LINE  2
#define RIGHT_ON_LINE  3
#define RIGHT_TWO_ON_LINE  4
#define THRESHOLD  2
#define FULL_POWER 50
#define HALF_POWER 25
#define ON 2.35
#define OFF 2.8

//DECLARES OPTOSENSORS
AnalogInputPin leftOpto(FEHIO::P1_0);
AnalogInputPin middleOpto(FEHIO::P1_1);
AnalogInputPin rightOpto(FEHIO::P1_2);

//DECLARES MOTORS
FEHMotor rightMotor (FEHMotor::Motor0);
FEHMotor leftMotor (FEHMotor::Motor1);


int main(){
  float l, c, r;
  int prev;

  //INFINITE LINE FOLLOWING LOOP
  while(true){

    //GETS OPTOSENSOR VALUES
    l = leftOpto.Value();
    c = middleOpto.Value();
    r = rightOpto.Value();
    //write values to screen
    LCD.Write("Right");
    LCD.WriteLine(r);
    LCD.Write("Center");
    LCD.WriteLine(c);
    LCD.Write("Left");
    LCD.WriteLine(l);
    //if statements to check for on left
    if ( l < ON && c < ON && r > ON ){
      rightMotor.SetPercent(10);
      leftMotor.SetPercent(75);
      Sleep( 150 );
      prev = LEFT_ON_LINE;
    }//end left check
    
    //check if robot is on middle
    else if ( l < ON && c > ON && r < ON ){
      rightMotor.SetPercent(75);
      leftMotor.SetPercent(75);
      Sleep( 150 );
      prev = ON_LINE;
    }//END MIDDLE CHECK
    
    //CHECK IF TO THE RIGHT
    else if ( l > ON && c < ON && r < ON){
      rightMotor.SetPercent(75);
      leftMotor.SetPercent(10);
      Sleep( 150 );
      prev = ON_LINE;
    }//END RIGHT CHECK
    
    //else error statement
    else {
      LCD.Write("Error.\n")
    }
    
   
}



