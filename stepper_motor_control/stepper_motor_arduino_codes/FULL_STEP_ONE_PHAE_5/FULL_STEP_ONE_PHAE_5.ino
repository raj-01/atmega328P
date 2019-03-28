
/*
   Stride angle of motor is 5.625 degree per 64 steps.
   Also , there is a geare inside the steper motor of 32 teeths.
   S0 , it requires 64*32 = 2048 steps ( pulse ) from microcontroller, to rotate 360 dgrees.

   So, step resolution is 360/2048 = 0.17578125 ;
   We are sending 4 pulse of HIGH in same for loop , so , number of  pulse  required is 2048/4 .

   So, step resolutoion required = 4*(360/2048)  = 0.703125 ~= 0.7 ;

*/



// excitaton coil 
int coil_A = 7;
int coil_B = 8;
int coil_C = 9;
int coil_D = 10;
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


  //FUNCTION FOR FULL STEP --- ONE-PHASE  ROTATION
  //ONE PHASE ENERSIZED AT A TIME
 
  
    // I AM GIVING 4 PULSE OF HIGH IN ONE LOOP CYCLE 
    
    for(int i = 0 ; i < num_pulse ; i++){
    digitalWrite(coil_A , HIGH );
    delay(5);
    digitalWrite(coil_A,LOW);
    digitalWrite(coil_B , HIGH);
    delay(5);
    digitalWrite(coil_B , LOW);
    digitalWrite(coil_C , HIGH);
    delay(5);
    digitalWrite(coil_C , LOW ) ;
    digitalWrite(coil_D,HIGH );
    delay(5);
    digitalWrite(coil_D,LOW);

    
  }
  exit(0) ; 
 
  }
  
