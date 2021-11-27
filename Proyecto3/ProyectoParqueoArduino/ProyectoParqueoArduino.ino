
// set pin numbers:
const int buttonPin1 = 10;     // the number of the pushbutton pin1
const int buttonPin2 = 11;     // the number of the pushbutton pin2
const int buttonPin3 = 12;     // the number of the pushbutton pin3
const int buttonPin4 = 13;     // the number of the pushbutton pin4

const int out1 = 2;     // the number of the pushbutton pin1
const int out2 = 3;     // the number of the pushbutton pin2
const int out3 = 4;     // the number of the pushbutton pin3
const int out4 = 5;     // the number of the pushbutton pin4
const int out5 = 6;     // the number of the pushbutton pin5
const int out6 = 7;     // the number of the pushbutton pin6
const int out7 = 8;     // the number of the pushbutton pin7
const int out8 = 9;     // the number of the pushbutton pin8

//entradas analogicas
int buttonPin5 = A0;
int buttonPin6 = A1;
int buttonPin7 = A2;
int buttonPin8 = A3;

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton1 status
int buttonState2 = 0;         // variable for reading the pushbutton2 status
int buttonState3 = 0;         // variable for reading the pushbutton3 status
int buttonState4 = 0;         // variable for reading the pushbutton4 status
int buttonState5 = 0;         // variable for reading the pushbutton1 status
int buttonState6 = 0;         // variable for reading the pushbutton2 status
int buttonState7 = 0;         // variable for reading the pushbutton3 status
int buttonState8 = 0; 

int State5 = 0;
int State6 = 0;
int State7 = 0;
int State8 = 0;

String txt;

void setup() {
  // initialize the LED pin as an output: 
  Serial.begin(9600);    
  pinMode(out1, OUTPUT);      
  pinMode(out2, OUTPUT);      
  pinMode(out3, OUTPUT);      
  pinMode(out4, OUTPUT);  
  pinMode(out5, OUTPUT);      
  pinMode(out6, OUTPUT);      
  pinMode(out7, OUTPUT);      
  pinMode(out8, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT_PULLUP);    
  pinMode(buttonPin2, INPUT_PULLUP);     
  pinMode(buttonPin3, INPUT_PULLUP);     
  pinMode(buttonPin4, INPUT_PULLUP);     
  //entradas analogicas
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  pinMode(buttonPin7, INPUT);
  pinMode(buttonPin8, INPUT);
}

void loop(){
    escuela();
  
}
void escuela(){

  

  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  
  buttonState5 = analogRead(buttonPin5);
  buttonState6 = analogRead(buttonPin6);
  buttonState7 = analogRead(buttonPin7);
  buttonState8 = analogRead(buttonPin8);

 if(buttonState5 < 600){
  State5 = 1;
 }
 else{
  State5 = 0;
 }
 if(buttonState6 < 600){
  State6 = 1;
 }
 else{
  State6 = 0;
 }
  if(buttonState7 < 600){
  State7 = 1;
 }
 else{
  State7 = 0;
 }
 if(buttonState8 < 600){
  State8 = 1;
 }
 else{
  State8 = 0;
 }
 int conteo = (buttonState1 + buttonState2 + buttonState3 + buttonState4 + State5 + State6 + State7 + State8);
 Serial.println(conteo);
 txt = conteo;
 
//------------------------------------------------------------------------------------------------------------------------------------------


  // check if the pushbutton is pressed.
  // if it is, the buttonState is LOW:
  //*****************
  if (buttonState1 == LOW) {     
    // turn LED on:    
    digitalWrite(out1, HIGH); 
    digitalWrite(out2, LOW);  
 
  } 
  else {
    // turn LED off:
    digitalWrite(out1, LOW);  
    digitalWrite(out2, HIGH);  
 
    }
  //******************
  if (buttonState2 == LOW) {     
    // turn LED on:    
    digitalWrite(out3, HIGH);  
    digitalWrite(out4, LOW);  
 
  } 
  else {
    // turn LED off:
    digitalWrite(out3, LOW);  
    digitalWrite(out4, HIGH);  
 
    }
  //******************
  if (buttonState3 == LOW) {     
    // turn LED on:    
    digitalWrite(out5, HIGH);  
    digitalWrite(out6, LOW);  
    
  } 
  else {
    // turn LED off:
    digitalWrite(out5, LOW);  
    digitalWrite(out6, HIGH);  

    }
  //*****************
  if (buttonState4 == LOW) {     
    // turn LED on:    
    digitalWrite(out7, HIGH);  
    digitalWrite(out8, LOW);  
    
  } 
  else {
    // turn LED off:
    digitalWrite(out7, LOW); 
    digitalWrite(out8, HIGH);  
     
    }
 delay(1500);
}
