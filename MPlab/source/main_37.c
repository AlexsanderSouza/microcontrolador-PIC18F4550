/*********************************************************************
Nome do arquivo:	main_37.c            
Data:	    		17 de maio de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:			Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>		//diretiva de compila��o
#include "MCC18.h"
#include <delays.h>			//diretiva de compila��o
#include <stdio.h>			//diretiva de compila��o
#include "Lcd_8bits.h"		//diretiva de compila��o
#include "I2C_Master.h"		//diretiva de compila��o
//********************************************************************
//prot�tipos de fun��es
void Inic_Regs (void);
void Atual_LCD (void);
void Master_I2C (void);
char  ESCRITA_24C08  (unsigned char ENDH, unsigned char ENDL, char DADO);
char LEITURA_24C08 (unsigned char _ENDH, unsigned char _ENDL);
char Detecta_fim_escrita(void);
//********************************************************************
//vari�veis globais
char buf [17];
unsigned char ENDH=0b01010000;
unsigned char ENDL=0;
char DADO='A';
unsigned char TEMP;
//********************************************************************
//defini��es
#define Botao1			PORTBbits.RB0
//********************************************************************
void main(void)							//fun��o main					
{	
float temp=0;							//declara��o  de vari�vel local inicializada
int dly=0;								//declara��o  de vari�vel local inicializada
char status_botao=0;					//declara��o  de vari�vel local inicializada
//**********************************
	Inic_Regs ();						//configurar SFRs
	Master_I2C ();						//configura Mestre I2C
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
//rotina principal
	ESCRITA_24C08(ENDH, ENDL, DADO);						//escreve dado na EEPROM
	while(Detecta_fim_escrita()==-1)Detecta_fim_escrita ();	//aguarda final da escrita na EEPROM
	DADO=LEITURA_24C08 (ENDH, ENDL);						//l� EEPROM
	Atual_LCD();											//atualiza LCD
	while (1)												//loop infinito
	{
		if(!Botao1) 										//Bot�o 1 pressionado?
		{													//sim, executa bloco de c�digo
			if(!status_botao)								//Bot�o 1 foi tratado?
			{												//n�o, executa bloco de c�digo
				status_botao=1;								//sinaliza que Bot�o foi tratado
				if(DADO=='Z')DADO='A';						//reinicializa DADO se atingiu o valor final
				else DADO+=1;								//atualiza DADO
				
				ESCRITA_24C08(ENDH, ENDL, DADO);						//escreve dado na EEPROM
				while(Detecta_fim_escrita()==-1)Detecta_fim_escrita ();	//aguarda finalizar ciclo de escrita na EEPROM
				DADO=LEITURA_24C08 (ENDH, ENDL);						//l� EEPROM
				ENDL+=1;												//incrementa endere�o baixo
				Atual_LCD();											//atualiza LCD
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
	TRISA = 0x00;						//PORTA sa�da
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
//configura o microcontrolador como mestre com bit rate de 100kb.
void Master_I2C (void)
{
	TRISC = ((TRISC * 0b11100111) | 0b00011000 );	//configura pinos SDA e SCL como entrada
	SSPCON1 = 0b00101000;				//configura dispositivo como mestre
										//Habilita porta serial e ativa pinos SDA E SCL <5>
										//ativa modo mestre <3:0>
	SSPADD = 19;						//bit rate de 100kbps a Fosc = 8MHz
	SSPSTAT = 0b10000000;				//controle de inclina��o desativado <7>
										//n�veis de entrada conforme especifica��o I2C <6>
}//*********************************************************************
/*fun��o  que  atualiza o LCD. Ser� mostrado no LCD o endere�o e
o conte�do armazenado no endere�o*/
void Atual_LCD (void)
{
int END;									//declara��o de vari�vel local
//*************************
	END = ENDH & 3;
	END = END << 8;
	END += ENDL;							//obtem endere�o					  
//*************************
	EscInstLCD(0x01);						//limpa display e mostra cursor piscando na primeira posi��o da primmeira linha
	while(TesteBusyFlag());					//espera LCD controller terminar de executar instru��o
	if(DADO==-1)							//houve erro de comunica��o?
	{
		sprintf(buf,"Erro na transmiss�o");	//sim, converte valor em string e armazena no vetor buf	
		EscStringLCD(buf);					//escreve string no LCD
		while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
	}
	else 									//n�o houve erro de comunica��o
	{
		sprintf(buf,"End: %#xh",END);		//converte valor em string e armazena no vetor buf	
		EscStringLCD(buf);					//escreve string no LCD
		while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o

		EscInstLCD(0xC0);					//posiciona cursor na primeira posi��o da segunda linha
		while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o

		sprintf(buf,"Dado: %c",DADO);		//converte valor em string e armazena no vetor buf	
		EscStringLCD(buf);					//escreve string no LCD
		while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
	}
}//*******************************************************************
/*fun��o que escreve o valor no endere�o de mem�ria recebido  como par�metro
o valor escrito � retornado. Caso ocorra um erro na transmiss�o � retornado o valor -1.*/
char  ESCRITA_24C08  (unsigned char ENDH, unsigned char ENDL, char DADO)
{
char x;									//declara��o de vari�vel local 
	x = I2C_LIVRE ();					//chamada � fun��o com retorno de valor. Verifica se barramento est� livre
	if (x == 0)							//se barramento ocupado, aborta transmiss�o e retorna
	{
		I2C_STOP();						//gera bit STOP
		return -1;						//erro na transmiss�o
	}
	else 								//barramento livre
	{
		I2C_START();					//barramento livre, gera condi��o START
		TEMP= ENDH << 1;				//rotaciona END_I2C para a esquerda (insere bit R_W para escrita) 
		I2C_TRANSMITE(TEMP);			//transmite endere�o alto
		if (!I2C_TESTA_ACK())	 		//se erro na transmiss�o, aborta transmiss�o
		{
			I2C_STOP();					//gera bit STOP
			return -1;					//erro na transmiss�o
 		}
		I2C_TRANSMITE(ENDL);			//transmite endere�o baixo
		if (!I2C_TESTA_ACK())			//se erro na transmiss�o, aborta transmiss�o
		{
			I2C_STOP();					//gera bit STOP
			return -1;					//erro na transmiss�o
		}
		I2C_TRANSMITE(DADO);			//transmite dado
		if (!I2C_TESTA_ACK())	 		//se erro na transmiss�o, aborta transmiss�o
		{
			I2C_STOP();					//gera bit STOP
			return -1;					//erro na transmiss�o
 		}
		I2C_STOP();						//gera bit STOP
		return DADO;					//transmiss�o feita com sucesso
	}
}//*********************************************************************
/*fun��o que l� o valor no endere�o de mem�ria recebido  como par�metro.
o valor lido � retornado. Caso ocorra um erro na transmiss�o � retornado o valor -1.*/
char LEITURA_24C08 (unsigned char _ENDH, unsigned char _ENDL)
{
	char x;								//declara��o de vari�vel local 
	unsigned char DADO_I2C;				//declara��o de vari�vel local 
	x = I2C_LIVRE ();					//chamada � fun��o com retorno de valor. Verifica se barramento est� livre
	if (x == 0)							//se barramento ocupado, aborta transmiss�o e retorna
	{
		I2C_STOP();						//gera bit STOP
		return -1;						//erro na transmiss�o
	}
	else 								//barramento livre
	{
		I2C_START();					//barramento livre, gera condi��o START
		TEMP = _ENDH << 1;				//rotaciona END_I2C para a esquerda 
		I2C_TRANSMITE(TEMP);			//transmite endere�o
		if (!I2C_TESTA_ACK()) 			//se erro na transmiss�o, aborta transmiss�o
		{
			I2C_STOP();					//gera bit STOP
			return -1;					//erro na transmiss�o
 		}
		I2C_TRANSMITE(_ENDL);			//transmite endere�o baixo
		if (!I2C_TESTA_ACK())			//se erro na transmiss�o, aborta transmiss�o
		{
			I2C_STOP();					//gera bit STOP
			return -1;					//erro na transmiss�o
		}
		I2C_RESTART();
		TEMP |= 0b00000001;				//insere bit R_W para leitura
		I2C_TRANSMITE(TEMP);			//transmite endere�o
		if (!I2C_TESTA_ACK()) 			//se erro na transmiss�o, aborta transmiss�o
		{
			I2C_STOP();					//gera bit STOP
			return -1;					//erro na transmiss�o
 		}
		DADO_I2C = I2C_RECEBE();		//recebe dado
		I2C_NACK();						//gera bit NACK
		I2C_STOP();						//gera bit STOP
		return DADO_I2C;				//transmiss�o feita com sucesso
	}
}//*********************************************************************
/*esta fun��o detecta se o ciclo de escrita na EEPROM terminou.Caso a 
escrita tenha terminado ela retornar� 0, caso contrario retornar� -1*/
char Detecta_fim_escrita (void)
{
	char x;								//declara��o de vari�vel local 
	unsigned char DADO_I2C;				//declara��o de vari�vel local 
	x = I2C_LIVRE ();					//chamada � fun��o com retorno de valor. Verifica se barramento est� livre
	if (x == 0)							//se barramento ocupado, aborta transmiss�o e retorna
	{
		I2C_STOP();						//gera bit STOP
		return -1;						//barramento ocupado
	}
	else 								//barramento livre
	{
		I2C_START();					//barramento livre, gera condi��o START
		TEMP = ENDH << 1;				//rotaciona END_I2C para a esquerda 
		I2C_TRANSMITE(TEMP);			//transmite endere�o
		if (!I2C_TESTA_ACK()) 			//se erro na transmiss�o, aborta transmiss�o
		{
			I2C_STOP();					//gera bit STOP
			return -1;					//ciclode esrita n�o terminou
 		}
		return 0;						//ciclo de escrita terminou
	}
//***********************************************************************
}