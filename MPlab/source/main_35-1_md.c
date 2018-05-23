/*********************************************************************
Nome do arquivo:	main_35.c            
Data:	    		19 Maio de 2018          
Versao:				1.1                              
MPLAB IDE:			MPLAB-X v.4.15 
Autor:				Wagner Zanco
Modificado por:     Carl�cio Silva     
Descri��o: Configura��o do conversor A/D para operar com clock de 4 MHz,
com VREF- igual a GND/VSS, VREF+ igual a VCC, no modo "Autom�tico de
Convers�o",  
*********************************************************************/

/**** Arquivos de cabe�alho ****/
#include <p18f4550.h>		//diretiva de compila��o
#include "MCC18_18F4550.h"  //diretiva de compila��o
#include <delays.h>			//diretiva de compila��o
#include <stdio.h>			//diretiva de compila��o
#include "Lcd_8bits.h"		//diretiva de compila��o


/**** Prot�tipos de fun��es ****/
void configSFR(void);
void configAD(void);
int convAD(void);
char *convFloatString(float);

/**** Vari�veis globais ****/
char buf [17];


/**** Defini��es ****/
#define	AJUSTA_DECIMAL	10	//precis�o de uma casa decimal


void main(void) //fun��o main					
{	
    //Vari�veis locais
    float x=0;				
    int dly=0;

/****** Configura��o dos SFRs *******/    
	configSFR();						
    
/******* Inicializa��o do LCD *******/ 
	IniciaLCD(2);						//inicializar LCD controller HD44780
	TestPixelsLCD();					//teste no LCD - acende todos os pixels.
	EscInstLCD(0x0C);					//desativa cursor
	while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
/***********************************/
    
//delay de 3 segundos
	for(dly=0;dly<600;dly++)			//comando de itera��o
	{
		_Delay5ms();					//delay de 5ms
	}
//**********************************/
configAD();

    EscInstLCD(0x01);           //limpa display e mostra cursor piscando na primeira linha
    while(TesteBusyFlag());		//espera LCD controller terminar de executar instru��o
    sprintf(buf,"TEMPERATURA"); //armazena string no vetor buf
    EscStringLCD(buf);			//escreve string no LCD
    while(TesteBusyFlag());		//espera LCD controller terminar de executar instru��o

//Rotina principal
	while (1)
	{
        
        x = (float)(convAD()/2.048); //Faz a convers�o A/D
		Delay1KTCYx(20);			 //delay de 20ms        
        convFloatString(x);         //Converte o valor da Temperatura para string
                                    //e salva o resultado em buf[]        
        EscInstLCD(0xC0);           //Posiciona o cursor na segunda linha do LCD
        while(TesteBusyFlag());     //Espera LCD controller terminar de executar instru��o
        EscStringLCD(buf);			//Escreve string no LCD
        while(TesteBusyFlag());		//Espera LCD controller terminar de executar instru��o    
        Delay10KTCYx(40);
	}
}

/*******************************************************************************
Esta fun��o inicializa os registradores SFRs.*/
 void configSFR(void)
{
	TRISA = 0x01;		//RA0 como entrada e os demais de PORTA como sa�da
	TRISB = 0x00;		//PORTB sa�da
	TRISC = 0x00;		//PORTC sa�da
	TRISD = 0x00;		//PORTD sa�da
	TRISE = 0x00;		//PORTE sa�da
	ADCON1 = 0x0F;		//configura pinos dos PORTA e PORTE como digitais
	PORTA = 0;			//limpa PORTA
	PORTB = 0;			//limpa PORTB
	PORTC = 0;			//limpa PORTC
	PORTD = 0;  		//limpa PORTC
	PORTE = 0;			//limpa PORTE  
}
 
/*******************************************************************************
Esta fun��o configura o conversor A/D.*/ 
void configAD(void)
{
	ADCON0=0b00000001;					/*canal AN0 selecionado<5:2>
										M�dulo conversor ligado<1>*/
	ADCON1=0b00001110;					/*Vref- = VSS<5>
										Vref+ = VDD<4>
										pino RA0/AN0 anal�gico e demais pinos digitais<3:0>*/
	ADCON2=0b10101100;					/*resultado justificado � direita<7>
										Tempo de aquisi��o de 12TAD<5:3>
										TAD = 1�s<2:0>*/
}

/*******************************************************************************
Esta fun��o efetua uma ocnvers�o A/D.*/
int convAD(void)
{
int Result_AD;							//declara��o de vari�vel local
	ADCON0bits.GO = 1;					//inicia convers�o
	while (ADCON0bits.GO);				//aguarda finalizar convers�o
	Result_AD = (((int)ADRESH)<<8)|(ADRESL);	//obt�m valor da convers�o 
	return Result_AD;					//retorna valor da convers�o
}

/********************************************************************/
/*Convers�o de float para ASCII. Esta fun��o converte valores float 
na faixa de -65535.998 a +65535.998 em uma string. 
//*******************************************************************/
char *convFloatString(float inputFloat)
{
    unsigned int parte_inteira;				//declara��o de vari�vel local
    unsigned int parte_decimal;				//declara��o de vari�vel local
    char sinal, *pt;						//declara��o de vari�vel local
    unsigned char x, y;						//declara��o de vari�vel local
    unsigned char z = 0xB2;

//*******************************************************************
	if(inputFloat < 0)					//valor � menor que 0?
	{
		sinal = '-';					//sim, sinal negativo
		inputFloat = inputFloat * (-1);		//inverte o sinal de float_in
	}
	else sinal = '+';					//n�o, sinal positivo
    
//*******************************************************************
	parte_inteira = inputFloat;			//resgata parte inteira do valor
    
//*******************************************************************
	parte_decimal =(unsigned int)((inputFloat - parte_inteira) * AJUSTA_DECIMAL);	//resgata parte fracion�ria do valor
	sprintf(buf," Temp = %c%u.%01u *C",sinal,parte_inteira,parte_decimal);		//converte valor em string e armazena no vetor buf	
	pt = buf;							//passa para o ponteiro pt o endere�o de buf
	return (pt);						//retorna o endere�o de buf.
}


