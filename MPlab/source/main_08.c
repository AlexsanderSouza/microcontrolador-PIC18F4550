/*********************************************************************
Nome do arquivo:	main_08.c            
Data:	    		23 de novembro de 2008          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <stdio.h>									//diretiva de compila��o
//*******************************************************************
void main(void)										//fun��o main					
{	
unsigned char x;									//declara��o de vari�vel n�o inicializada
unsigned char y;									//declara��o de vari�vel n�o inicializada
unsigned int z;										//declara��o de vari�vel n�o inicializada
unsigned int w;										//declara��o de vari�vel n�o inicializada
	x = 37;											//atribui a z o valor 37
	y = 6;											//atribui a z o valor 37
	z = x / y; 										//z = x / y
	w = x%y;										//w recebe o resto da divis�o x/y
	printf("37/6 = %d",z);							//envia para a USART o rsultado da divis�o x/y
	printf(", e o resto da divisao = %d\r\n",w);	//envia para a USART o resto da divis�o x/y
	while (1);										//loop infinito	
//*******************************************************************
}
