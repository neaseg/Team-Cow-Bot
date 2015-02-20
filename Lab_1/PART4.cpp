/*Written By: Maxwell Powell*/
/*Date Created: 2/13/15*/
/*Revision: 0*/
/*Date Revised: 2/13/15*/
/*Program Function: Read in values of cds cell to operate motor.*/

int main(void){
    
    //Declares button board, CdS cell, and motor
    ButtonBoard buttons(FEHIO::Bank3);
    AnalogInputPin CDSCell(FEHIO::P1_0);
    FEHMotor motor0 (FEHMotor::Motor0);

    //Sleeps until middle button is pressed
    while(!buttons.MiddlePressed()){
        Sleep(10);
    }
    
    //Sleeps to prevent button press from terminating program
    Sleep(1000);
    
    //Sets motor to 100 percent
    motor0.SetPercent(100);
    
    //Controls motor via cds input unitl middle button is pressed
    while(!buttons.MiddlePressed()){
        motor0.SetPercent((1.65 - CDSCell.Value()) * 100 /1.65);
    }
    
    //Sets motor off
    motor0.SetPercent(0);
}
