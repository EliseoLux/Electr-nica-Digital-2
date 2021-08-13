//Master

// Archivo: main.c
// Dispositivo: PIC16F887
// Autor: Eliseo Lux
// Compilador: XC-8 (v2.32)
//
// Programa: I2C
// Hardware: 3 PIC16f887, 2 pots, 4LEDs, LCD, sensor i2c
//

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = ON       
#pragma config CP = OFF         
#pragma config CPD = OFF        
#pragma config BOREN = ON       
#pragma config IESO = ON        
#pragma config FCMEN = ON       
#pragma config LVP = OFF         

// CONFIG2
#pragma config BOR4V = BOR40V   
#pragma config WRT = OFF        

#define _XTAL_FREQ  4000000
#include<xc.h>
#include<pic.h>
#include<stdint.h>
#include<string.h>
#include"Libreria.h"


//|-------------------------------VARIABLES------------------------------------|

uint16_t analog0;
uint16_t analog0_temp;

uint8_t counter=0;
uint8_t counter_temp;

uint8_t temperature_sensor;
uint8_t temperature_sensor_temp;
//------------------------------------------------------------------------------

void setup(void);
void __interrupt() isr(void);



void    main(void){
    setup();
    Lcd_Write_String("  S1    S2    S3 ");

    uint8_t v0;
    uint8_t m0;
    uint8_t c0;
    uint8_t d0;
    uint8_t u0;
    
    uint8_t mc;
    uint8_t cc;
    uint8_t dc;
    uint8_t uc;
    

    uint8_t     mt;
    uint8_t     ct;
    uint8_t     dt;
    uint8_t     ut;
    
    
    while(1){
        I2C_Master_Start();
        I2C_Master_Write(0b00000001);
        analog0 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0b00000011);
        counter = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        
        
        I2C_Master_Start();
        I2C_Master_Write(0x80);
        I2C_Master_Write(0xF3);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0b10000001);
        temperature_sensor = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        if(analog0_temp !=  analog0 | counter_temp!=counter | temperature_sensor_temp  !=  temperature_sensor){
            divide(analog0, &m0, &c0, &d0, &u0);
            divide(counter, &mc, &cc, &dc, &uc);
            divide(temperature_sensor, &mt, &ct, &dt, &ut);
            analog0_temp =  analog0;
            counter_temp =  counter;
            temperature_sensor_temp =   temperature_sensor;
            //Write V1 on LCD
            Lcd_Cmd(0b11000000);
            Lcd_Write_String(" ");
            Lcd_Write_Char(c0+48);
            Lcd_Write_Char(d0+48);
            Lcd_Write_Char(u0+48);
            Lcd_Write_String("   ");
            Lcd_Write_Char(dc+48);
            Lcd_Write_Char(uc+48);
            Lcd_Write_String("   ");
            Lcd_Write_Char(ct+48);
            Lcd_Write_Char(dt+48);
            Lcd_Write_Char(ut+48);
        }
    }

}
//Funciones

void setup(void){
   
    ANSEL   =   0;
    ANSELH  =   0;
    TRISA   =   0;
    TRISB   =   0;
    TRISC   =   0b10010000;
    TRISD   =   0;
    TRISE   =   0;

   
    GIE     =   1;
    PEIE    =   1;
    ADIE    =   1;
    
    
    Lcd_Init();
    
    I2C_Master_Init(100000);
    
    
    PORTA   =   0;
    PORTB   =   0;
    PORTC   =   0;
    PORTD   =   0;
    PORTE   =   0;
    
    
    
}

//Interrupciones
void __interrupt() isr(void){

}
