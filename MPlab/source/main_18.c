/*********************************************************************
Nome do arquivo:	main_18.c            
Data:				02 de fevereiro de 2009          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>		//diretiva de compila��o
#include <stdio.h>			//diretiva de compila��o
//*******************************************************************
//prot�tipos de fun��es
void Recebe_Vetor(char *);	// port�tipo da fun��o Recebe_Vetor()
//*******************************************************************
void main(void)						//fun��o main					
{	
char alfabeto[10]={"Wagner"};		//declara��o de vetor inicializado com string

	Recebe_Vetor(alfabeto);			//chamada � fun��o com passagem de par�metro 	
	while (1);						//loop infinito
}
//*******************************************************************
void Recebe_Vetor(char *p)			//fun��o Recebe_Vetor
{
	printf("O conteudo o vetor alfabeto eh igual a %s\n", p);		//envia para a UART o conte�do do vetor apontado por p. 
//******************************************************************
}

