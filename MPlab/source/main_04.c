/*********************************************************************
Nome do arquivo:	main_04.c            
Data:	    		13 de novembro de 2008          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <stdio.h>			//diretiva de compila��o
//*******************************************************************
unsigned char x,y;			//declara��o de vari�vel global n�o inicializada
unsigned char y;			//declara��o de vari�vel global n�o inicializada
unsigned int  z = 0;		//declara��o de vari�vel global inicializada
//*******************************************************************
void main(void)				//fun��o main					
{	
	x = 20;					//inicializa a vari�vel x com 20
	y = 50;					//inicializa a vari�vel x com 50
	z = (int) x * y;		//z = x * 1
	printf("z = %u\r\n",z);	//envia para a USART o valor de z
	while (1);				//loop infinito	
//*******************************************************************
} 
