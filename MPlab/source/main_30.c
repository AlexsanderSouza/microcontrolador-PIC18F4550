/*********************************************************************
Nome do arquivo:	main_29.c            
Data:	    		16 de mar�o de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>		//diretiva de compila��o
#include "MCC18.h"
#include "Keyboard_HEX.h"	//dirativa de compila��o
#include <delays.h>			//diretiva de compila��o
//********************************************************************
//defini��es dos leds
#define	led1	PORTDbits.RD7
#define	led2	PORTDbits.RD6
#define	led3	PORTDbits.RD5
#define	led4	PORTDbits.RD4
#define	led5	PORTDbits.RD3
#define	led6	PORTDbits.RD2
#define	led7	PORTDbits.RD1
#define	led8	PORTDbits.RD0
//********************************************************************
//prot�tipos de fun��es
 void Inic_Regs (void);
//********************************************************************
void main(void)										//fun��o main					
{	
    unsigned char i, flag = 0;                         // vari�vel de controle de loop
	char x=0;										//declara��o de vari�vel local
	Inic_Regs ();									//chamada a func�o: configurar SFRs
	while (1)										//loop infinito
	{
		x=GetKey();									//chamada � fun��o. rastrear teclado
		Delay1KTCYx(40);							//delay de 20ms
		if(x=='G')continue;							//finaliza itera��o atual at� que a tecla seja solta
		{
			if (x!='\0')							//uma tecla est� pressionada e ainda n�o  foi tratada?
			{
				if (x=='1')							//tecla S1 pressionada
				{                  
                    for(i=1;i<9;i++)
                    {
                        switch(i)
                        {
                            case 1: 
                                led1 = 0;
                                break;
                            case 2: 
                                led2 = 0;
                                break;
                            case 3: 
                                led3 = 0;
                                break;
                            case 4: 
                                led4 = 0;
                                break;
                            case 5: 
                                led5 = 0;
                                break;
                            case 6: 
                                led6 = 0;
                                break;
                            case 7: 
                                led7 = 0;
                                break;
                            case 8: 
                                led8 = 0;
                                break;
                        }
                            Delay10KTCYx(40);		//delay de 800ms
                            PORTD = 0b11111111;     
                    }
                    /*
					if (led1==0)led1=1;				//led1 emite se bot�o BT1 estiver pressionado
					else	led1=0;					//se n�o, apaga led1
                    Implementa��o de sequ�ncia de LEDs: MSB -> LSB */
                    
				}	
				else    if (x=='2')					//tecla S2 pressionada
				{
					if (led2==0)led2=1;				//led2 emite se bot�o BT2 estiver pressionado
					else	led2=0;					//sen�o acende led2
				}	
				else	if (x=='3')					//tecla S3 pressionada				
				{
					if (led3==0)led3=1;				//led3 emite se bot�o BT3 estiver pressionado
					else	led3=0;					//se n�o, acende led3
				}		
				else	if (x=='4')					//tecla S4 pressionada
				{
					if (led4==0)led4=1;				//led4 emite se bot�o BT4 estiver pressionado
					else	led4=0;					//se n�o, acende led4
				}	
				else	if (x=='5')					//tecla S5 pressionada
				{
					if (led5==0)led5=1;				//led5 emite se bot�o BT5 estiver pressionado
					else	led5=0;					//se n�o, acende led5
				}	
				else	if (x=='6')					//tecla S6 pressionada
				{
					if (led6==0)led6=1;				//led6 emite se bot�o BT6 estiver pressionado
					else	led6=0;					//se n�o, acende led6
				}	
				else	if (x=='7')					//tecla S7 pressionada
				{
					if (led7==0)led7=1;				//led7 emite se bot�o BT7 estiver pressionado
					else	led7=0;					//se n�o, acende led7
				}	
				else	if (x=='8')					//tecla S8 pressionada
				{
					if (led8==0)led8=1;				//led8 emite se bot�o BT8 estiver pressionado
					else	led8=0;					//se n�o, acende led8
				}	
			}
		}
	}
}
/*******************************************************************
Esta funcao inicializa os resgistradores SFRs.*/
 void Inic_Regs (void)
{
	TRISA = 0x00;			//PORTA saida
	TRISB = 0x00;			//PORTB saida
	TRISC = 0x00;			//PORTC saida
	TRISD = 0x00;			//PORTD saida
	TRISE = 0x00;			//PORTE saida
	ADCON1 = 0x0F;			//configura pinos dos PORTA e PORTE como digitais
	PORTA = 0;				//limpa PORTA
	PORTB = 0;				//limpa PORTB
	PORTC = 0;				//limpa PORTC
	PORTD = 0xFF;			//apaga leds
	PORTE = 0;				//limpa PORTE
//********************************************************************
}
