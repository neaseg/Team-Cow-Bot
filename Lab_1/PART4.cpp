/*Written By: Maxwell Powell*/
/*Date Created: 2/13/15*/
/*Revision: 0*/
/*Date Revised: 2/13/15*/
/*Program Function: Read in values of cds cell to operate motor.*/

int main(void){
    ButtonBoard buttons(FEHIO::Bank3);
    AnalogInputPin CDSCell(FEHIO::P1_0);
    FEHMotor motor0 (FEHMotor::Motor0);

    while(!buttons.MiddlePressed()){
        Sleep(10);
    }
    Sleep(1000);
    motor0.SetPercent(100);
    while(!buttons.MiddlePressed()){
        motor0.SetPercent((1.65 - CDSCell.Value()) * 100 /1.65);
    }
    motor0.SetPercent(0);
}
