/*********************************************************************
Nome do arquivo:	amarme1.c   
Proteus:            SimpleProject4-MUX-1         
Data:	    		29 de mar�o de 2018          
Versao:				1.0                              
MPLAB IDE:			MPLAB-X v 4.10 
Autor:				Carl�cio Silva              
*********************************************************************/
#include <p18f4550.h>		//diretiva de compila��o
#include "MCC18_18F4550.h"
#include <delays.h>

//Constantes
#define CHAVE_A PORTBbits.RB0
#define CHAVE_B PORTBbits.RB1
#define AL_DISPARADO PORTBbits.RB2
#define AL_DEFEITO   PORTBbits.RB3
#define AL_NORMAL    PORTBbits.RB4

//********************************************************************
//prot�tipos de fun��es
 void Inic_Regs(void);
 void alarmeSensor(void);
//********************************************************************
 
void main(void)					//fun��o main					
{	    
    unsigned char cont = 0b00000001; 
    
	Inic_Regs ();				//chamada a func�o
        
	while (1)				//loop infinito
	{
        PORTC = cont;
        switch(cont){
            case 1:
                alarmeSensor();
                if(AL_DISPARADO)PORTDbits.RD0 = 1;
                break;
            case 2:
                alarmeSensor();
                if(AL_DISPARADO)PORTDbits.RD1 = 1;
                break;
            case 4:
                alarmeSensor();
                if(AL_DISPARADO)PORTDbits.RD2 = 1;
                break;
            case 16: 
                alarmeSensor();
                if(AL_DISPARADO)PORTDbits.RD3 = 1;
                break;
            case 32:
                alarmeSensor();
                if(AL_DISPARADO)PORTDbits.RD4 = 1;
                break;
            case 64:
                alarmeSensor();
                if(AL_DISPARADO)PORTDbits.RD5 = 1;
                break;
            default:
                PORTD = 0;
                break;
        }
        Delay10KTCYx(250);
        cont = cont << 1;
        if(cont == 8) cont = cont << 1;
        if(cont > 64) cont = 0b00000001;        
    }

}
/*******************************************************************
Esta funcao inicializa os resgistradores SFRs.*/
 void Inic_Regs(void){
	TRISA = 0x00;			//PORTA sa�da
	TRISB = 0x03;			//pinos RB0:RB1 entrada e demais pinos do PORTB sa�da
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
 /*******************************************************************
Esta funcao implementa um sensor de alarme com redund�ncia*/
void alarmeSensor(void){
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
//********************************************************************
}