/*********************************************************************
Nome do arquivo:	main_05.c            
Data:	    		13 de novembro de 2008          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <stdio.h>			//diretiva de compila��o
//*******************************************************************
unsigned char x;			/*declara��o de vari�vel global n�o inicializada*/
//*******************************************************************
void main(void)				//fun��o main					
{		
	x = 10;					//seq��ncia de comandos
	soma();					//chamada � fun��o soma()
	printf("x = %u\n",x); 	//envia para a USART o valor de x
	while (1);				//loop infinito
//*******************************************************************
}