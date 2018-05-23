/*******************************************************************************
Nome do arquivo:	main_34-1_md.c            
Data:	    		27 abril de 2018          
Versao:				1.1                              
MPLAB IDE:			MPLAB-X v.4.15 
Autor:				Wagner Zanco
Modificado por:     Carl�cio Silva     
Descri��o: Configura��o do TIMER0 para operar como temporizador no modo 8 bits, 
sem interrup��o com a codifica��o desenvolvida dentro de main().         
*******************************************************************************/
#include <p18f4550.h>			//diretiva de compila��o
#include "MCC18_18F4550.h"      //diretiva de compila��o

//******************************************************************************
//Prot�tipos de fun��es
void configSFR(void);

//******************************************************************************
// Declara��o de vari�veis globais
unsigned char flagPORTD = 0;

//******************************************************************************
void main(void){
    //Configura��o do SFR
    configSFR();
    
// Configura��o do TIMER0
//****************************************************************************** 
/* Passo 1: Configurar o TMR0 para operar como temporizador e estourar a cada Xs
 * T0CON<7> (TMR0ON = 1): Liga o TIMER 0
 * T0CON<6> (T08BIT = 1): Operar no modo 8 bits
 * T0CON<5> (T0CS = 0)  : Operar com o clock do Fosc/4
 * T0CON<4> (T0SE = 0)  : Operar na borda de subida **
 * T0CON<3> (PSA = 0)   : Operar a partir do prescaler
 * T0CON<2:0> (T0PS2 = 1; T0PS1 = 1; T0PS0 = 1): Configura o prescaler para 1:256,
 * com essa configura��o o prescaler proporciona um atrso de 128us. */   
    T0CON = 0b11000111;
//******************************************************************************
    
/*Passo 2: Inicializar o TMR0.*/
    TMR0L = 0;  
//****************************************************************************** 
        
	while(1){							//loop infinito
        if(INTCONbits.TMR0IF){
            if(!flagPORTD){
                PORTD = 0xFF;
                flagPORTD = 0xFF;
                TMR0L = 0;  
            }
            else{
                PORTD = 0x00;
                flagPORTD = 0x00;
                TMR0L = 127;  
            }
            INTCONbits.TMR0IF = 0;      //limpa a flag de estouro  
        }
    }
}

/*******************************************************************************
Esta fun��o inicializa os registradores SFRs.*/
 void configSFR(void)
{
	TRISA = 0x00;		//PORTA sa�da
	TRISB = 0x00;		//PORTB sa�da
	TRISC = 0xFF;		//PORTC entrada
	TRISD = 0x00;		//PORTD sa�da
	TRISE = 0x00;		//PORTE sa�da
	ADCON1 = 0x0F;		//configura pinos dos PORTA e PORTE como digitais
	PORTA = 0;			//limpa PORTA
	PORTB = 0;			//limpa PORTB
	PORTC = 0;			//limpa PORTC
	PORTD = 0;  		//limpa PORTC
	PORTE = 0;			//limpa PORTE   
}
 

 
