/*********************************************************************
Nome do arquivo:	main_03.c            
Data:	    		13 de novembro de 2008          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <stdio.h>					//diretiva de compila��o
//*******************************************************************
//declara��o de fun��o
void _parametros (unsigned char c)	//fun��o _parametros
{
	unsigned char y;				//declara��o de vari�vel local inicializada
	y = c + 25;						//y = y + 1
	printf("y = %u\n",y); 			//envia para a USART o valor de x
}
//*******************************************************************
//*******************************************************************
void main(void)						//fun��o main					
{	
	_parametros(15);				//chamada � fun��o com passagem de par�metro
	while (1);						//loop infinito	
//*******************************************************************
}
