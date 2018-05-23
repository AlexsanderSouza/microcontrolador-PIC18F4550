/*********************************************************************
Nome do arquivo:	main_26.c            
Data:				16 de fevereiro de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18f4520.h>							//diretiva de compila��o
#include <stdio.h>								//diretiva de compila��o
//*******************************************************************
//vari�veis globais
rom char z[] = "Botafogo eh um timao!";			//declara��o de vetor inicializado
//*******************************************************************
void main (void)								//fun��o main
{
char x = 150;									//declara��o de vari�vel local inicializada
int xa = -2500;									//declara��o de vari�vel local inicializada
unsigned int ya = 40000 ;						//declara��o de vari�vel local inicializada
unsigned char y = 200;							//declara��o de vari�vel local inicializada
short long wa = 9000000;						//declara��o de vari�vel local inicializada
char w[] = "Eu gosto de C.";					//declara��o de vetor inicializado
	fprintf(_H_USART,"O conteudo da variavel x em decimal sinalizado eh: %d\n", x);
	fprintf(_H_USART,"O conteudo da variavel x em decimal nao sinalizado eh: %hhu\n", x);
	fprintf(_H_USART,"O conteudo da variavel xa em decimal sinalizado eh: %d\n",xa);
	fprintf(_H_USART,"O conteudo da variavel xa em decimal nao sinalizado eh: %u\n",xa);
	fprintf(_H_USART, "O conteudo da variavel x em binario eh: %#hhb\n", x);
	fprintf(_H_USART,"O conteudo da variavel ya em decimal sinalizado eh: %d\n", ya);
	fprintf(_H_USART,"O conteudo da variavel ya em decimal nao sinalizado eh: %u\n", ya);
	fprintf(_H_USART,"O conteudo da variavel y em hexadeciaml eh: %#x\n",y);
	fprintf(_H_USART,"O conteudo da variavel y em hexadecimal eh: %#X\n",y);
	fprintf(_H_USART,"O conteudo da variavel wa em decimal sinalizado eh: %Hd\n",wa);
	fprintf(_H_USART,"O conteudo da variavel wa em decimal nao sinalizado eh: %Hu\n",wa);
	fprintf(_H_USART,"O conteudo da variavel wa em hexadecimal eh: %#Hx\n",wa);
	fprintf(_H_USART,"O conteudo da variavel wa em binario eh: %#Hb\n",wa);
	fprintf(_H_USART,"O conteudo da variavel wa em decimal eh: %#Hu e da variavel x em hexadecimal eh: %#hhx\n",wa,x);
	fprintf(_H_USART,"O endereco da variavel wa eh: %#p\n",&wa);
	fprintf(_H_USART,"O endereco do vetor z eh: %#p\n",&z);
	fprintf(_H_USART,"%s\n",w);
	fprintf(_H_USART,"%S\n",z);
	while(1);									//loop infinito
//*******************************************************************
}
