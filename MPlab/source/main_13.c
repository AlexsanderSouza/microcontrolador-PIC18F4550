/*********************************************************************
Nome do arquivo:	main_13.c            
Data:	07 de janeiro de 2009          
Versao:	1.0                              
MPLAB IDE:	v8.20a 
Autor:	Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>	//diretiva de compila��o
#include <stdio.h>		//diretiva de compila��o
//*******************************************************************
void main(void)	//fun��o main					
{	
int x;											//declara��o de vari�vel local inicializada
	for(x=0; x<=5; x++)							//la�o de itera��o
	{
		if(x>3)	break;							//sai do la�o se x > 3	
		else printf("x eh igual a %d\r\n", x);	//envia para a USART o valor de x. 
	}
	while (1);									//loop infinito
//*******************************************************************
}
