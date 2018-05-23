/*********************************************************************
Nome do arquivo:	amarme1.c   
Proteus:            SimpleProject4         
Data:	    		28 de dezembro de 2008          
Versao:				1.0                              
MPLAB IDE:			MPLAB-X v 4.10 
Autor:				Carl�cio Silva              
*********************************************************************/
#include <p18f4550.h>		//diretiva de compila��o
#include "MCC18_18F4550.h"

//Constantes
#define CHAVE_A PORTBbits.RB2
#define CHAVE_B PORTBbits.RB3
#define AL_DISPARADO PORTDbits.RD0
#define AL_DEFEITO   PORTDbits.RD1
#define AL_NORMAL    PORTDbits.RD2

//********************************************************************
//prot�tipos de fun��es
 void Inic_Regs (void);
//********************************************************************
 
void main(void)					//fun��o main					
{	    
	Inic_Regs ();				//chamada a func�o
        
	while (1)				//loop infinito
	{   
        // 1- VERIFICA SE ALARME EST� OPERANDO NORMALMENTE
        if(CHAVE_A ^ CHAVE_B){
            AL_DEFEITO = 0; // RESET DO LED INDICADOR DE DEFEITO
            AL_NORMAL = 1;  // SET DO LED INDICADOR NORMALIDADE
            // 2- VERIFICA SE ALARME DISPAROU
            if(!CHAVE_A){
               AL_DISPARADO = 1; // SET DO LED INDICADOR DE INVAS�O 
            }
            else AL_DISPARADO = 0; // RESET DO LED INDICAR DE INVAS�O
        }	
        else{
            AL_DEFEITO = 1;   // SET DO LED INDICADOR DE DEFEITO
            AL_NORMAL = 0;    // RESET DO LED INDICADOR DE NORMALIDADE
            AL_DISPARADO = 0; // RESET DO LED INDICADOR DE INVAS�O
        }
	}
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
	PORTD = 0;			    //apaga LEDs
	PORTE = 0;				//limpa PORTE
//********************************************************************
}
