	/*********************************************************************
	Nome do arquivo:	main_27.c            
	Data:				21 de fevereiro de 2010          
	Versao:				1.0                              
	MPLAB IDE:			v8.20 
	Autor:				Wagner Zanco              
	*********************************************************************/
	#include <p18f4520.h>		//diretiva de compila��o
	#include <stdio.h>			//diretiva de compila��o
	//*******************************************************************
	int printf_message(FILE *f, const rom char *format, ...);
	//*******************************************************************
	void main (void)			//fun��o main
	{
	int x=31;																//declara��o de vari�vel local
		printf_message(_H_USART,"O conteudo da variavel z eh: %d.\n",x);	//chamada � fun��o
		while(1);															//loop infinito
	}
	//*******************************************************************
	int printf_message(FILE *f, const rom char *format, ...)	//fun��o printf_message
	{
		int x=0;							//declara��o de vari�vel local
		va_list ap;							//cria um ponteiro do tipo va_list
		va_start(ap, format);				//inicializa o ponteiro
		x = vfprintf(_H_USART, format, ap);	//chamada � fun��o
		va_end(ap);							//finaliza processo
		return x;							/*retorna um valor negativo em caso 
											de ocorr�ncia de algum erro na execu��o
											da fun��o, caso contr�rio retorna o npumero
											de caracteres escritos.*/
	//*******************************************************************
	}