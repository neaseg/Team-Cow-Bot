/*Written By: Maxwell Powell*/
/*Date Created: 2/13/15*/
/*Revision: 0*/
/*Date Revised: 2/13/15*/
/*Program Function: Runs motor based on switch input.*/

#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <FEHIO.h>

FEHMotor motor0 (FEHMotor::Motor0);
DigitalInputPin microSwitch (FEHIO::P0_0);

int main(void)
{
    while(1){
        if(microSwitch.Value()){
            motor0.SetPercent(100);
        } else {
            motor0.SetPercent(0);
        }
    }
}
