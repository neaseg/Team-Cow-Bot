/********************************/
/*   Student Proteus Testing    */
/*     OSU FEH Spring 2014      */
/* Drew Phillips and Brian Rice */
/*    01/23/14  Version 2.1     */
/********************************/

/* This program uses a menu-based system to allow the user to test any motor port or flex I/O port on the Proteus. */

/* Include preprocessor directives */
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>

/* Declare DC Motor ports */
FEHMotor motor0 (FEHMotor::Motor0);
FEHMotor motor1 (FEHMotor::Motor1);
FEHMotor motor2 (FEHMotor::Motor2);
FEHMotor motor3 (FEHMotor::Motor3);

/* Declare Servo Motor ports */
FEHServo servo0 (FEHServo::Servo0);
FEHServo servo1 (FEHServo::Servo1);
FEHServo servo2 (FEHServo::Servo2);
FEHServo servo3 (FEHServo::Servo3);
FEHServo servo4 (FEHServo::Servo4);
FEHServo servo5 (FEHServo::Servo5);
FEHServo servo6 (FEHServo::Servo6);
FEHServo servo7 (FEHServo::Servo7);

/* Initialize degree for Servo Motors */
int degree = 0;

/* Declare ports for digital input */
DigitalInputPin dg00 (FEHIO::P0_0);
DigitalInputPin dg01 (FEHIO::P0_1);
DigitalInputPin dg02 (FEHIO::P0_2);
DigitalInputPin dg03 (FEHIO::P0_3);
DigitalInputPin dg04 (FEHIO::P0_4);
DigitalInputPin dg05 (FEHIO::P0_5);
DigitalInputPin dg06 (FEHIO::P0_6);
DigitalInputPin dg07 (FEHIO::P0_7);
DigitalInputPin dg10 (FEHIO::P1_0);
DigitalInputPin dg11 (FEHIO::P1_1);
DigitalInputPin dg12 (FEHIO::P1_2);
DigitalInputPin dg13 (FEHIO::P1_3);
DigitalInputPin dg14 (FEHIO::P1_4);
DigitalInputPin dg15 (FEHIO::P1_5);
DigitalInputPin dg16 (FEHIO::P1_6);
DigitalInputPin dg17 (FEHIO::P1_7);
DigitalInputPin dg20 (FEHIO::P2_0);
DigitalInputPin dg21 (FEHIO::P2_1);
DigitalInputPin dg22 (FEHIO::P2_2);
DigitalInputPin dg23 (FEHIO::P2_3);
DigitalInputPin dg24 (FEHIO::P2_4);
DigitalInputPin dg25 (FEHIO::P2_5);
DigitalInputPin dg26 (FEHIO::P2_6);
DigitalInputPin dg27 (FEHIO::P2_7);

/* Declare ports for analog input */
AnalogInputPin an00 (FEHIO::P0_0);
AnalogInputPin an01 (FEHIO::P0_1);
AnalogInputPin an02 (FEHIO::P0_2);
AnalogInputPin an03 (FEHIO::P0_3);
AnalogInputPin an04 (FEHIO::P0_4);
AnalogInputPin an05 (FEHIO::P0_5);
AnalogInputPin an06 (FEHIO::P0_6);
AnalogInputPin an07 (FEHIO::P0_7);
AnalogInputPin an10 (FEHIO::P1_0);
AnalogInputPin an11 (FEHIO::P1_1);
AnalogInputPin an12 (FEHIO::P1_2);
AnalogInputPin an13 (FEHIO::P1_3);
AnalogInputPin an14 (FEHIO::P1_4);
AnalogInputPin an15 (FEHIO::P1_5);
AnalogInputPin an16 (FEHIO::P1_6);
AnalogInputPin an17 (FEHIO::P1_7);
AnalogInputPin an20 (FEHIO::P2_0);
AnalogInputPin an21 (FEHIO::P2_1);
AnalogInputPin an22 (FEHIO::P2_2);
AnalogInputPin an23 (FEHIO::P2_3);
AnalogInputPin an24 (FEHIO::P2_4);
AnalogInputPin an25 (FEHIO::P2_5);
AnalogInputPin an26 (FEHIO::P2_6);
AnalogInputPin an27 (FEHIO::P2_7);

/* Set Button Board to Bank 3 */
ButtonBoard buttons (FEHIO::Bank3);

/* Declare function to display main menu */
void MainMenu()
{
    /* Set up main menu */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Proteus Testing!");
    LCD.WriteLine("Use the right and left");
    LCD.WriteLine("buttons to navigate.");
    LCD.WriteLine("Press the middle button");
    LCD.WriteLine("to select a test.");
    LCD.WriteLine(" ");
}

/* Declare function for DC motor menu */
void DCMenu()
{
    /* Set up DC Motor menu */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Test DC Motors");
    LCD.WriteLine("Use the right and left");
    LCD.WriteLine("buttons to navigate.");
    LCD.WriteLine("Press the middle button");
    LCD.WriteLine("to select a motor.");
    LCD.WriteLine(" ");
}

/* Declare function for Servo motor menu */
void ServoMenu()
{
    /* Set up Servo Motor menu */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Test Servo Motors");
    LCD.WriteLine("Use the right and left");
    LCD.WriteLine("buttons to navigate.");
    LCD.WriteLine("Press the middle button");
    LCD.WriteLine("to select a motor.");
    LCD.WriteLine(" ");
}

/* Declare function for digital input menu */
void DigitalMenu()
{
    /* Set up digital input menu */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Test Digital Inputs");
    LCD.WriteLine("Use the right and left");
    LCD.WriteLine("buttons to navigate.");
    LCD.WriteLine("Press the middle button");
    LCD.WriteLine("to select a port.");
    LCD.WriteLine(" ");
}

/* Declare function for analog input menu */
void AnalogMenu()
{
    /* Set up ananlog input menu */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Test Analog Inputs");
    LCD.WriteLine("Use the right and left");
    LCD.WriteLine("buttons to navigate.");
    LCD.WriteLine("Press the middle button");
    LCD.WriteLine("to select a port.");
    LCD.WriteLine(" ");
}

/* Declare function to increment or decrement given counter variable */
int CounterChange(int c)
{
    /* Wait until a button is pressed */
    while (!buttons.RightPressed() && !buttons.LeftPressed() && !buttons.MiddlePressed()) {}

    /* Check to see which of the buttons is pressed and change c accordingly */
    if (buttons.RightPressed())
    {
        /* Increment c */
        c++;
    }
    else if (buttons.LeftPressed())
    {
        /* Decrement c */
        c--;
    }
    else if (buttons.MiddlePressed())
    {
        /* Leave c */
    }

    /* Wait */
    Sleep(.25);

    /* Return new counter value */
    return c;
}

/* Declare function to setup boundaries for menus */
int CounterBoundaries(int c, int a, int b)
{
    /* Use boundaries to cycle through choices */
    if (c == a-1)
    {
        c = b;
    }
    else if (c == b+1)
    {
        c = a;
    }

    /* Return new counter value */
    return c;
}

/* Declare function for waiting for the middle button to be pressed */
void Wait()
{
    /* Wait until the middle button is pressed and released */
    while (!buttons.MiddlePressed()) {}
    while (buttons.MiddlePressed()) {}
}

/* Declare function to search main menu options */
void SearchMain(int n)
{
    /* Enter if structure to determine which choice is shown */
    if (n==0)
    {
        LCD.Write("Test DC Motors");
    }
    else if (n==1)
    {
        LCD.Write("Test Servo Motors");
    }
    else if (n==2)
    {
        LCD.Write("Test Digital Input");
    }
    else if (n==3)
    {
        LCD.Write("Test Analog Input");
    }
    else if (n==4)
    {
        LCD.Write("Quit Testing");
    }
}

/* Declare function to set DC motor power */
void DCPower(int n, int p)
{
    /* Determine which motor to run */
    if (n==0)
    {
        motor0.SetPower(p);
    }
    else if (n==1)
    {
        motor1.SetPower(p);
    }
    else if (n==2)
    {
        motor2.SetPower(p);
    }
    else if (n==3)
    {
        motor3.SetPower(p);
    }
}

/* Declare function for searching DC motors */
void SearchDC(int n)
{
    /* Determine which DC motor to use */
    if (n==0)
    {
        LCD.Write("DC Motor 0");
    }
    else if (n==1)
    {
        LCD.Write("DC Motor 1");
    }
    else if (n==2)
    {
        LCD.Write("DC Motor 2");
    }
    else if (n==3)
    {
        LCD.Write("DC Motor 3");
    }
    else if (n==4)
    {
        LCD.Write("Exit");
    }
}

/* Declare function for DC testing */
void DCTest(int n)
{
    /* Instructions */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Insert DC Motor");
    LCD.Write("into port ");
    LCD.Write(n);
    LCD.WriteLine(".");
    LCD.WriteLine("Press the middle");
    LCD.WriteLine("button to run.");

    /* Wait for middle button */
    Wait();

    /* Set the motor to run forward */
    DCPower(n, 25);

    /* Instructions */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Running forward.");
    LCD.WriteLine("Press the middle");
    LCD.WriteLine("button to stop.");

    /* Wait for the middle button */
    Wait();

    /* Set the motor to stop */
    DCPower(n, 0);

    /* Instructions */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Press the middle");
    LCD.WriteLine("button to run backward.");

    /* Wait for the middle button */
    Wait();

    /* Set the motor to run backward */
    DCPower(n, -25);

    /* Instructions */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Running backward.");
    LCD.WriteLine("Press the middle");
    LCD.WriteLine("button to stop.");

    /* Wait for middle button */
    Wait();

    /* Set the motor to stop */
    DCPower(n, 0);
}

/* Declare function to search for which servo to use */
void SearchServo(int n)
{
    /* Enter if structure to determine motor */
    if (n==0)
    {
        LCD.Write("Servo Motor 0");
    }
    else if (n==1)
    {
        LCD.Write("Servo Motor 1");
    }
    else if (n==2)
    {
        LCD.Write("Servo Motor 2");
    }
    else if (n==3)
    {
        LCD.Write("Servo Motor 3");
    }
    else if (n==4)
    {
        LCD.Write("Servo Motor 4");
    }
    else if (n==5)
    {
        LCD.Write("Servo Motor 5");
    }
    else if (n==6)
    {
        LCD.Write("Servo Motor 6");
    }
    else if (n==7)
    {
        LCD.Write("Servo Motor 7");
    }
    else if (n==8)
    {
        LCD.Write("Exit");
    }
}

/* Declare function for using servo motor */
void Servo(int n, int degree)
{
    /* Determine which servo to rotate */
    if (n==0)
    {
        servo0.SetDegree(degree);
    }
    else if (n==1)
    {
        servo1.SetDegree(degree);
    }
    else if (n==2)
    {
        servo2.SetDegree(degree);
    }
    else if (n==3)
    {
        servo3.SetDegree(degree);
    }
    else if (n==4)
    {
        servo4.SetDegree(degree);
    }
    else if (n==5)
    {
        servo5.SetDegree(degree);
    }
    else if (n==6)
    {
        servo6.SetDegree(degree);
    }
    else if (n==7)
    {
        servo7.SetDegree(degree);
    }
}

/* Declare function for servo test */
void ServoTest(int n)
{
    /* Reset servo to degree 90 */
    Servo(n, 90);
    degree = 90;

    /* Instructions */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Insert Servo Motor");
    LCD.Write("into port ");
    LCD.Write(n);
    LCD.WriteLine(".");
    LCD.WriteLine("Press the middle");
    LCD.WriteLine("button to run.");

    /* Wait for middle button */
    Wait();

    /* Instructions */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Use the right and left");
    LCD.WriteLine("buttons to rotate.");
    LCD.WriteLine("Press the middle");
    LCD.WriteLine("button to stop.");

    /* Allow servo motor to be rotated until the middle button is pressed */
    while (!buttons.MiddlePressed())
    {
        /* Decrease Servo Motor angle if left button is pressed */
        if (buttons.LeftPressed())
        {
            degree--;
            if(degree<0) degree=0;
            Servo(n, degree);
        }

        /* Increase Servo Motor angle if right button is pressed */
        if (buttons.RightPressed())
        {
            degree++;
            if(degree>180) degree=180;
            Servo(n, degree);
        }
    }

    /* Wait until the Middle Button is released */
    while (buttons.MiddlePressed()) {}
}

/* Declare function for finding the correct port */
void SearchPorts(int n, int d)
{
    /* Determine the proper port and decision*/
    if (n==0)
    {
        if (d==1)
        {
            LCD.Write("P0_0");
        }
        else if (d==2)
        {
            LCD.Write(dg00.Value());
        }
        else if (d==3)
        {
            LCD.Write(an00.Value());
        }
    }
    else if (n==1)
    {
        if (d==1)
        {
            LCD.Write("P0_1");
        }
        else if (d==2)
        {
            LCD.Write(dg01.Value());
        }
        else if (d==3)
        {
            LCD.Write(an01.Value());
        }
    }
    else if (n==2)
    {
        if (d==1)
        {
            LCD.Write("P0_2");
        }
        else if (d==2)
        {
            LCD.Write(dg02.Value());
        }
        else if (d==3)
        {
            LCD.Write(an02.Value());
        }
    }
    else if (n==3)
    {
        if (d==1)
        {
            LCD.Write("P0_3");
        }
        else if (d==2)
        {
            LCD.Write(dg03.Value());
        }
        else if (d==3)
        {
            LCD.Write(an03.Value());
        }
    }
    else if (n==4)
    {
        if (d==1)
        {
            LCD.Write("P0_4");
        }
        else if (d==2)
        {
            LCD.Write(dg04.Value());
        }
        else if (d==3)
        {
            LCD.Write(an04.Value());
        }
    }
    else if (n==5)
    {
        if (d==1)
        {
            LCD.Write("P0_5");
        }
        else if (d==2)
        {
            LCD.Write(dg05.Value());
        }
        else if (d==3)
        {
            LCD.Write(an05.Value());
        }
    }
    else if (n==6)
    {
        if (d==1)
        {
            LCD.Write("P0_6");
        }
        else if (d==2)
        {
            LCD.Write(dg06.Value());
        }
        else if (d==3)
        {
            LCD.Write(an06.Value());
        }
    }
    else if (n==7)
    {
        if (d==1)
        {
            LCD.Write("P0_7");
        }
        else if (d==2)
        {
            LCD.Write(dg07.Value());
        }
        else if (d==3)
        {
            LCD.Write(an07.Value());
        }
    }
    if (n==8)
    {
        if (d==1)
        {
            LCD.Write("P1_0");
        }
        else if (d==2)
        {
            LCD.Write(dg10.Value());
        }
        else if (d==3)
        {
            LCD.Write(an10.Value());
        }
    }
    else if (n==9)
    {
        if (d==1)
        {
            LCD.Write("P1_1");
        }
        else if (d==2)
        {
            LCD.Write(dg11.Value());
        }
        else if (d==3)
        {
            LCD.Write(an11.Value());
        }
    }
    else if (n==10)
    {
        if (d==1)
        {
            LCD.Write("P1_2");
        }
        else if (d==2)
        {
            LCD.Write(dg12.Value());
        }
        else if (d==3)
        {
            LCD.Write(an12.Value());
        }
    }
    else if (n==11)
    {
        if (d==1)
        {
            LCD.Write("P1_3");
        }
        else if (d==2)
        {
            LCD.Write(dg13.Value());
        }
        else if (d==3)
        {
            LCD.Write(an13.Value());
        }
    }
    else if (n==12)
    {
        if (d==1)
        {
            LCD.Write("P1_4");
        }
        else if (d==2)
        {
            LCD.Write(dg14.Value());
        }
        else if (d==3)
        {
            LCD.Write(an14.Value());
        }
    }
    else if (n==13)
    {
        if (d==1)
        {
            LCD.Write("P1_5");
        }
        else if (d==2)
        {
            LCD.Write(dg15.Value());
        }
        else if (d==3)
        {
            LCD.Write(an15.Value());
        }
    }
    else if (n==14)
    {
        if (d==1)
        {
            LCD.Write("P1_6");
        }
        else if (d==2)
        {
            LCD.Write(dg16.Value());
        }
        else if (d==3)
        {
            LCD.Write(an16.Value());
        }
    }
    else if (n==15)
    {
        if (d==1)
        {
            LCD.Write("P1_7");
        }
        else if (d==2)
        {
            LCD.Write(dg17.Value());
        }
        else if (d==3)
        {
            LCD.Write(an17.Value());
        }
    }
    if (n==16)
    {
        if (d==1)
        {
            LCD.Write("P2_0");
        }
        else if (d==2)
        {
            LCD.Write(dg20.Value());
        }
        else if (d==3)
        {
            LCD.Write(an20.Value());
        }
    }
    else if (n==17)
    {
        if (d==1)
        {
            LCD.Write("P2_1");
        }
        else if (d==2)
        {
            LCD.Write(dg21.Value());
        }
        else if (d==3)
        {
            LCD.Write(an21.Value());
        }
    }
    else if (n==18)
    {
        if (d==1)
        {
            LCD.Write("P2_2");
        }
        else if (d==2)
        {
            LCD.Write(dg22.Value());
        }
        else if (d==3)
        {
            LCD.Write(an22.Value());
        }
    }
    else if (n==19)
    {
        if (d==1)
        {
            LCD.Write("P2_3");
        }
        else if (d==2)
        {
            LCD.Write(dg23.Value());
        }
        else if (d==3)
        {
            LCD.Write(an23.Value());
        }
    }
    else if (n==20)
    {
        if (d==1)
        {
            LCD.Write("P2_4");
        }
        else if (d==2)
        {
            LCD.Write(dg24.Value());
        }
        else if (d==3)
        {
            LCD.Write(an24.Value());
        }
    }
    else if (n==21)
    {
        if (d==1)
        {
            LCD.Write("P2_5");
        }
        else if (d==2)
        {
            LCD.Write(dg25.Value());
        }
        else if (d==3)
        {
            LCD.Write(an25.Value());
        }
    }
    else if (n==22)
    {
        if (d==1)
        {
            LCD.Write("P2_6");
        }
        else if (d==2)
        {
            LCD.Write(dg26.Value());
        }
        else if (d==3)
        {
            LCD.Write(an26.Value());
        }
    }
    else if (n==23)
    {
        if (d==1)
        {
            LCD.Write("P2_7");
        }
        else if (d==2)
        {
            LCD.Write(dg27.Value());
        }
        else if (d==3)
        {
            LCD.Write(an27.Value());
        }
    }
    else if (n==24)
    {
        LCD.Write("Exit");
    }
}

/* Declare function for digital input test */
void DigitalTest(int n)
{
    /* Run digital test with SearchPorts function to get values */

    /* Allow the microswitch to be pressed and released until the middle button is pressed */
    while(!buttons.MiddlePressed())
    {
    /* Instructions */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Press microswitch to");
    LCD.WriteLine("test input status.");
    LCD.WriteLine("Press the middle");
    LCD.WriteLine("button to stop.");
    LCD.WriteLine(" ");
    LCD.Write("Status: ");
    SearchPorts(n, 2);

    /* Wait half a second */
    Sleep(0.25);
    }

    /* Wait until the middle button is released */
    while (buttons.MiddlePressed()) {}
}

/* Declare function for analog input test */
void AnalogTest(int n)
{
    /* Run analog test with SearchPorts function to get values */

    /* Allow CdS to change value until the middle button iss pressed */
    while(!buttons.MiddlePressed())
    {

    /* Instructions */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Vary light intensity");
    LCD.WriteLine("to test input value.");
    LCD.WriteLine("Press the middle");
    LCD.WriteLine("button to stop.");
    LCD.WriteLine(" ");
    LCD.Write("Value: ");
    SearchPorts(n, 3);

    /* Wait half a second */
    Sleep(0.25);
    }

    /* Wait until the middle button is released */
    while (buttons.MiddlePressed()) {}
}

/* Begin main function to test Proteus */
int main(void)
{
    /* Initialize counter variables */
    int q=0, c1=0, m=0, temp, c2=0, n=0;

    /* Clear screen and set font color to white */
    LCD.Clear(FEHLCD::Black);
    LCD.SetFontColor(FEHLCD::White);

    /* Enter large while loop */
    while (q==0)
    {

    /* Enter while loop for main menu */
    while (m==0)
    {
    /* Show main menu and options */
    MainMenu();
    LCD.Write("< ");
    SearchMain(c1);
    LCD.WriteLine(" >");

    /* Allow change in c1 to select test */
    temp = c1;
    c1 = CounterChange(c1);

    /* Determine if a choice was made */
    if (c1 == temp)
    {
        /* Set counter to exit main menu loop */
        m=1;
    }

    /* Use boundaries */
    c1 = CounterBoundaries(c1, 0, 4);
    }

    /* Re-initialize c2 */
    c2 = 0;

    /* Enter if structure to determine test */
    if (c1 == 0)
    {
        /* Enter while loop for DC Motors */
        while (m==1)
        {
            /* Reset n */
            n=0;

            /* Enter loop for menu */
            while (n==0)
            {
            /* Show menu and choices */
            DCMenu();
            LCD.Write("< ");
            SearchDC(c2);
            LCD.Write(" >");

            /* Allow change in c2 to select motor */
            temp = c2;
            c2 = CounterChange(c2);

            /* Determine if a choice was made */
            if (c2 == temp)
            {
                /* Set counter to exit menu loop */
                n=1;
            }

            /* Use boundaries */
            c2 = CounterBoundaries(c2, 0, 4);
            }

            /* Enter if structure to determine which motor to run */
            if (c2==4)
            {
                 /* Exit DC Motors */
                 m = 0;
            }
            else
            {
                /* Run test */
                DCTest(c2);
            }
        }
    }
    else if (c1 == 1)
    {
        /* Enter while loop for Servo Motors */
        while (m==1)
        {
            /* Reset n */
            n=0;

            /* Enter loop for menu */
            while (n==0)
            {
            /* Show menu and options */
            ServoMenu();
            LCD.Write("< ");
            SearchServo(c2);
            LCD.WriteLine(" >");

            /* Allow change in c2 to select motor */
            temp = c2;
            c2 = CounterChange(c2);

            /* Determine if a choice was made */
            if (c2 == temp)
            {
                /* Set counter to exit menu loop */
                n=1;
            }

            /* Use boundaries */
            c2 = CounterBoundaries(c2, 0, 8);
            }

            /* Enter if structure to determine which motor to run */
            if (c2==8)
            {
                 /* Exit Servo Motors */
                 m = 0;
            }
            else
            {
                /* Run test */
                ServoTest(c2);
            }
        }
    }
    else if (c1 == 2)
    {
        /* Enter while loop for digital input */
        while (m==1)
        {
            /* Reset n */
            n=0;

            /* Enter loop for menu */
            while (n==0)
            {
            /* Show menu and options */
            DigitalMenu();
            LCD.Write("< ");
            SearchPorts(c2, 1);
            LCD.WriteLine(" >");

            /* Allow change in c2 to select port */
            temp = c2;
            c2 = CounterChange(c2);

            /* Determine if a choice was made */
            if (c2 == temp)
            {
                /* Set counter to exit menu loop */
                n=1;
            }

            /* Use boundaries */
            c2 = CounterBoundaries(c2, 0, 24);
            }

            /* Enter if structure to determine which port to use */
            if (c2==24)
            {
                 /* Exit digital inputs */
                 m = 0;
            }
            else
            {
                /* Run test */
                DigitalTest(c2);
            }
        }
    }
    else if (c1 == 3)
    {
        /* Enter while loop for analog input */
        while (m==1)
        {
            /* Reset n */
            n=0;

            /* Enter loop for menu */
            while (n==0)
            {
            /* Show menu and options */
            AnalogMenu();
            LCD.Write("< ");
            SearchPorts(c2, 1);
            LCD.WriteLine(" >");

            /* Allow change in c2 to select motor */
            temp = c2;
            c2 = CounterChange(c2);

            /* Determine if a choice was made */
            if (c2 == temp)
            {
                /* Set counter to exit menu loop */
                n=1;
            }

            /* Use boundaries */
            c2 = CounterBoundaries(c2, 0, 24);
            }

            /* Enter if structure to determine which port to use */
            if (c2==24)
            {
                 /* Exit analog inputs */
                 m = 0;
            }
            else
            {
                /* Run test */
                AnalogTest(c2);
            }
        }
    }
    else if (c1 == 4)
    {
        /* Quit testing program by leaving large while loop */
        q=1;
    }
    }

    /* End program */
    LCD.Clear(FEHLCD::Black);
    LCD.WriteLine("Goodbye!");
    return 0;
}
