//MAXWELL POWELL
//2.23.15

//THREE OPTOSENSOR CODE
//DEFINE STATES
#define LEFT_ON_LINE  0;
#define LEFT_TWO_ON_LINE  1;
#define MIDDLE_ON_LINE  2;
#define RIGHT_ON_LINE  3;
#define RIGHT_TWO_ON_LINE  4;
#define THRESHOLD  2;

//DECLARES OPTOSENSORS
AnalogInputPin leftOpto(FEHIO::P1_0);
AnalogInputPin middleOpto(FEHIO::P1_0);
AnalogInputPin rightOpto(FEHIO::P1_0);

int main(){
//SETS INITIAL STATE & DECLARES VARIABLES FOR SENSOR VALUES
  int state = MIDDLE_ON_LINE;
  float leftValue, middleValue, rightValue;
  
  //INFINITE LINE FOLLOWING LOOP
  while(true){
  
    //GETS OPTOSENSOR VALUES
    leftValue = leftOpto.Value();
    middleValue = middleOpto.Value();
    rightValue = rightOpto.Value();
    
    //SETS ROBOT STATE
    if(leftValue < THRESHOLD && middleValue > THRESHOLD && rightValue > THRESHOLD){
      state = LEFT_ON_LINE;
      } else if(leftValue < THRESHOLD && middleValue > THRESHOLD && rightValue > THRESHOLD){
      state = LEFT_TWO_ON_LINE;
      } else if(leftValue < THRESHOLD && middleValue > THRESHOLD && rightValue > THRESHOLD){
      state = MIDDLE_ON_LINE;
      } else if(leftValue < THRESHOLD && middleValue > THRESHOLD && rightValue > THRESHOLD){
      state = RIGHT_ON_LINE;
      } else if(leftValue < THRESHOLD && middleValue > THRESHOLD && rightValue > THRESHOLD){
      state = RIGHT_TWO_ON_LINE;
      }
  
  

