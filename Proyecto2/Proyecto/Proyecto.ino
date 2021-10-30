//***************************************************************************************************************************************
/* Código de ejemplo de videojuego:
 * Detección de colisiones con objetos rectangulares.
 * Emplea estructuras para definir clases e instanciar objetos.
 * Incorpora actualización de cuadros cada 42ms ( aprox. 24fps).
 * Movimiento de sprite utilizando botones integrados.
 * Basado en librería para el uso de la pantalla ILI9341 en modo 8 bits
 * Autor: Diego Morales
 * IE3027: Electrónica Digital 2 - 2021
 */
//***************************************************************************************************************************************
#include <SPI.h>//librerias
#include <SD.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "font.h"
#include "lcd_registers.h"

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
#define TIEMPO 5 //tiempo en milisegundos
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};  

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0
 
// change this to make the song slower or faster
int tempo=140; 
 
// change this to whichever pin you want to use
int buzzer = 37;
 
// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[]PROGMEM = {
 
  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
  
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,
 
  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,
 
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,
 
  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,
  
 
  NOTE_E5,2,  NOTE_C5,2,
  NOTE_D5,2,   NOTE_B4,2,
  NOTE_C5,2,   NOTE_A4,2,
  NOTE_GS4,2,  NOTE_B4,4,  REST,8, 
  NOTE_E5,2,   NOTE_C5,2,
  NOTE_D5,2,   NOTE_B4,2,
  NOTE_C5,4,   NOTE_E5,4,  NOTE_A5,2,
  NOTE_GS5,2,
 
};
 
// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes=sizeof(melody)/sizeof(melody[0])/2; 
 
// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int wholenote = (60000 * 4) / tempo;
 
int divider = 0, noteDuration = 0;
int delay_musica;
unsigned long millis_musica;
int thisNote;

//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);
bool Collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

extern uint8_t marioBitmap[]; // cargar bitmap desde memoria flash

struct Sprite { // estructura para sprites
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de bitmap
  int height; // altura de bitmap
  int columns; // columna sprite sheet
  int index; // indice sprite sheet
  int flip; // voltear imagen
  int offset; // desfase
} mario;

struct Rectangle{ // estructura para rectangulos
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de rectángulo
  int height; // altura de rectángulo
  int color; // color de relleno  
} rect;

struct Rectangle2{ // estructura para rectangulos
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de rectángulo
  int height; // altura de rectángulo
  int color; // color de relleno  
} rect2;

struct Rectangle3{ // estructura para rectangulos
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de rectángulo
  int height; // altura de rectángulo
  int color; // color de relleno  
} rect3;

struct Rectangle4{ // estructura para rectangulos
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de rectángulo
  int height; // altura de rectángulo
  int color; // color de relleno  
} rect4;

struct Rectangle5{ // estructura para rectangulos
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de rectángulo
  int height; // altura de rectángulo
  int color; // color de relleno  
} rect5;

struct Rectangle6{ // estructura para rectangulos
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de rectángulo
  int height; // altura de rectángulo
  int color; // color de relleno  
} rect6;

struct Rectangle7{ // estructura para rectangulos
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de rectángulo
  int height; // altura de rectángulo
  int color; // color de relleno  
} rect7;

bool rectUp = false; // dirección rectángulo
bool collision = false; // detección de colisión
bool collision2 = false; // detección de colisión
bool collision3 = false; // detección de colisión
bool collision4 = false; // detección de colisión
bool collision5 = false; // detección de colisión
bool collision6 = false; // detección de colisión
bool collision7 = false; // detección de colisión

unsigned long previousMillis = 0;  
const long interval = 42;

int lecturaButton = 1;
int lecturaAnteriorEstable = 1;
int buttonAnterior = 1;
boolean jugando = false; // para indicar que se esta iniciando la partida
unsigned long timeButton = 0;

File dataFile;
File myFile;
const int chipSelect = 12; //cs PIN
int ASCII_HEX(int a);
void mapeo_SD(char doc[]);

//***************************************************************************************************************************************
// Initialization
//***************************************************************************************************************************************
void setup() {
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Start");
  SPI.setModule(0);         //Indespensable declarar el SPI a usar en TIVA C
  delay(2500);              //Tiempo para abrir la terminal serial
  Serial.print("\nInitializing SD card...\n");
  pinMode(12, OUTPUT);     // change this to 53 on a mega or 12 on a Tiva C
  if (!SD.begin(chipSelect)) {        //Inicio la comunicacion a la SD pero en config. de lectura/escritura
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  LCD_Init();
  LCD_Clear(0xE36B2C);

  
  pinMode(PUSH1, INPUT_PULLUP); // botones integrados con como entrada pull-up
  pinMode(PUSH2, INPUT_PULLUP);

  mario.x = 0;
  mario.y = 100;
  mario.width = 16;
  mario.height = 32;
  mario.columns = 8;
  mario.index = 0;
  mario.flip = 0;
  mario.offset = 0;
  
//rectangulo 1
  rect.x = 35;
  rect.y = 80;
  rect.width = 20;
  rect.height = 65;
  rect.color = 0x00FFFF;
//rectangulo 2
  rect2.x = 107;
  rect2.y = 0;
  rect2.width = 10;
  rect2.height = 30;
  rect2.color = 0x00FFFF;
//rectangulo 3
  rect3.x = 107;
  rect3.y = 100;
  rect3.width = 10;
  rect3.height = 30;
  rect3.color = 0x00FFFF;
//rectangulo 4
  rect4.x = 180;
  rect4.y = 0;
  rect4.width = 20;
  rect4.height = 70;
  rect4.color = 0x00FFFF;
//rectangulo 5
  rect5.x = 250;
  rect5.y = 0;
  rect5.width = 10;
  rect5.height = 30;
  rect5.color = 0x00FFFF;
//rectangulo 6
  rect6.x = 250;
  rect6.y = 100;
  rect6.width = 10;
  rect6.height = 30;
  rect6.color = 0x00FFFF;
  
//rectangulo 7
  rect7.x = 313;
  rect7.y = 0;
  rect7.width = 10;
  rect7.height = 240;
  rect7.color = 0x00FF00;
 
}
//***************************************************************************************************************************************
// Loop
//***************************************************************************************************************************************
void loop(){

  readButton();
 if (lecturaAnteriorEstable == 0 && lecturaButton ==1 && !jugando){ //Pulsador1 o 2 inicia el juego
    jugando = true;
    LCD_Clear(  0x0000);
    
 }
 if(jugando){
    funcion();
    cancion();
  }
  else{
    menu();
    
  }
}
void fotomenu(){
  myFile = SD.open("1.TXT", FILE_READ);
  if (myFile) {// Leer datos de SD y mostrar en pantalla
      LCD_Clear(0x00);
      int wid = 0;// limpiar pantalla e imprimir nueva
      int hei = 0;
      LCD_CMD(0x02c); // write_memory_start

      digitalWrite(LCD_RS, HIGH);
      digitalWrite(LCD_CS, LOW);
     
      SetWindows(0, 0, 319, 239);// poner pantalla
      while (myFile.available()) {

    }
  }
}
void readButton(){
  // antirebote para el boton
    int lectura = digitalRead(PUSH1);

    if (lectura !=buttonAnterior) timeButton = millis();

    if (millis() - timeButton > TIEMPO ){
      lecturaAnteriorEstable = lecturaButton;
      lecturaButton = lectura;
    }

    buttonAnterior = lectura;   
}
void cancion(void){
  if (millis() >= delay_musica + millis_musica) {
    millis_musica = millis();
    thisNote = thisNote + 2;
    if (thisNote < notes * 2) {
      // calculates the duration of each note
      divider = melody[thisNote + 1];
      if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }
      tone(buzzer, melody[thisNote], noteDuration * 0.9);
      delay_musica = noteDuration;
    }
  }

  // para reiniciar la musica (esto tambien se coloca cuando se pierde)
  if (thisNote > notes * 2) {
    thisNote = 0;
    delay_musica = 0;
    notes = sizeof(melody) / sizeof(melody[0]) / 2;
    wholenote = (60000 * 4) / tempo;
    divider = 0, noteDuration = 0;
  }
}
void menu(void){

   String text1 = "Presionar boton";
   String text2 = "para comenzar";
  LCD_Print(text1, 40, 90, 2, 0xffff, 0xE36B2C);
  LCD_Print(text2, 50, 120, 2, 0xffff, 0xE36B2C);

}
void funcion(void){
  
  unsigned long currentMillis = millis();
  
  // actualización de frame cada 42ms = 24fps
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    bool left = !digitalRead(PUSH1); // lectura de entradas
    bool right = !digitalRead(PUSH2);
    if (right) { // modificación de atributos de sprite
      mario.x += 4;
      mario.index++;
      mario.index %= 3;
      mario.flip = 1;
    }
    if (left) {
      mario.x -= 4;
      mario.index++;
      mario.index %= 3;
      mario.flip = 0;
    }
//______________________________________________________________________________________________________________________________
    if (rectUp) { // movimiento de rectángulo
      FillRect(rect.x, rect.y + rect.height - 5, rect.width, 5, 0x0000);// se colorea resto de rectángulo del frame anterior
      rect.y-= 5;
      if (rect.y <= 0) {
        rectUp = false;
      }
      FillRect(rect2.x, rect2.y + rect2.height - 5, rect2.width, 5, 0x0000);// se colorea resto de rectángulo del frame anterior
      rect2.y-= 5;
      if (rect2.y <= 0) {
        rectUp = false;
      }
      FillRect(rect3.x, rect3.y + rect3.height - 5, rect3.width, 5, 0x0000);// se colorea resto de rectángulo del frame anterior
      rect3.y-= 5;
      if (rect3.y <= 0) {
        rectUp = false;
      }
      FillRect(rect4.x, rect4.y + rect4.height - 5, rect4.width, 5, 0x0000);// se colorea resto de rectángulo del frame anterior
      rect4.y-= 5;
      if (rect4.y <= 0) {
        rectUp = false;
      }
      FillRect(rect5.x, rect5.y + rect5.height - 5, rect5.width, 5, 0x0000);// se colorea resto de rectángulo del frame anterior
      rect5.y-= 5;
      if (rect5.y <= 0) {
        rectUp = false;
      }
      FillRect(rect6.x, rect6.y + rect6.height - 5, rect6.width, 5, 0x0000);// se colorea resto de rectángulo del frame anterior
      rect6.y-= 5;
      if (rect6.y <= 0) {
        rectUp = false;
      }
    }
    
    else {
      FillRect(rect.x, rect.y, rect.width, 5, 0x0000);
      rect.y+= 5;
      if (rect.y >= 200) {
        rectUp = true;
        }
      FillRect(rect2.x, rect2.y, rect2.width, 5, 0x0000);
      rect2.y+= 5;
      if (rect2.y >= 200) {
        rectUp = true;
      }
      FillRect(rect3.x, rect3.y, rect3.width, 5, 0x0000);
      rect3.y+= 5;
      if (rect3.y >= 200) {
        rectUp = true;
        }
      FillRect(rect4.x, rect4.y, rect4.width, 5, 0x0000);
      rect4.y+= 5;
      if (rect4.y >= 200) {
        rectUp = true;
      }
      FillRect(rect5.x, rect5.y, rect5.width, 5, 0x0000);
      rect5.y+= 5;
      if (rect5.y >= 200) {
        rectUp = true;
        }
      FillRect(rect6.x, rect6.y, rect6.width, 5, 0x0000);
      rect6.y+= 5;
      if (rect6.y >= 200) {
        rectUp = true;
      }
   
    }  
    }

//______________________________________________________________________________________________________________________________
    collision = Collision(mario.x, mario.y, mario.width, mario.height,
                          rect.x, rect.y, rect.width, rect.height); // detección de colisión
    collision2 = Collision(mario.x, mario.y, mario.width, mario.height,
                          rect2.x, rect2.y, rect2.width, rect2.height); // detección de colisión
    collision3 = Collision(mario.x, mario.y, mario.width, mario.height,
                          rect3.x, rect3.y, rect3.width, rect3.height); // detección de colisión
    collision4 = Collision(mario.x, mario.y, mario.width, mario.height,
                          rect4.x, rect4.y, rect4.width, rect4.height); // detección de colisión
    collision5 = Collision(mario.x, mario.y, mario.width, mario.height,
                          rect5.x, rect5.y, rect5.width, rect5.height); // detección de colisión
    collision6 = Collision(mario.x, mario.y, mario.width, mario.height,
                          rect6.x, rect6.y, rect6.width, rect6.height); // detección de colisión
    collision7 = Collision(mario.x, mario.y, mario.width, mario.height,
                          rect7.x, rect7.y, rect7.width, rect7.height); // detección de colisión
                          

    FillRect(rect.x, rect.y, rect.width, rect.height, rect.color);
    FillRect(rect2.x, rect2.y, rect2.width, rect2.height, rect2.color);
    FillRect(rect3.x, rect3.y, rect3.width, rect3.height, rect3.color);
    FillRect(rect4.x, rect4.y, rect4.width, rect4.height, rect4.color);
    FillRect(rect5.x, rect5.y, rect5.width, rect5.height, rect5.color);
    FillRect(rect6.x, rect6.y, rect6.width, rect6.height, rect6.color);
    FillRect(rect7.x, rect7.y, rect7.width, rect7.height, rect7.color);
    
    
    if (mario.flip == 1){ // dependiendo de la dirección, se colorea resto del sprite del frame anterior
      FillRect(mario.x - 4, mario.y, 4, mario.height, 0x0000);
    }
    else{
      FillRect(mario.x + mario.width, mario.y, 4, mario.height, 0x0000);
    }
    LCD_Sprite(mario.x, mario.y, mario.width, mario.height, marioBitmap, mario.columns, mario.index, mario.flip, mario.offset);
      
      if (collision || collision2 || collision3 || collision4 || collision5 || collision6) { // se reemplaza el color al colisionar
      LCD_Clear(0xffff00);
      String text1 = "Game Over";
      LCD_Print(text1, 80, 110, 2, 0x0000, 0xffff00);
      delay(900);
      LCD_Clear(0xE36B2C);
      jugando = false;
      mario.x = 0;
      mario.y = 100;
      mario.width = 16;
      mario.height = 32;
      mario.columns = 8;
      mario.index = 0;
      mario.flip = 0;
      mario.offset = 0; 
    }
      if (collision7) { // se reemplaza el color al colisionar
      LCD_Clear(0xE69DFB);
      String text1 = "Haz ganado";
      LCD_Print(text1, 80, 110, 2, 0x0000, 0xE69DFB);
      delay(900);
      LCD_Clear(0xE36B2C);
      jugando = false;
      mario.x = 0;
      mario.y = 100;
      mario.width = 16;
      mario.height = 32;
      mario.columns = 8;
      mario.index = 0;
      mario.flip = 0;
      mario.offset = 0; 
    }
    else {
      rect.color = 0x00FFFF;
      rect2.color = 0x00FFFF;
      rect3.color = 0x00FFFF;
      rect4.color = 0x00FFFF;
      rect5.color = 0x00FFFF;
      rect6.color = 0x00FFFF;

    }
  }
  

//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++){
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER) 
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40|0x80|0x20|0x08); // LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
//  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on 
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);   
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);   
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);   
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);   
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c){  
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);   
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
    }
  digitalWrite(LCD_CS, HIGH);
} 
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i,j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8); 
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);  
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+w;
  y2 = y+h;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = w*h*2-1;
  unsigned int i, j;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c); 
      k = k - 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background) 
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;
  
  if(fontSize == 1){
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if(fontSize == 2){
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }
  
  char charInput ;
  int cLength = text.length();
  Serial.println(cLength,DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength+1];
  text.toCharArray(char_array, cLength+1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1){
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2){
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]){  
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+width;
  y2 = y+height;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      //LCD_DATA(bitmap[k]);    
      k = k + 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset){
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 

  unsigned int x2, y2;
  x2 =   x+width;
  y2=    y+height;
  SetWindows(x, y, x2-1, y2-1);
  int k = 0;
  int ancho = ((width*columns));
  if(flip){
    for (int j = 0; j < height; j++){
        k = (j*(ancho) + index*width -1 - offset)*2;
        k = k+width*2;
       for (int i = 0; i < width; i++){
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k+1]);
        k = k - 2;
       } 
    }
  }
  else{
     for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width + 1 + offset)*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k + 2;
     } 
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//*****************************************************************************
// Retorno de numero decimal a partir de hexadecimal
//*****************************************************************************
int ASCII_HEX(int a) {
  switch (a) {
    case 48:
      return 0;
    case 49:
      return 1;
    case 50:
      return 2;
    case 51:
      return 3;
    case 52:
      return 4;
    case 53:
      return 5;
    case 54:
      return 6;
    case 55:
      return 7;
    case 56:
      return 8;
    case 57:
      return 9;
    case 97:
      return 10;
    case 98:
      return 11;
    case 99:
      return 12;
    case 100:
      return 13;
    case 101:
      return 14;
    case 102:
      return 15;
  }
}
//*****************************************************************************
// leer la sd espacio por espacio
//*****************************************************************************
void mapeo_SD(char doc[]) {
  dataFile = SD.open(doc, FILE_READ);
  int hex1 = 0;
  int val1 = 0;       
  int val2 = 0;
  int mapear = 0;
  int vertical = 0;
  unsigned char maps[640];//320*240

  if (dataFile) {
    Serial.println("Abriendo el archivo");
    while (dataFile.available() ) {
      mapear = 0;
      while (mapear < 640) {
        hex1 = dataFile.read();
        if (hex1 == 120) {
          val1 = dataFile.read();
          val2 = dataFile.read();
          val1 = ASCII_HEX(val1);
          val2 = ASCII_HEX(val2);
          maps[mapear] = val1 * 16 + val2;
          mapear++;
        }
      }
      LCD_Bitmap(0, vertical, 320, 1, maps);
      vertical++;
    }
    dataFile.close();
    Serial.println("cierro");
  } else {
    Serial.println("error opening el doc");
    dataFile.close();
  }
}
bool Collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
  return (x1 < x2 + w2) && (x1+ w1 > x2) && (y1 < y2 + h2) && (y1 + h1 > y2);
}
