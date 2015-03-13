#define LINE_ON_RIGHT 0
#define ON_LINE_FIRST 1
#define LINE_ON_LEFT 2
#define ON_LINE_SECOND 3


#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>


int main() {

    AnalogInputPin middle_opt(FEHIO::P1_0);
    ButtonBoard buttons(FEHIO::Bank3);
    DigitalEncoder right_encoder(FEHIO::P0_0);
    DigitalEncoder left_encoder(FEHIO::P0_1);
    FEHMotor right_motor(FEHMotor::Motor0);
    FEHMotor left_motor(FEHMotor::Motor1);



    int state = LINE_ON_LEFT; // Set the initial state
    while (true) { // I will follow this line forever!
        switch(state) {
            // If the line is on my right...
            case LINE_ON_RIGHT:
            // Set motor powers for right turn
            right_motor.SetPercent(25);
            left_motor.SetPercent(75);
            if ( middle_opt.Value() >= 2.35 ) {
                    state = ON_LINE_FIRST; // update a new state
                    }
                    break;

 // If I am on the line, but zigging to the right...
                case ON_LINE_FIRST:
                 // Set motor powers for right turn
            right_motor.SetPercent(40);
            left_motor.SetPercent(60);
                if(middle_opt.Value() <= 2.35/* I don't see the line */) {
                    state = LINE_ON_LEFT; // update a new state
                }
                break;
 // If the line is on my left...
            case LINE_ON_LEFT:
            // Mirror operation of LINE_ON_RIGHT state
            // Set motor powers for Left turn
            right_motor.SetPercent(75);
            left_motor.SetPercent(25);
            if ( middle_opt.Value() >= 2.35 ) {
                    state = ON_LINE_SECOND; // update a new state
                    }
                    break;


// If I am on the line, but zagging to the left...
            case ON_LINE_SECOND:
            // Mirror operation of ON_LINE_FIRST state
            // Set motor powers for left turn
            right_motor.SetPercent(60);
            left_motor.SetPercent(40);
           if( middle_opt.Value() <= 2.35/* I don't see the line */) {
               state = LINE_ON_RIGHT; // update a new state
           }
            break;
            default: // Error. Something is very wrong.
break;
}
        LCD.Clear();
        LCD.WriteLine(middle_opt.Value());
        LCD.WriteLine(state);
        Sleep(50);
}

/*
    while(1)
    {
        LCD.Clear();
        LCD.WriteLine(middle_opt.Value());
        Sleep(100);
    }
    return 0;
    */
}
