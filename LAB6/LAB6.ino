#define rojo RED_LED    //pin 30 PF_1
#define verde GREEN_LED //pin 39 PF_3
#define azul BLUE_LED   //pin 40 PF_2
#define sw1 PUSH1       //pin 31 PF_4
#define sw2 PUSH2       //pin 17 PF_0

byte estado1 = 0;   //se almacenara los el valor de cada pulsador
byte estado2 = 0;
byte old_estado1 = 0;   //anti-rebote
byte old_estado2 = 0;
byte valor1 = 0;   //pulsacion de cada jugador
byte valor2 = 0;
bool lux = 0;     //solamente puede ser 1 o 0



void setup() {
  //declaracion de pulsadores como entrada
  pinMode(sw1, INPUT_PULLUP); 
  pinMode(sw2, INPUT_PULLUP); 
  
  //declaracion de leds como salida
  pinMode(verde, OUTPUT);     
  pinMode(rojo, OUTPUT);
  pinMode(azul, OUTPUT);

  pinMode(23, OUTPUT);  
  pinMode(24, OUTPUT);  
  pinMode(25, OUTPUT);  


  Serial.begin(9600);
  delay(1);
  Serial.println("Juego de carreras");
 
}

void loop() {
  //se utilizará para el antirebote
  old_estado1 = estado1;  
  old_estado2 = estado2;
  //se asigna a estado 1 y 2, los datos de los pulsadores
  estado1 = digitalRead(sw1);
  estado2 = digitalRead(sw2);

  if ((estado1 == 0 || estado2 == 0) && lux == 0) { //Pulsador1 o 2 inicia el juego
    lux = 1;
    Serial.println("Rojo");
    digitalWrite(23, 1);
    digitalWrite(24, 0);
    digitalWrite(25, 0);
    delay(1000);
    Serial.println("Amarillo");
    digitalWrite(23, 0);
    digitalWrite(24, 1);
    digitalWrite(25, 0);
    delay(1000);
    Serial.println("Verde");
    digitalWrite(23, 0);
    digitalWrite(24, 0);
    digitalWrite(25, 1);
    delay(1000);
    Serial.println("Empieza la carrera:");
    digitalWrite(23, 0);
    digitalWrite(24, 0);
    digitalWrite(25, 0);
    //se resetean los valores
    estado1 = 0;
    estado2 = 0;
  }

  if (lux) {
    if (estado1 == 0 && estado2 == 1) { //sw1 presionado, suma
      if (estado1 != old_estado1) {
        valor1++;

        Serial.print("CorredorUno = ");
        Serial.print(valor1);
        Serial.print("  CorredorDos = ");
        Serial.println(valor2);

        digitalWrite(azul, 1);
        digitalWrite(rojo, 0);
      }
    }
    else if (estado1 == 1 && estado2 == 0) { //sw2 presionado, suma
      if (estado2 != old_estado2) {
        valor2++;

        Serial.print("CorredorUno = ");
        Serial.print(valor1);
        Serial.print("  CorredorDos = ");
        Serial.println(valor2);

        digitalWrite(azul, 0);
        digitalWrite(rojo, 1);
      }
    }

    if ((valor1 >= 8) || (valor2 >= 8) ) {
      digitalWrite(rojo, 1);
      digitalWrite(verde, 1);
      digitalWrite(azul, 1);
      delay(2000);

      if (valor1 >= 8) {
        Serial.println(" CorredorUno ha ganado \n");
        digitalWrite(rojo, 0);
        digitalWrite(verde, 0);
        digitalWrite(azul, 1);
        delay(1000);
        digitalWrite(rojo, 0);
        digitalWrite(verde, 0);
        digitalWrite(azul, 0);
        delay(1000);
        digitalWrite(rojo, 0);
        digitalWrite(verde, 0);
        digitalWrite(azul, 1);
      } else {
        Serial.println(" CorredorDos ha ganado \n");
        digitalWrite(rojo, 1);
        digitalWrite(verde, 0);
        digitalWrite(azul, 0);
        delay(1000);
        digitalWrite(rojo, 0);
        digitalWrite(verde, 0);
        digitalWrite(azul, 0);
        delay(1000);
        digitalWrite(rojo, 1);
        digitalWrite(verde, 0);
        digitalWrite(azul, 0);

      }
      valor1 = 0;  //se reinician los valores
      valor2 = 0;
      lux = 0;
      delay(1300);
      digitalWrite(rojo, 0);
      digitalWrite(verde, 0);
      digitalWrite(azul, 0);

      Serial.println("Inicia de nuevo el juego de carreras");
    }
  }
}
