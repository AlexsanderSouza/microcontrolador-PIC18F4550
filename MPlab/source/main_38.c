/*********************************************************************
Nome do arquivo:	main_38.c            
Data:	    		17 de maio de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>		//diretiva de compila��o
#include <delays.h>			//diretiva de compila��o
#include <stdio.h>			//diretiva de compila��o
#include "Lcd_8bits.h"		//diretiva de compila��o
//********************************************************************
//prot�tipos de fun��es
void Inic_Regs (void);
void Atual_LCD (void);
void Configura_AD	(void);
int Conv_AD	(void);
char *Conv_Float_String(float float_in);
char Detecta_fim_escrita(void);
void configura_SPI (void);
void Transmite_Comando_SPI (unsigned char Comand, unsigned char dado);
//********************************************************************
//vari�veis globais
char buf [17];							//declara��o de vetor
char buf2 [17];							//declara��o de vetor
float temp=0;							//declara��o  de vari�vel inicializada
unsigned char Pos_cursor=0;				//declara��o  de vari�vel inicializada
//********************************************************************
//defini��es
#define	AJUSTA_DECIMAL	10				//precis�o de uma casa decimal
#define Botao1	PORTBbits.RB0			//define Botao 1
#define _SS		PORTCbits.RC1			//define linha chip select	
//********************************************************************
void main(void)							//fun��o main					
{	
float x=0;								//declara��o  de vari�vel local inicializada
int dly=0;								//declara��o  de vari�vel local inicializada
char status_botao=0;					//declara��o  de vari�vel local inicializada
unsigned char Comando=0x11;				//declara��o  de vari�vel local inicializada
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
	configura_SPI();					//configura interface SPI como mestre
	Configura_AD();						//configura conversor A/D
//**********************************
	Transmite_Comando_SPI (Comando, Pos_cursor);						
	temp = (float)(Conv_AD()*4.88/1000);//chamada � fun��o com retorno de valor
	Conv_Float_String(temp);			//chamada � fun��o
	Atual_LCD();						//atualiza LCD
	Pos_cursor +=25;					//atualiza posi��o do cursor
//**********************************/
//rotina principal
	while (1)										//loop infinito
	{
		if(!Botao1) 								//Bot�o 1 pressionado?
		{											//sim, executa bloco de c�digo
			if(!status_botao)						//Bot�o 1 foi tratado?
			{										//n�o, executa bloco de c�digo
				status_botao=1;						//sinaliza que Bot�o foi tratado
				Transmite_Comando_SPI (Comando, Pos_cursor);	//chamada � fun��o. Atualiza posi��o do cursor						
				temp = (float)((Conv_AD()*4.88/1000));		//temp recebe o valor convertido pelo conversor A/D
				Conv_Float_String(temp);			//chamada � fun��o
				Atual_LCD();						//atualiza LCD
				if(Pos_cursor==250)Pos_cursor=0;	//Se cursor chegou a posi��o 250retorna a posi��o 0
				else Pos_cursor +=25;				//n�o, incrementa cursor 10 posi��es
			}
		} 
		else status_botao=0;						//sinaliza que Bot�o foi tratado
		Delay1KTCYx(100);							//delay de 20ms
	}
}//********************************************************************
//							fun��es
//*******************************************************************
/*Esta funcao inicializa os resgistradores SFRs.*/
 void Inic_Regs (void)
{
	TRISA = 0x01;						//RA0 como entrada e demais pinos do PORTA como sa�da
	TRISB = 0x01;						//RB0 como entrada e demais pinos do PORTB como sa�da
	TRISC = 0x00;						//PORTC sa�da
	TRISD = 0x00;						//PORTD sa�da
	TRISE = 0x00;						//PORTE sa�da
	ADCON1 = 0x0F;						//configura pinos dos PORTA e PORTE como digitais
	PORTA = 0;							//limpa PORTA
	PORTB = 0;							//limpa PORTB
	PORTC = 0;							//limpa PORTC
	PORTD = 0x00;						//apaga displays
	PORTE = 0;							//limpa PORTE
}
//********************************************************************
//esta fun��o configura o conversor A/D
void Configura_AD	(void)
{
	ADCON0=0b00000001;					/*canal AN0 selecionado<5:2>
										M�dulo conversor ligado<1>*/
	ADCON1=0b00001110;					/*Vref- = VSS<5>
										Vref+ = VDD<4>
										pino RA0/AN0 anal�gico e demais pinos digitais<3:0>*/
	ADCON2=0b10101001;					/*resultado justificado � direita<7>
										Tempo de aquisi��o de 12TAD<5:3>
										TAD = 1�s<2:0>*/
}//********************************************************************
//esta fun��o efetua uma convers�o A/D
int Conv_AD (void)
{
int Result_AD;									//declara��o de vari�vel local
	ADCON0bits.GO = 1;							//inicia convers�o
	while (ADCON0bits.GO);						//aguarda finalizar convers�o
	Result_AD = (((int)ADRESH)<<8)|(ADRESL);	//obt�m valor da convers�o 
	return Result_AD;							//retorna valor da convers�o
}//********************************************************************
/********************************************************************/
/*Convers�o de float para ASCII. Esta fun��o converte valores float 
na faixa de -65535.998 a +65535.998 em uma string. 
//*******************************************************************/
char *Conv_Float_String(float float_in)
{
unsigned int parte_inteira;				//declara��o de vari�vel local
unsigned int parte_decimal;				//declara��o de vari�vel local
char sinal, *pt;						//declara��o de vari�vel local
unsigned char x, y;						//declara��o de vari�vel local
unsigned char z = 0xB2;

//*******************************************************************
	if(float_in < 0)					//valor � menor que 0?
	{
		sinal = '-';					//sim, sinal negativo
		float_in = float_in * (-1);		//inverte o sinal de float_in
	}
	else sinal = ' ';					//n�o, sinal positivo
//*******************************************************************
	parte_inteira = float_in;			//resgata parte inteira do valor
//*******************************************************************
	parte_decimal =(unsigned int)((float_in - parte_inteira) * AJUSTA_DECIMAL);	//resgata parte fracion�ria do valor
	sprintf(buf," Tensao: %c%u.%01uV",sinal,parte_inteira,parte_decimal);		//converte valor em string e armazena no vetor buf	
	pt = buf;							//passa para o ponteiro pt o endere�o de buf
	return (pt);						//retorna o endere�o de buf.
}//******************************************************************

//********************************************************************
//Configura��o do modulo SPI  como mestre com taxa de 125kbps
void  configura_SPI  (void)
{
	TRISCbits.TRISC5 = 0;				//configura SDO como sa�da
	TRISCbits.TRISC4 = 1;				//configura SDI como entrada
	TRISCbits.TRISC3 = 0;				//configura SCK como sa�da
	TRISCbits.TRISC1 = 0;				//configura linha _SS como sa�da
	_SS = 1;							//desabilita chip select
	SSPCON1 =  0b00100010;				/*habilita m�dulo SPI <5> 										
										bit rate 125kbps (Fosc/64)<3:0> 
										clock ocioso em n�vel baixo<4>*/						
	SSPSTAT = 0b11000000;				/*dado de entrada � amostrado no fim do time bit do dado de sa�da<7>
										transmiss�o ocorre do estado ocioso para o estado ativo do clock <6>*/
}//*********************************************************************
/*fun��o  que  atualiza o LCD. Ser� mostrado no LCD o c�digo e
a tens�o entre o cursor e o terra do DPOT.*/
void Atual_LCD (void)
{

	EscInstLCD(0x01);					//limpa display e mostra cursor piscando na primeira posi��o da primmeira linha
	while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o

		sprintf(buf2,"Codigo: %u",Pos_cursor);	//converte valor em string e armazena no vetor buf	
		EscStringLCD(buf2);						//escreve string no LCD
		while(TesteBusyFlag());					//espera LCD controller terminar de executar instru��o


		EscInstLCD(0xC0);				//posiciona cursor na primeira posi��o da segunda linha
		while(TesteBusyFlag());			//espera LCD controller terminar de executar instru��o

		EscStringLCD(buf);				//escreve string no LCD
		while(TesteBusyFlag());			//espera LCD controller terminar de executar instru��o
}//*******************************************************************
//transmite e recebe um byte de dados  
unsigned char  Transmite_SPI  (unsigned char dado)
{
	SSPBUF = dado;						//inicia transmiss�o	
	while(!SSPSTATbits.BF);				//aguarde byte chegar
	dado = SSPBUF; 						//leitura burra
	return dado;						//retorna o dado recebido
}//*********************************************************************
//transmite comando para o MCP41010
void Transmite_Comando_SPI (unsigned char Comand, unsigned char dado)
{
	_SS = 0;							//habilita chip select
	Transmite_SPI (Comand);				//transmite comando
	Transmite_SPI (dado);				//transmite dado	
	_SS = 1;							//desabilita chip select
//*********************************************************************
}
