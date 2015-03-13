#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHRPS.h> //Must include this library
/*Retrieved from carmen.osu.edu on 2/18/15*/


int main(void)
{
    ButtonBoard buttons( FEHIO::Bank3 );

    //Set the LCD screen color
    LCD.Clear( FEHLCD::Scarlet );
    LCD.SetBackgroundColor(FEHLCD::Scarlet);
    LCD.SetFontColor( FEHLCD::Gray );

    //Call this function to initialize the RPS to a course
    RPS.InitializeMenu();

    //Press middle button to begin
    LCD.WriteLine("Press the middle button to begin");
    //Wait for middle button to be pressed
    while(!buttons.MiddlePressed());
    //Wait for middle button to be unpressed
    while(buttons.MiddlePressed());
    LCD.Clear();

    //Write initial screen info
    LCD.WriteRC("X Position:",0,0);
    LCD.WriteRC("Y Position:",1,0);
    LCD.WriteRC("   Heading:",2,0);

    while( true )
    {
        LCD.WriteRC(RPS.X(),0,12); //update the x coordinate
        LCD.WriteRC(RPS.Y(),1,12); //update the y coordinate
        LCD.WriteRC(RPS.Heading(),2,12); //update the heading
        Sleep(10); //wait for a 10ms to avoid updating the screen too quickly
    }

    //we will never get here because of the infinite while loop
    return 0;
}
