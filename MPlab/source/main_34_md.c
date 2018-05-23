/*******************************************************************************
Nome do arquivo:	main_34_md.c            
Data:	    		22 abril de 2017          
Versao:				1.0                              
MPLAB IDE:			MPLAB-X v.3.55 
Autor:				Wagner Zanco
Modificado por:     Carl�cio Silva  
Descri��o: Configura��o do TIMER0 para operar como temporizador no modo 16 bits, 
com interrup��o com a codifica��o desenvolvida dentro de configTMR0() com passagem
de par�metro e com a inicializa��o do TIMER desmembrada da configura��o. Com
uma fun��o para tratar a interrup��o em separado.              
*******************************************************************************/
#include <p18f4520.h>			//diretiva de compila��o
#include "MCC18.h"              //diretiva de compila��o

//******************************************************************************
//Prot�tipos de fun��es
void Inic_Regs(void);
void setupTIMER0(void);
void high_isr(void);

//******************************************************************************
// Declara��o de vari�veis globais
unsigned char flagPORTD = 0;

//******************************************************************************
/* Vetor de interrup��o de alta prioridade.
 * Toda vez que ocorre uma interrup��o o fluxo do program � desviado para a 
 * regi�o de mem�ria definida por essa instru��o, mais especificamente, para o 
 * endere�o 0x08 da Mem�ria de Programa. */ 
#pragma code high_vector=0x08
void interrupt_at_high_vector(void)
{
    /*Desvia programa para rotina de tratamento da interrup��o*/
	_asm GOTO high_isr _endasm		
}
#pragma code

//******************************************************************************
void main(void)							//fun��o main				
{	
	Inic_Regs();						//configurar SFRs - Geral  
    setupTIMER0();                      //configurar SFRs - TIMER 0
	while(1);							//loop infinito
}

/*******************************************************************************
Esta funcao inicializa os registradores SFRs.*/
 void Inic_Regs(void)
{
	TRISA = 0x00;				//PORTA sa�da
	TRISB = 0x00;				//PORTB sa�da
	TRISC = 0x00;				//PORTC sa�da
	TRISD = 0x00;				//PORTD sa�da
	TRISE = 0x00;				//PORTE sa�da
	ADCON1 = 0x0F;				//configura pinos dos PORTA e PORTE como digitais
	PORTA = 0;					//limpa PORTA
	PORTB = 0;					//limpa PORTB
	PORTC = 0;					//limpa PORTC
	PORTD = 0x00;				//acende os LEDS
	PORTE = 0;					//limpa PORTE   
}
 /******************************************************************************
  Esta funcao inicializa os registradores SFRs do TIMER 0*/  
 void setupTIMER0(void)
 {
//******************************************************************************     
//Passo 1: Habilitar a interrup��o de estouro de TMR0
	INTCONbits.TMR0IE = 1;	//liga chave individual de interrup��o do TIMER 0     
	INTCONbits.GIE = 1;		//liga chave geral de interrup��o
    
//******************************************************************************
/* Passo 2: Configurar o TMR0 para operar como temporizador e estourar a cada 1s
 * T0CON<7> (TMR0ON = 1): Liga o TIMER 0
 * T0CON<6> (T08BIT = 0): Operar no modo 16 bits
 * T0CON<5> (T0CS = 0)  : Operar com o clock do Fosc
 * T0CON<4> (T0SE = 0)  : Operar na borda de subida **
 * T0CON<3> (PSA = 0)   : Operar a partir do prescaler
 * T0CON<2:0> (T0PS2 = 1; T0PS1 = 1; T0PS0 = 1): Configura o prescaler para 1:256,
 * com essa configura��o o prescaler proporciona um atrso de 128us. */   
	T0CON = 0b10000111;
    
//******************************************************************************    
/*Passo 3: Inicializar o TMR0. 
 * Como esta configura��o contempla o modo 16 bits, inicializando o TMR0 com o 
 * valor 49911, este contar� de 0 - 15624, ao final de tudo, proporcionando um 
 * atraso de 2 segundos. */
    TMR0H = 0b11000010; 
    TMR0L = 0b11110111;     
 }
 
 /****************************************************************************** 
 * Rotina de tratamento de interrup��o (ISR)
 * Depois que ocorre a interrup��o, o vetor de interrup��o direciona o fluxo do
 * programa para a localiza��o da Mem�ria de Programa onde encontra-se essa 
 * instru��o, "high_isr".*/
#pragma interrupt high_isr
void high_isr(void)
{
    //**************************************************************************
    /* - if(INTCONbits.TMR0IF);
     * Se TMR0IF for igual a 1 trata a interrup��o vinda do TIMER 0.*/
	if(INTCONbits.TMR0IF);
	{
        //**********************************************************************
        /* - INTCONbits.TMR0IF;
         * Como houve interrup��o pelo TIMER 0, o bit INTCON<2> (INTCONbits.TMR0IF)
         * precisa ser limpo (levado a L�GICO 0) para que, quando houver outra 
         * interrup��o esta possa ser identificada. O hardaware n�o faz isso para
         * o programador, sendo necess�rio ser feito a n�vel de softwarre.*/
		INTCONbits.TMR0IF=0;	
        	
        //**********************************************************************
        /* Neste ponto coloca-se as instru��es que dever�o ocorrer dentro da
         * interrup��o, como por exemplo a seq��ncia de comuta��o dos LEDS.*/
        if(!flagPORTD)
        {
            //******************************************************************
            flagPORTD = 1;          /*
                                     Controla o acendimento dos LEDS segundo a
                                     interrup��o, na verdade o que esta vari�vel
                                     faz � definir um tipo de permuta��o entre os
                                     estados acessos e apagados dos LEDS. Na pr�xima 
                                     interrup��o ela direciona o fluxo do programa
                                     para a estrutura de decis�o else().*/ 
            
            //******************************************************************
            PORTD = 0xFF;           /* Apaga os LEDS */ 
            
            //******************************************************************
            /* TMR0L = 123 <-> 0x7B; TMR0H = 225 <-> 0xE1 <-> TMR0 = 65535 - 57723 = 7812
            * De acordo com a necessidade � �til inicializar o registro TMR0
            * (modo 16 bits: TMR0L:TMR0H) para definir alguma quantidade de contagem. 
            * Neste caso, o TMR0 = 0b1110000101111011 (57723) iniciado com esse
            * valor temos que o TMR0 contar� de 0 - 7812, proporcionando ao final de 
            * tudo, um atraso de 1 segundo.*/
            TMR0H = 0b11100001;              
            TMR0L = 0b01111011;            
        }
        else 
        {
            //******************************************************************
            flagPORTD = 0;          /*
                                     Controla o acendimento dos LEDS segundo a
                                     interrup��o, na verdade o que esta vari�vel
                                     faz � definir um tipo de permuta��o entre os
                                     estados acessos e apagados dos LEDS. Na pr�xima 
                                     interrup��o ela direciona o fluxo do programa
                                     para a estrutura de decis�o if().*/
            
            //******************************************************************
            PORTD = 0x00;          // Acende os LEDS   
            /* TMR0L = 247 <-> 0xF7; TMR0H = 194 <-> 0xC2 <-> TMR0 = 65535 - 49911 = 15624 
            * De acordo com a necessidade � �til inicializar o registro TMR0
            * (modo 16 bits: TMR0L:TMR0H) para definir alguma quantidade de contagem. 
            * Neste caso, o TMR0 = 0b1100001011110111 (49911) , proporcionando ao final de 
            * tudo, um atraso de 2 segundos, contando de 0 - 15624.*/
            TMR0H = 0b11000010;            
            TMR0L = 0b11110111;              
        }        
	}
}
 
