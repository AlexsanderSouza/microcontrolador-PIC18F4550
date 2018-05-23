/*********************************************************************
Nome do arquivo:	main_33.c            
Data:	    		25 abril de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>								//diretiva de compila��o
#include <delays.h>									//diretiva de compila��o
#include "DSP_7Seg_x4.h"							//diretiva de compila��o
//********************************************************************
//prot�tipos de fun��es
void Inic_Regs (void);
void high_isr (void);
//********************************************************************
//vari�veis globais
volatile unsigned char Dsp1=0;						//declara��o  de vari�vel local inicializada
volatile unsigned char Dsp2=0;						//declara��o  de vari�vel local inicializada
volatile unsigned char Dsp3=0;						//declara��o  de vari�vel local inicializada
volatile unsigned char Dsp4=0;						//declara��o  de vari�vel local inicializada
//********************************************************************/
#pragma code high_vector=0x08						//vetor de interrup��o de alta prioridade
void interrupt_at_high_vector(void)
{
	_asm GOTO high_isr _endasm						//desvia programa para rotina de tratamento da interrup��o
}
#pragma code 
//*****************************
//Rotina de tratamento de interrup��o
#pragma interrupt high_isr 
void high_isr (void)
{
	if(!INTCONbits.INT0IF);							//interrup��o externa?
	else
	{
		INTCONbits.INT0IF = 0;						//sim, limpa bit de sinaliza��o
		Dsp1+=1;									//incrementa unidade
		if(Dsp1==10)								//unidade estourou?
		{
			Dsp1=0;									//sim, zera unidade
			Dsp2+=1;								//incrementa dezena
		}
		if(Dsp2==10)								//dezena estourou?
		{
			Dsp2=0;									//sim,zera dezena
			Dsp3+=1;								//incrementa centena
		}
		if(Dsp3==10)								//centena estourou?
		{
			Dsp3=0;									//sim, zera centena
			Dsp4+=1;								//incrementa unidade de milhar
		}
		if(Dsp4==10)								//unidade de milhar estourou?
		{
			Dsp4=Dsp3=Dsp2=Dsp1=0;					//sim, zera contador
		}
	}
}
//********************************************************************/
void main(void)										//fun��o main					
{	
//**********************************
	Inic_Regs ();									//configurar SFRs
	while(1)										//loop infinito
	{
		Aciona_DPS_7_seg (Dsp4, Dsp3, Dsp2, Dsp1);  //chamada � fun��o: atualizar display
		Delay1KTCYx(8);								//delay de 4ms
	}
}
/*******************************************************************
Esta funcao inicializa os registradores SFRs.*/
 void Inic_Regs (void)
{
	TRISA = 0x00;									//PORTA sa�da
	TRISB = 0x01;									//RB0 como entrada e demais pinnos do PORTB como sa�da
	TRISC = 0x00;									//PORTC sa�da
	TRISD = 0x00;									//PORTD sa�da
	TRISE = 0x00;									//PORTE sa�da
	ADCON1 = 0x0F;									//configura pinos dos PORTA e PORTE como digitais
	PORTA = 0;										//limpa PORTA
	PORTB = 0;										//limpa PORTB
	PORTC = 0;										//limpa PORTC
	PORTD = 0x00;									//apaga displays
	PORTE = 0;										//limpa PORTE
//*****************************************
//habilita interrup��o externa
	INTCONbits.GIE = 1;								//liga chave geral de interrup��o
	INTCONbits.INT0IE = 1;							//liga chave individual de interrup��o externa 0
	INTCON2bits.INTEDG0 = 0;						//interrup��o externa 0 ocorrer� na borda de descida
//********************************************************************
}

