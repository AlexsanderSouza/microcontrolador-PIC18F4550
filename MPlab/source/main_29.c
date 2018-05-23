/*********************************************************************
Nome do arquivo:	main_29.c            
Data:	    		28 de dezembro de 2008          
Versao:				1.0                              
MPLAB IDE:			v8.10 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4550.h>		//diretiva de compila��o
#include "MCC18_18F4550.h"

//********************************************************************
//prot�tipos de fun��es
 void Inic_Regs (void);
//********************************************************************
void main(void)					//fun��o main					
{	
    unsigned char A, B, C;
    
    A = 0b11110011;
    B = 0b00110011;
    
    C = A & B;
    
    C = A | B;
    
    C = ~A;
    
	Inic_Regs ();				//chamada a func�o
    
	while (1);				//loop infinito
//	{
////		if (PORTBbits.RB2==0)PORTD = 0b00000001;			//led3 emite se bot�o BT1 estiver pressionado
//////		else	if (PORTBbits.RB3==0)PORTD = 0b00000010;	//se n�o, led2 emite se bot�o BT2 estiver pressionado
//////		else	if (PORTBbits.RB4==0)PORTD = 0b00000100;	//se n�o, led1 emite se bot�o BT3 estiver pressionado
//////        else	if (PORTBbits.RB5==0)PORTD = 0b00001000;	//se n�o, led1 emite se bot�o BT3 estiver pressionado
////		else 	PORTD = 0x00;	 					//se n�o, acende todos os leds se nenhum bot�o estiver pressionado					
//	}
}
/*******************************************************************
Esta funcao inicializa os resgistradores SFRs.*/
 void Inic_Regs (void)
{
	TRISA = 0x00;			//PORTA sa�da
	TRISB = 0x3C;			//pinos RB5:RB2 entrada e demais pinos do PORTB sa�da
	TRISC = 0x00;			//PORTC saida
	TRISD = 0x00;			//PORTD saida
	TRISE = 0x00;			//PORTE saida
	ADCON1 = 0x0F;			//configura pinos dos PORTA e PORTE como digitais
	PORTA = 0;				//limpa PORTA
	PORTB = 0;				//limpa PORTB
	PORTC = 0;				//limpa PORTC
	PORTD = 0xFF;			//apaga LEDs
	PORTE = 0;				//limpa PORTE
//********************************************************************
}
