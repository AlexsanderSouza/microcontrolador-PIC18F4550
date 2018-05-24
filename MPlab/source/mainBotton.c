/* 
 * File:   mainBotton.h
 * Author: Carl�cio Silva
 *
 * Created on 8 de Mar�o de 2017, 14:37
 */

/*Local para inser��o dos arquivos de cabe�alho*/
#include <p18F4520.h>
#include "MCC18.h"

main()
{
    /*Configura��o dos SFRs do projeto para ler um bot�o e acender um LED*/
    TRISA = 0b00000000;     // Configura o registro PORTA como sa�da
    TRISB = 0b00000001;     // Configura o pino RB0 do registro PORTB como entrada 
                            // e os demais como sa�da. Este pino ser� utilizado para 
                            // ler um bot�o.
    TRISC = 0b00000000;     // Configura o registro PORTC como sa�da
    TRISD = 0b00000000;     // Configura o registro PORTD como sa�da
    TRISE = 0b00000000;     // Configura o registro PORTE como sa�da
    ADCON1 = 0b00001111;    // Configura os registros PORTA e PORTE como digitais
    PORTA = 0b00000000;     // Limpa o registro PORTA, coloca seus bits em L�GICO 0
    PORTB = 0b00000000;     // Limpa o registro PORTB, coloca seus bits em L�GICO 0
    PORTC = 0b00000000;     // Limpa o registro PORTC, coloca seus bits em L�GICO 0
    PORTD = 0b00000001;     // Limpa o registro PORTD, coloca seus bits em L�GICO 0, 
                            // exceto o bit RD0, que ficar� com L�GICO 1. Neste bit (pino)
                            // estar� conectado um LED.    
    PORTE = 0b00000000;     // Limpa o registro PORTE, coloca seus bits em L�GICO 0
    /*Fim da configura��o dos SFRs*/
    
    while(1)                // Loop principal
    {
        if(PORTBbits.RB0==0)      // Verifica se o bot�o BT1 foi pressionado
        {
            PORTDbits.RD0=0;      // Se foi pressionado, acender LED
        }
        else PORTDbits.RD0=1;     // Se n�o foi pressionado, apagar o LED
    }
}