//MAXWELL POWELL
//2.23.15
//Rev 1: Garrett Nease
//2.27.15

//THREE OPTOSENSOR CODE
//DEFINE STATES
#define LEFT_ON_LINE  0
#define LEFT_TWO_ON_LINE  1
#define MIDDLE_ON_LINE  2
#define RIGHT_ON_LINE  3
#define RIGHT_TWO_ON_LINE  4
#define THRESHOLD  2
#define FULL_POWER 50
#define HALF_POWER 25

//DECLARES OPTOSENSORS
AnalogInputPin leftOpto(FEHIO::P1_0);
AnalogInputPin middleOpto(FEHIO::P1_1);
AnalogInputPin rightOpto(FEHIO::P1_2);

//DECLARES MOTORS
FEHMotor rightMotor (FEHMotor::Motor0);
FEHMotor leftMotor (FEHMotor::Motor1);


int main(){
//SETS INITIAL STATE & DECLARES VARIABLES FOR SENSOR VALUES
  int state = MIDDLE_ON_LINE;
  float leftValue, middleValue, rightValue;
  
  //INFINITE LINE FOLLOWING LOOP
  while(true){
    
    //SLEEP
    Sleep(100);
  
    //GETS OPTOSENSOR VALUES
    leftValue = leftOpto.Value();
    middleValue = middleOpto.Value();
    rightValue = rightOpto.Value();
    
    //SETS ROBOT STATE
    if(leftValue > THRESHOLD && middleValue < THRESHOLD && rightValue < THRESHOLD)){
      state = LEFT_ON_LINE;
      } else if(leftValue > THRESHOLD && middleValue > THRESHOLD && rightValue < THRESHOLD){
      state = LEFT_TWO_ON_LINE;
      } else if(leftValue < THRESHOLD && middleValue > THRESHOLD && rightValue < THRESHOLD){
      state = MIDDLE_ON_LINE;
      } else if(leftValue < THRESHOLD && middleValue < THRESHOLD && rightValue > THRESHOLD){
      state = RIGHT_ON_LINE;
      } else if(leftValue < THRESHOLD && middleValue > THRESHOLD && rightValue > THRESHOLD){
      state = RIGHT_TWO_ON_LINE;
      }
      
      //WRITES STATE TO SCREEN
      LCD.Clear();
      LCD.Write(state\n);
      LCD.Write(leftValue\n);
      
      //ACTS BASED ON STATE
      switch(state){
        
        //TURNS LEFT IF ONLY LEFT IS ON LINE
        case LEFT_ON_LINE;
          rightMotor.SetPercent(FULL_POWER);
          leftMotor.SetPercent(HALF_POWER);
          break;
          
        //TURNS LEFT IF ONLY LEFT TWO ARE ON ON LINE
        case LEFT_TWO_ON_LINE;
          rightMotor.SetPercent(FULL_POWER);
          leftMotor.SetPercent(HALF_POWER);
          break;
          
        //NO TURN IF ONLY MIDDLE IS ON LINE
        case MIDDLE_ON_LINE;
          rightMotor.SetPercent(FULL_POWER);
          leftMotor.SetPercent(FULL_POWER);
          break;
          
        //TURNS RIGHT IF ONLY RIGHT IS ON LINE
        case LEFT_ON_LINE;
          rightMotor.SetPercent(HALF_POWER);
          leftMotor.SetPercent(FULL_POWER);
          break;
          
        //TURNS RIGHT IF RIGHT TWO ARE ON LINE
        case LEFT_ON_LINE;
          rightMotor.SetPercent(FULL_POWER);
          leftMotor.SetPercent(HALF_POWER);
          break;
          
        default:
          break;
      }
  }
}
  
  

