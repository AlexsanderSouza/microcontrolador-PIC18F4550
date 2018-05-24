/*********************************************************************
Nome do arquivo:	main_06.c            
Data:	    		14 de novembro de 2008          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <stdio.h>				//diretiva de compila��o
//*******************************************************************
unsigned char x = 0;			//declara��o de vari�vel global inicializada
//*******************************************************************
//declara��o de fun��o
char inc_y(void)				//fun��o inc_y
{
	static char y = 0;			//declara��o de vari�vel local inicializada
	y++;						//y = y + 1
	return y;					//retorna de fun��o com valor 
}
//*******************************************************************
void main(void)					//fun��o main					
{		
	while(x < 10)				//executa bloco de c�digo a seguir enquanto x < 10
	{
		x = inc_y();			//chamda � fun��o com retorno de valor
		printf("x = %u\n",x); 	//envia para a USART o valor de x
	}
	while(1);					//loop infinito
//*******************************************************************
}