/*********************************************************************
Nome do arquivo:	main_10.c            
Data:	    		28 de novembro de 2008          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <stdio.h>					//diretiva de compila��o
//*******************************************************************
void main(void)						//fun��o main					
{	
int *p;								//declara��o de vari�vel de ponteiro	
int contador;						//declara��o de vari�vel n�o inicializada
int x;								//declara��o de vari�vel n�o inicializada

	contador = 100;					//contador recebe o valor 100
	p = &contador;					//p recebe endere�o da vari�vel contador
	x = *p;							//x recebe o conte�do do endere�o apontado por p

	printf("O endereco da variavel contador eh = %#x\n",p);		//envia para a USART o endere�o de contador
	printf("O conteudo da variavel contador eh = %d\n",x);		//envia para a USART o conte�do de contador
	while (1);						//loop infinito	
//*******************************************************************
}
