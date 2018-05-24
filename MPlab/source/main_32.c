/*********************************************************************
Nome do arquivo:	main_32.c            
Data:	    		29 de mar�o de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>			//diretiva de compila��o
//#include <delays.h>			//diretiva de compila��o
#include "Lcd_8bits.h"			//diretiva de compila��o
//********************************************************************
//prot�tipos de fun��es
 void Inic_Regs (void);
 //********************************************************************
void main(void)										//fun��o main					
{	
char buf [17] = {"Seja bem vindo!"};				//declara��o de vetor inicializado
char buf02 [17] = {"   LCD 16 x 2"};				//declara��o de vetor inicializado
int dly=0;											//declara��o de vari�vel local inicializada
//**********************************
	Inic_Regs ();									//configurar SFRs
	IniciaLCD (2);									//inicializar LCD controller HD44780
	TestPixelsLCD();								//teste no LCD - acende todos os pixels.
//**********************************
//delay de 3 segundos
	for(dly=0;dly<600;dly++)						//comando de itera��o
	{
		_Delay5ms();								//delay de 5ms
	}
//**********************************
	EscInstLCD(0x01);								//limpa display e mostra cursor piscando na primeira posi��o da primmeira linha
	while(TesteBusyFlag());							//espera LCD controller terminar de executar instru��o

	EscStringLCD(buf);								//escreve string no LCD
	while(TesteBusyFlag());							//espera LCD controller terminar de executar instru��o

	EscInstLCD(0xC0);								//posiciona cursor na primeir aposic��o  da segunda linha
	while(TesteBusyFlag());							//espera LCD controller terminar de executar instru��o

	EscStringLCD(buf02);							//escreve string no LCD					
	while(TesteBusyFlag());							//espera LCD controller terminar de executar instru��o

	EscInstLCD(0x0C);								//desativa cursor
	while(TesteBusyFlag());							//espera LCD controller terminar de executar instru��o
	while(1);										//loop infinito
}
/*******************************************************************
Esta funcao inicializa os resgistradores SFRs.*/
 void Inic_Regs (void)
{
	TRISA = 0x00;			//PORTA sa�da
	TRISB = 0x00;			//PORTB sa�da
	TRISC = 0x00;			//PORTC sa�da
	TRISD = 0x00;			//PORTD sa�da
	TRISE = 0x00;			//PORTE sa�da
	ADCON1 = 0x0F;			//configura pinos dos PORTA e PORTE como digitais
	PORTA = 0;				//limpa PORTA
	PORTB = 0;				//limpa PORTB
	PORTC = 0;				//limpa PORTC
	PORTD = 0x00;			//apaga displays
	PORTE = 0;				//limpa PORTE
//********************************************************************
}

