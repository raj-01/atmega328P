

/*
   Stride angle of motor is 5.625 degree per 64 steps.
   Also , there is a geare inside the steper motor of 32 teeths.
   S0 , it requires 64*32 = 2048 steps from microcontroller, to rotate 360 dgrees.

   ** Here because its a superposetion of both full-step-exitation , so , it requires 2 pulse two rotate 1 step  
   * * Hence , 2*2048 pulse for 360 degree rotation. 

   So, step resolution is 360/(2*2048) = 0.17578125/2 ;
   We are sending 8 pulse of HIGH and LOW in same for loop , so , number of steps ( pulse ) required is (2*2048)/8 = 2048/4 .

   So, step resolutoion required = 4*(360/2048)  = 0.703125 ~= 0.7 ;

*/
// excitaton coil 
int coil_A = 10;
int coil_B = 9;
int coil_C = 8;
int coil_D = 7;
float rotate = 60 ;  // in degrees 
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


  //FUNCTION FOR HALF STEP  EXITATION 
  //SUPER POSITION OF ONE PHAE AND TWO PHASE ENERGISED AT A TIME 

    // I AM GIVING 8 HIGH PULSE IN ONE LOOP CYCLE , WE CAN SEE HERE effectilvely for making two coil HIGH simultaneously , one can always use single pulse.
    
    for(int i = 0 ; i < num_pulse ; i++){

      // MAKING A HIGH 
      digitalWrite(coil_A , HIGH ); 
      delay(5);
      digitalWrite(coil_A , LOW );     // not required but writen for redability 
      // A HIGH AND B HIGH CASE
    digitalWrite(coil_D , LOW );
    digitalWrite(coil_A , HIGH );   
    digitalWrite(coil_B , HIGH);
    digitalWrite(coil_C,LOW);         // not required but writen for redability
    
    delay(5);
    digitalWrite(coil_B , HIGH);
    delay(5);
    digitalWrite(coil_B , LOW);       // not required but writen for redability
   
    // A LOW , B HIGH AND C HIGH CASE 
     digitalWrite(coil_A , LOW );
     digitalWrite(coil_B , HIGH);
    digitalWrite(coil_C , HIGH);
    digitalWrite(coil_D , LOW );        // not required but writen for redability
    
    delay(5);
    digitalWrite(coil_C , HIGH);
    delay(5);
    digitalWrite(coil_C , LOW);             // not required but writen for redability
    // A LOW , B LOW , C HIGH AND D HIGH CASE 
    digitalWrite(coil_A , LOW );            // not required but writen for redability
    digitalWrite(coil_B , LOW);
    digitalWrite(coil_C , HIGH);
    digitalWrite(coil_D , HIGH);            
    
    delay(5);
    digitalWrite(coil_D , HIGH);
    delay(5);
    digitalWrite(coil_D , LOW);             // not required but writen for redability
   
    // A HIGH , B LOW , C LOW AND D HIGH CASE
    digitalWrite(coil_A , HIGH );         
    digitalWrite(coil_B , LOW);              // not required but writen for redability
    digitalWrite(coil_C,LOW);
    digitalWrite(coil_D , HIGH);             
    delay(5);
  
  }
  exit(0) ; 
 
  }
  
