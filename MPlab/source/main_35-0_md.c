/*********************************************************************
Nome do arquivo:	main_35.c            
Data:	    		17 de maio de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4550.h>		//diretiva de compila��o
#include "MCC18_18F4550.h"  //diretiva de compila��o
#include <delays.h>			//diretiva de compila��o
#include <stdio.h>			//diretiva de compila��o
#include "Lcd_8bits.h"		//diretiva de compila��o
//********************************************************************
//prot�tipos de fun��es
void Inic_Regs (void);
void Configura_AD	(void);
int Conv_AD	(void);
void Atual_LCD (void);
char *Conv_Float_String(float float_in);
void Confg_PWM (void);
void Config_Duty_Cycle (int x);
//********************************************************************
//vari�veis globais
char buf [17];
int z = 0;
float temp1=0;
//********************************************************************
//defini��es
#define	AJUSTA_DECIMAL	10				//precis�o de uma casa decimal
#define Botao1			PORTBbits.RB0
#define Resistencia		PORTCbits.RC1
//********************************************************************
void main(void)							//fun��o main					
{	
float x=0;								//declara��o  de vari�vel local inicializada
                           //declara��o  de vari�vel local inicializada
float tempLocal=0;
char y=0;								//declara��o  de vari�vel local inicializada
char i=0;								//declara��o  de vari�vel local inicializada
//float temp=0;							//declara��o  de vari�vel local inicializada
int dly=0;
//**********************************
	Inic_Regs ();						//configurar SFRs
//*
	IniciaLCD (2);						//inicializar LCD controller HD44780
	TestPixelsLCD();					//teste no LCD - acende todos os pixels.
	EscInstLCD(0x0C);								//desativa cursor
	while(TesteBusyFlag());							//espera LCD controller terminar de executar instru��o
//**********************************
//delay de 3 segundos
	for(dly=0;dly<600;dly++)			//comando de itera��o
	{
		_Delay5ms();					//delay de 5ms
	}
//**********************************/
Configura_AD();
//**********************************
//rotina principal
	while (1)
	{
		for(i=0;i<=49;i++)				//la�o de itera��o
		{
			if(!Botao1) Resistencia =1;	//liga a resist�ncia se o bot�o estiver pressionado
			else Resistencia =0;		//sen�o, desliga resist�ncia
			x = (float)((Conv_AD()*25)-2050);	//chamada � fun��o com retorno de valor
			temp1 += x;					//obt�m temperatura medida
			Delay1KTCYx(40);			//delay de 20ms
		}
        tempLocal = temp1/50;
		Conv_Float_String(tempLocal);		//chamada � fun��o
        if((tempLocal > 36.0)&&(z==0)) Confg_PWM();
        if((tempLocal > 36.0)&&(tempLocal < 40.0)) {z = 1; Config_Duty_Cycle (33);}
        if((tempLocal > 39.0)&&(tempLocal < 42.0)) {z = 2; Config_Duty_Cycle (66);}
        if((tempLocal > 41.0)&&(tempLocal < 45.0)) {z = 3; Config_Duty_Cycle (100);}
		Atual_LCD ();		    //chamada � fun��o
		temp1=0;							//temp = 0
	}
}
//*******************************************************************
/*Esta funcao inicializa os resgistradores SFRs.*/
 void Inic_Regs (void)
{
	TRISA = 0x01;						//PORTA sa�da
	TRISB = 0x00;						//PORTB sa�da
	TRISC = 0x01;						//PORTC sa�da
	TRISD = 0x00;						//PORTD sa�da
	TRISE = 0x00;						//PORTE sa�da
	ADCON1 = 0x0F;						//configura pinos dos PORTA e PORTE como digitais
	PORTA = 0;							//limpa PORTA
	PORTB = 0;							//limpa PORTB
	PORTC = 0;							//limpa PORTC
	PORTD = 0x00;						//apaga displays
	PORTE = 0;							//limpa PORTE
}//********************************************************************
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
//esta fun��o efetua uma ocnvers�o A/D
int Conv_AD (void)
{
int Result_AD;							//declara��o de vari�vel local
	ADCON0bits.GO = 1;					//inicia convers�o
	while (ADCON0bits.GO);				//aguarda finalizar convers�o
	Result_AD = (((int)ADRESH)<<8)|(ADRESL);	//obt�m valor da convers�o 
	return Result_AD;					//retorna valor da convers�o
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
	sprintf(buf," Temp =%c%u.%01u*C",sinal,parte_inteira,parte_decimal);		//converte valor em string e armazena no vetor buf	
	pt = buf;							//passa para o ponteiro pt o endere�o de buf
	return (pt);						//retorna o endere�o de buf.
}//******************************************************************
//esta fun��o atualiza o LCD
void Atual_LCD (void)
{
	EscInstLCD(0x01);					//limpa display e mostra cursor piscando na primeira posi��o da primeira linha
	while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o

	EscStringLCD(buf);					//escreve string no LCD
	while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
    
    if(temp1>36.0)
    {
        EscInstLCD(0xC0);
        while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
        if(z==1)								//PWM desligado?
        {
            sprintf(buf,"duty cycle 33%");		//converte valor em string e armazena no vetor buf	
            EscStringLCD(buf);					//escreve string no LCD
            while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
        }
        else if(z==2)							//PWM ligado com duty cycle de 50%?
        {
            sprintf(buf,"duty cycle 66%");		//converte valor em string e armazena no vetor buf	
            EscStringLCD(buf);					//escreve string no LCD
            while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
        }

        else if(z==3)							//PWM ligado com duty cycle de 100%?
        {
            sprintf(buf,"duty cycle 100%");		//converte valor em string e armazena no vetor buf	
            EscStringLCD(buf);					//escreve string no LCD
            while(TesteBusyFlag());				//espera LCD controller terminar de executar instru��o
        }        
    }
}//******************************************************************
//Ativa sinal PWM com um duty cycle de 50%. 
//Fosc=8MHz e FPWM=15625Hz.
void Confg_PWM (void)
{
	PR2 = 127;								//per�odo do sinal PWM = 15625Hz
	CCPR1L = 0b01000000;
	CCP1CONbits.DC1B1 = 0;
	CCP1CONbits.DC1B0 = 0;					//bits de controle = 256
	TRISCbits.RC2 = 0;						//configura pino de sa�da do sinal PWM como sa�da
//*******************************************************************						
//configura TMR2 para operar como temporizador e estourar a cada 4ms
	T2CON = 0b00000100;					//fator de postscaler de 1:1 <6:3>
										//fator de prescaler de 1:1<1:0>
										//liga TMR2<1>
	TMR2 = 0;							//inicializa TMR2
//*******************************************************************	
	CCP1CON *= 0b00110000;
	CCP1CON += 0b00001100;				//ativa modo PWM
}//******************************************************************
//esta fun��o atualiza o duty cycle do sinal PWM
void  Config_Duty_Cycle (int x)
{
int temp;								//declara��o de vari�vel local
	if(x>100)x=100;						//ajusta valor de x
	x = (x*100)/512;					//obt�m valor dos bits de controle
	temp =  x >> 2;						//obt�m os seis bits mais significativos						
	CCPR1L = temp;						//carrega bits de controle mais significativos 
//********************
//carrega segundo bit de controle menos significativo
	temp = x & 2;
	if (temp==1)CCP1CONbits.DC1B1 = 1;			
	else 	CCP1CONbits.DC1B1 = 0;
//********************
//carrega bit de controle menos significativo
	temp = x & 1;
	if (temp==1)CCP1CONbits.DC1B0 = 1;
	else 	CCP1CONbits.DC1B0 = 0;
}//*******************************************************************

