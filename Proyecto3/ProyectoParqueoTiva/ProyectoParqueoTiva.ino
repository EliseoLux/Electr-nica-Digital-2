
// set pin numbers:
const int buttonPin1 = 11;     // the number of the pushbutton pin1
const int buttonPin2 = 12;     // the number of the pushbutton pin2
const int buttonPin3 = 13;     // the number of the pushbutton pin3
const int buttonPin4 = 14;     // the number of the pushbutton pin4

const int out1 = 31;     // the number of the pushbutton pin1
const int out2 = 32;     // the number of the pushbutton pin2
const int out3 = 33;     // the number of the pushbutton pin3
const int out4 = 34;     // the number of the pushbutton pin4
const int out5 = 35;     // the number of the pushbutton pin5
const int out6 = 36;     // the number of the pushbutton pin6
const int out7 = 37;     // the number of the pushbutton pin7
const int out8 = 38;     // the number of the pushbutton pin8

const int outG = 10;     // the out number to  free spaces

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton1 status
int buttonState2 = 0;         // variable for reading the pushbutton2 status
int buttonState3 = 0;         // variable for reading the pushbutton3 status
int buttonState4 = 0;         // variable for reading the pushbutton4 status

// general variables
int outGnumber = 0;         // variable for reading the pushbutton2 status

void setup() {
  // initialize the LED pin as an output: 
      
  pinMode(out1, OUTPUT);      
  pinMode(out2, OUTPUT);      
  pinMode(out3, OUTPUT);      
  pinMode(out4, OUTPUT);  
  pinMode(out5, OUTPUT);      
  pinMode(out6, OUTPUT);      
  pinMode(out7, OUTPUT);      
  pinMode(out8, OUTPUT);      
      
  pinMode(outG, OUTPUT);      

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT_PULLUP);    
  pinMode(buttonPin2, INPUT_PULLUP);     
  pinMode(buttonPin3, INPUT_PULLUP);     
  pinMode(buttonPin4, INPUT_PULLUP);     

}

void loop(){
  parqueos();
}
void parqueos(){

   //outGnumber = digitalRead(out5) + digitalRead(out6) + digitalRead(out7) + digitalRead(out8);
   //analogWrite(outG, outGnumber);
   //Serial.println(outGnumber);

  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is LOW:
  //*****************
  if (buttonState1 == LOW) {     
    // turn LED on:    
    digitalWrite(out1, HIGH); 
    digitalWrite(out5, LOW);  
 
  } 
  else {
    // turn LED off:
    digitalWrite(out1, LOW);  
    digitalWrite(out5, HIGH);  
 
    }
  //******************
  if (buttonState2 == LOW) {     
    // turn LED on:    
    digitalWrite(out2, HIGH);  
    digitalWrite(out6, LOW);  
 
  } 
  else {
    // turn LED off:
    digitalWrite(out2, LOW);  
    digitalWrite(out6, HIGH);  
 
    }
  //******************
  if (buttonState3 == LOW) {     
    // turn LED on:    
    digitalWrite(out3, HIGH);  
    digitalWrite(out7, LOW);  
    
  } 
  else {
    // turn LED off:
    digitalWrite(out3, LOW);  
    digitalWrite(out7, HIGH);  

    }
  //*****************
  if (buttonState4 == LOW) {     
    // turn LED on:    
    digitalWrite(out4, HIGH);  
    digitalWrite(out8, LOW);  
    
  } 
  else {
    // turn LED off:
    digitalWrite(out4, LOW); 
    digitalWrite(out8, HIGH);  
     
    }
}
