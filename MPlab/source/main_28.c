	/*********************************************************************
	Nome do arquivo:	main_28.c            
	Data:				21 de fevereiro de 2010          
	Versao:				1.0                              
	MPLAB IDE:			v8.20 
	Autor:				Wagner Zanco              
	*********************************************************************/
	#include <p18f4520.h>		//diretiva de compila��o
	#include <stdio.h>			//diretiva de compila��o
	//*******************************************************************
	//defini��es
	#define		AJUSTA_DECIMAL	100	//precis�o de duas casas decimais
	/*
	1 	- nenhuma parte decimal
	10	- uma casa decimal
	100 - duas casas decimais
	etc...
	//*******************************************************************/
	//prot�tipos de fun��es
	int printf_message(FILE *f, const rom char *format, ...);
	char *Conv_Float_String(float float_in);
	//*******************************************************************
	//vari�veis globais
	char buf[50];							//declara��o de vetor
	//*******************************************************************
	void main (void)
	{
	float x = 6553.35;						//declara��o de vari�vel local
	char *p;								//declara��o de vari�vel local
		p=Conv_Float_String(x);				//chamada � fun��o com retorno de valor
		printf_message(_H_USART,"O conteudo da variavel z eh: %s.\n",p);	//chamada � fun��o
		while(1);							//loop infinito
	}
	//*******************************************************************
	int printf_message(FILE *f, const rom char *format, ...)
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
	/********************************************************************
	//Convers�o de float para ASCII. Esta fun��o converte valores float 
	na faixa de -65535.998 a +65535.998 em uma string. 
	//*******************************************************************/
	char *Conv_Float_String(float float_in)
	{
	unsigned int parte_inteira;				//declara��o de vari�vel local
	unsigned int parte_decimal;				//declara��o de vari�vel local
	char sinal, *pt;						//declara��o de vari�vel local
	unsigned char x, y;						//declara��o de vari�vel local
	//*******************************************************************
		if(float_in < 0)					//valor � menor que 0?
		{
			sinal = '-';					//sim, sinal negativo
			float_in = float_in * (-1);		//inverte o sinal de float_in
		}
		else sinal = ' ';					//n�o, sinal positivo
	//*******************************************************************
		parte_inteira = float_in;			//resgata parte interia dovalor
	//*******************************************************************
		parte_decimal =(unsigned int)((float_in - parte_inteira) * AJUSTA_DECIMAL);	//resgata parte fracion�ria do valor
		sprintf(buf,"%c%u.%02u",sinal,parte_inteira,parte_decimal);					//converte valor em string e armazena no vetor buf
		pt = buf;							//passa para o ponteiro pt o endere�o de buf
		return (pt);						//retorna o endere�o de buf
	//*******************************************************************
	}
