/*********************************************************************
Nome do arquivo:	main_17.c            
Data:				02 de fevereiro de 2009          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>	//diretiva de compila��o
#include <stdio.h>		//diretiva de compila��o
//*******************************************************************
//prot�tipos de fun��es
//*******************************************************************
void main(void)					//fun��o main					
{	
char alfabeto[30]={"Wagner"};	//declara��o de vetor inicializado
unsigned char i=0;				//declara��o de vari�vel local inicializada
unsigned char x=0x61;			//declara��o de vari�vel local inicializada

	for(i=0;i<=25;i++)			//la�o de itera��o
	{
	alfabeto [i]=x++;			//carrega x no �ndice apontado por i e em seguida incrementa x 
	}
	printf("%s\n", alfabeto);	//envia para a UART todo o alfabeto
	while (1);					//loop infinito
//*******************************************************************
}
