/*********************************************************************
Nome do arquivo:	main_25.c            
Data:				16 de fevereiro de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>		//diretiva de compila��o
#include <stdio.h>			//diretiva de compila��o
//*******************************************************************
//defini��es
#define max  55				//diretiva de compila��o
//*******************************************************************
//prot�tipos de fun��es
int divisao (int x, int y);
//*******************************************************************
//vari�veis globais
char buffer[max] = "";		//declara��o de vetor de caracteres
//*******************************************************************
void main (void)
{
int x = 150;				//declara��o de vari�vel local incializada
int y = 2;					//declara��o de vari�vel local incializada
int z =0;					//declara��o de vari�vel local incializada
	z = divisao(x,y);		//chamada � fun��o com passagem de par�metros
	while(1);				//loop infinito
}
//*******************************************************************
int _user_putc (char c)
{
static char x=0;			//declara��o de vari�vel local est�tica  inicializada
	if(c!=0 && c!=0x0A)		//executa bloco de c�digo se c!=0 e c!=0Ah
	{
		buffer[x]=c;		//carrega caractere recebido no �ndice do buffer apontado por x
		x++;				//incrementa x
		buffer[x]='\0';		//carrega o caractere null no �ndice apontado por x
	}
	else 	if(c==0x0A)		//se n�o e se c==0Ah executa bloco de c�digo
		{
		buffer[x]=c;		//carrega o caractere recebido no �ndice apontado por x
		x++;				//incrementa x
		buffer[x]='\0';		//carrega o caractere null no �ndice apontado por x
		x=0;				//x=0
		}
}
//*******************************************************************
int divisao (int x, int y)		//fun��o divisao
{
int result;						//declara��o  de vari�vel local n�o  inicializada
	if (y==0) 					//se denominador � zero
	{
		fprintf(_H_USER,"A divisao nao foi efetuada, o denominador eh zero.\n");	/*envia para a UART que a divis�o n�o pode ser 
																					efetuada porque o denominador � zero*/
		return -1;				//denominador � zero. retorna -1
	}
	else 						//se denominador n�o � zero
	{
		result = x / y;			//result = x /y
	    fprintf(_H_USART,"O resultado da divisao eh: %d\n",result);	//envia para a UART o resultado da divis�o
		return result;			//retorna resultado da divis�o
	}

//*******************************************************************
}
