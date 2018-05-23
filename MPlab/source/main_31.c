/*********************************************************************
Nome do arquivo:	main_31.c            
Data:	    		29 de mar�o de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>		//diretiva de compila��o
#include "DSP_7Seg_x4.h"	//diretiva de compila��o
#include <delays.h>			//diretiva de compila��o
//********************************************************************
//prot�tipos de fun��es
 void Inic_Regs (void);
//********************************************************************
void main(void)										//fun��o main					
{	
unsigned char Dsp1=0;								//declara��o  de vari�vel local inicializada
unsigned char Dsp2=0;								//declara��o  de vari�vel local inicializada
unsigned char Dsp3=0;								//declara��o  de vari�vel local inicializada
unsigned char Dsp4=0;								//declara��o  de vari�vel local inicializada
unsigned char x=0;
	Inic_Regs ();									//chamada a func�o: configurar SFRs
	while(1)										//loop infinito
	{
		Aciona_DPS_7_seg (Dsp4, Dsp3, Dsp2, Dsp1);	//chamada � fun��o: atualizar display
		Delay1KTCYx(8);								//delay de 4ms
		if(!(x==250))x++;							//se x diferente de 250, incrementa x
		else 										//sen�o, incrementa contador
		{
			x=0;									//x=0
			Dsp1+=1;								//incrementa unidade
			if(Dsp1==10)							//unidade estourou?
			{
				Dsp1=0;								//sim, zera unidade
				Dsp2+=1;							//incrementa dezena
			}
			if(Dsp2==10)							//dezena estourou?
			{
				Dsp2=0;								//sim, zera dezena
				Dsp3+=1;							//incrementa centena
			}
			if(Dsp3==10)							//centena estourou?
			{
				Dsp3=0;								//sim, zera centena
				Dsp4+=1;							//incrementa unidade de milhar
			}
			if(Dsp4==10)							//unidade de milhar estourou?
			{
				Dsp4=Dsp3=Dsp2=Dsp1=0;				//sim, zera contador
			}
		}
	}
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
