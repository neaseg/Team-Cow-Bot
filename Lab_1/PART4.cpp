/*Written By: Garrett Nease*/
/*Date Created: 2/13/15*/
/*Revision: 0*/
/*Date Revised: 2/13/15*/
/*Program Function: Read in values of cds cell to create color values.*/

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHBUZZER.h>
#include <FEHMotor.h>
#include <FEHServo.h>


int main(void)
{
    /*Initialize all inputs and outpus, as well as motors.*/
    ButtonBoard buttons( FEHIO::Bank3 );
    AnalogInputPin cdscell(FEHIO::P1_0);
    FEHMotor motor0 (FEHMotor::Motor0);
    DigitalInputPin microSwitch (FEHIO::P0_0);
    /*initialize sensor values*/
    float cdsvalue;
    
    /*Run motor0 at full speed*/

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    while(1)
    {
        /*Read in cdscell value to cdsvalue then print it.*/
        cdsvalue = cdscell.Value();
        LCD.Write( cdsvalue );
        Sleep(250);
    }
            
    return 0;
}
