/*********************************************************************
Nome do arquivo:	main_09.c            
Data:	    		26 de novembro de 2008          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <stdio.h>					//diretiva de compila��o
//*******************************************************************
void main(void)						//fun��o main					
{	
unsigned char x = 5;				//declara��o de vari�vel inicializada
unsigned char y;					//declara��o de vari�vel n�o inicializada
unsigned char z;					//declara��o de vari�vel n�o inicializada
	y = x << 2;						//y = x multiplicado por 4
	z = y >> 1;						//z = y dividido por 2
	printf("y = %d\r\n",y);			//envia para a USART o valor de y
	printf("z = %d\r\n",z);			//envia para a USART o valor de z
	while (1);						//loop infinito	
//*******************************************************************
}
