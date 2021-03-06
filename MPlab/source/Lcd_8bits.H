/*********************************************************************
Nome do arquivo:	LCD_8bits.h            
Data:	    		14 de mar�o de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#ifndef __LCD_8BITS_H
#define __LCD_8BITS_H
//*************************************************************
//defini��es do port ligado no LCD
//*
#define PORT_LCD 		PORTD			//LCD ligado no PORTD
#define PORT_CONT_LCD 	PORTE			//PORT de controle do LCD
#define TRIS_PORT_LCD 	TRISD			//dire��o dos pinos
#define TRIS_CONT_LCD 	TRISE			//dire��o dos pinos
//*************************************************************
//defini��es dos pinos de controle
#define _RS PORTEbits.RE0				//pino dado/instru��o
#define _EN PORTEbits.RE1				//pino enable
#define _RW PORTEbits.RE2				//pino escrita/leitura
//*************************************************************
//prot�tipos de fun��es
void IniciaLCD (unsigned char NL);
void Pulse(void);
void _Delay100us(void);
void _Delay5ms(void);
void TestPixelsLCD(void);
void DelayFor20TCY( void);
void DelayFor18TCY( void);
unsigned char TesteBusyFlag(void);
void EscDataLCD(char _data);
void EscInstLCD(unsigned char _inst);
void EscStringLCD(char *buffer);
void EscStringLCD_ROM(const rom char *buffer); //*************************************************************
#endif






