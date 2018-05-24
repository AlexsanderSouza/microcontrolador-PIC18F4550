/*********************************************************************
Nome do arquivo:	main_39.c            
Data:	    		17 de maio de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>		//diretiva de compila��o
#include "Lcd_8bits.h"		//diretiva de compila��o
//********************************************************************
//prot�tipos de fun��es
void Inic_Regs (void);
void Atual_LCD (char dado);
void Configura_UART (void);
void Transmite_UART (char dado);
//********************************************************************
//vari�veis globais
char count=0;
//********************************************************************
void main(void)							//fun��o main					
{	
float x=0;								//declara��o  de vari�vel local inicializada
int dly=0;								//declara��o  de vari�vel local inicializada
char DADO;								//declara��o  de vari�vel local inicializada
//**********************************
	Inic_Regs ();						//configurar SFRs
//**********************************
	IniciaLCD (2);						//inicializar LCD controller HD44780
	TestPixelsLCD();					//teste no LCD - acende todos os pixels.

	EscInstLCD(0x0C);					//desativa cursor
	while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
//**********************************
//delay de 3 segundos
	for(dly=0;dly<600;dly++)			//comando de itera��o
	{
		_Delay5ms();					//delay de 5ms
	}
//**********************************
	EscInstLCD(0x01);					//desativa cursor
	while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
//**********************************/
	Configura_UART();					//configura UART com taxa de 2400bps
//**********************************/
//rotina principal
	while(1)
	{
		while(!PIR1bits.RCIF);				//aguarda chegar um novo byte
		if (RCSTAbits.FERR)					//houve erro de transmiss�o?
		{
			RCSTAbits.CREN = 0;				//sim, desabilita recep��o
			RCSTAbits.CREN = 1;				//habilita recep��o
		}
		else								//n�o houve erro de transmiss�o, transmite dado recebido
		{
			DADO = RCREG;					//obt�m caractere
			Transmite_UART (DADO);			//transmite DADO
			Atual_LCD(DADO);				//atualiza LCD
		}
	}
}//******************************************************************
//							fun��es
//*******************************************************************
/*Esta funcao inicializa os resgistradores SFRs.*/
 void Inic_Regs (void)
{
	TRISA = 0x00;						//PORTA sa�da
	TRISB = 0x00;						//PORTB sa�da
	TRISC = 0x00;						//PORTC sa�da
	TRISD = 0x00;						//PORTD sa�da
	TRISE = 0x00;						//PORTE sa�da
	ADCON1 = 0x0F;						//configura pinos dos PORTA e PORTE como digitais
	PORTA = 0;							//limpa PORTA
	PORTB = 0;							//limpa PORTB
	PORTC = 0;							//limpa PORTC
	PORTD = 0x00;						//apaga displays
	PORTE = 0;							//limpa PORTE
}//********************************************************************
//inicializa USART
void Configura_UART (void)
{
	TRISCbits.TRISC7 = 1;			//configura pino RX como entrada
	TRISCbits.TRISC6 = 1;			//configura pino TX como entrada
	TXSTA = 0b00100100;				//transmiss�o habilitada<5>
									//transmiss�o ass�ncrona<4>
									//transmiss�o em alta velocidade<2>
	RCSTA = 0b10010000;				//porta serial habilitada<7>
									//recep��o cont�nua habilitada<4>
	BAUDCON = 0b00000000; 			//TX ocioso em n�vel alto<4>
									//gerador de baud rate de 8 bits<3>
	SPBRG = 207;					//2400bps
}//*********************************
//transmite o caractere
void Transmite_UART (char dado)
{
	TXREG = dado;					//inicia a transmiss�o
	while(TXSTAbits.TRMT);			//aguarda transmiss�o terminar
}//***************************************************************************
//fun��o  que  atualiza o LCD. 
void Atual_LCD (char dado)
{
	if(count==16)							//se cursor chegou no final da primeira linha
	{
		EscInstLCD(0xC0);					//move cursor para a primeira posi��o da segunda linha
		while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
	}
	else if(count==32)						//se cursor chegou no final da segunda linha		
	{
		EscInstLCD(0x01);					//limpa display e mostra cursor piscando na primeira posi��o da primmeira linha
		while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
	}
	EscDataLCD(dado);						//escreve caractere no LCD na posi��o apontada pelo cursor	
	while(TesteBusyFlag());					//espera LCD controller terminar de executar instru��o
	count+=1;								//incrementa count
//*******************************************************************
}
