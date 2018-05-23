/*********************************************************************
Nome do arquivo:	main_22.c            
Data:				03 de fevereiro de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>		//diretiva de compila��o
#include <stdio.h>			//diretiva de compila��o
#include <string.h>			//diretiva de compila��o
//*******************************************************************
//declara��o de estrutura
struct frame
{
	char x;
	char y;	
	char w[3];
};
//*******************************************************************
//prot�tipo de fun��o
void Verif_soma (struct frame);
//*******************************************************************
 /rotina principal
	void main (void)								//fun��o main
	{
		struct frame soma= {10,20,'A','B','C'};		//declara��o de vari�vel de estrutura inicializada 
		Verif_nota (soma);							//chamada a fun��o com passagem de par�metro
		while(1);									//loop infinito
	}
//***************************************
void Verif_soma (struct frame _soma)				//fun��o Verif_nota
	{
		printf("O conteudo de x eh: %d\n", _soma.x);		//envia para a UART o conteudo de x
		printf("O conteudo de y eh: %d\n", _soma.y);		//envia para a UART o conteudo de y
		printf("O conteudo w[0] eh: %d\n", _soma.w[0]);		//envia para a UART o conteudo de w[0]
		printf("O conteudo de w[1] eh: %d\n", _soma[1]);	//envia para a UART o conteudo de w[1]
		printf("O conteudo de w[2] eh: %d\n", _soma[2]);	//envia para a UART o conteudo de w[2]
//***************************************
	}
