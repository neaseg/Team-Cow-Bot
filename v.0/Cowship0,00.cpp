/*Created By: Garrett Nease*/
/*Date Created: 2/16/15*/
/*Revision: 0.00*/
/*Date Revised: 2/16/15*/
/*Program Function: Controls the robot on the entire course, the main file.*/

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHBUZZER.h>
#include <FEHMotor.h>
#include <FEHServo.h>

int main(void)
{
ButtonBoard buttons( FEHIO::Bank3 );
LCD.Clear( FEHLCD::Black );
LCD.SetFontColor( FEHLCD::White );
return 0;
}
