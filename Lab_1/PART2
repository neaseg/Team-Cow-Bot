/*Written By: Maxwell Powell*/
/*Date Created: 2/13/15*/
/*Revision: 0*/
/*Date Revised: 2/13/15*/
/*Program Function: Tests Motor Functionality.*/

#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <FEHIO.h>

FEHMotor motor0 (FEHMotor::Motor0);


int main(void)
{
    LCD.Clear();
    LCD.WriteLine("RUNNING MOTOR FORWARDS AT FULL POWER");
    motor0.SetPercent(100);
    Sleep(100);
    LCD.Clear();
    LCD.WriteLine("OFF");
    motor0.SetPercent(0);
    Sleep(100);
    LCD.Clear();
    LCD.WriteLine("RUNNING MOTOR BACKWARDS AT FULL POWER");
    motor0.SetPercent(-100);
    Sleep(100);
    LCD.Clear();
    LCD.WriteLine("OFF");
    motor0.SetPercent(0);
}
