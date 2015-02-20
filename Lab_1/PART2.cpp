/*Written By: Maxwell Powell*/
/*Date Created: 2/13/15*/
/*Revision: 0*/
/*Date Revised: 2/13/15*/
/*Program Function: Tests Motor Functionality.*/

#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <FEHIO.h>

//Declares a motor
FEHMotor motor0 (FEHMotor::Motor0);


int main(void)
{
    //Clears screen, writes motor state, sets motor state forward, and sleeps 100 milliseconds
    LCD.Clear();
    LCD.WriteLine("RUNNING MOTOR FORWARDS AT FULL POWER");
    motor0.SetPercent(100);
    Sleep(100);
    
    //Clears screen, writes motor state, sets motor state off, and sleeps 100 milliseconds
    LCD.Clear();
    LCD.WriteLine("OFF");
    motor0.SetPercent(0);
    Sleep(100);
    
    //Clears screen, writes motor state, sets motor state reverse, and sleeps 100 milliseconds
    LCD.Clear();
    LCD.WriteLine("RUNNING MOTOR BACKWARDS AT FULL POWER");
    motor0.SetPercent(-100);
    Sleep(100);
    
    //Clears screen, writes motor state, sets motor state off, and sleeps 100 milliseconds
    LCD.Clear();
    LCD.WriteLine("OFF");
    motor0.SetPercent(0);
}
