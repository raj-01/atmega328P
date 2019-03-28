

/*
   Stride angle of motor is 5.625 degree per 64 steps.
   Also , there is a geare inside the steper motor of 32 teeths.
   S0 , it requires 64*32 = 2048 steps ( pulse ) from microcontroller, to rotate 360 dgrees.

   So, step resolution is 360/2048 = 0.17578125 ;
   We are sending 4 pulse of HIGH and LOW in same for loop , so , number of steps ( pulse ) required is 2048/4 .

   So, step resolutoion required = 4*(360/2048)  = 0.703125 ~= 0.7 ;

*/
// excitaton coil 
int coil_A = 10;
int coil_B = 9;
int coil_C = 8;
int coil_D = 7;
float rotate = 90 ;  // in degrees 
int num_pulse = (int)(((float)rotate)/0.7) ;
String command ; 
void setup() {
  pinMode(coil_A , OUTPUT );
  pinMode(coil_B , OUTPUT );
  pinMode(coil_C , OUTPUT );
  pinMode( coil_D , OUTPUT );
  Serial.begin(9600);

}

void loop() {


  //FUNCTION FOR FULL STEP --- TW0-PHASE  ROTATION
  //TWO PHASE ENERSIZED AT A TIME
 

// I AM SENDING 4 PULSE BECAUSE , WE CAN SEE HERE effectilvely for making two coil HIGH simultaneously , one can always use single pulse. 

    
    for(int i = 0 ; i < num_pulse ; i++){
      // A HIGH AND B HIGH CASE
    digitalWrite(coil_D , LOW );               
    digitalWrite(coil_A , HIGH );   
    digitalWrite(coil_B , HIGH);
    digitalWrite(coil_C,LOW);                 
    delay(5);
    // A LOW , B HIGH AND C HIGH CASE 
     digitalWrite(coil_A , LOW );             
     digitalWrite(coil_B , HIGH);
    digitalWrite(coil_C , HIGH);
    digitalWrite(coil_D , LOW );               
    delay(5);
    // A LOW , B LOW , C HIGH AND D HIGH CASE 
    digitalWrite(coil_A , LOW );              
    digitalWrite(coil_B , LOW);
    digitalWrite(coil_C , HIGH);
    digitalWrite(coil_D , HIGH);
    delay(5);
   
    digitalWrite(coil_A , HIGH ); 
    digitalWrite(coil_B , LOW);
    digitalWrite(coil_C,LOW);
    digitalWrite(coil_D , HIGH);
    delay(5);
  
  }
  exit(0) ; 
 
  }
  
