	/*********************************************************************
	Nome do arquivo:	main_24.c            
	Data:				14 de fevereiro de 2010          
	Versao:				1.0                              
	MPLAB IDE:			v8.20a 
	Autor:				Wagner Zanco              
	*********************************************************************/
	#include <p18f452.h>	//diretiva de compila��o
	#include <stdio.h>		//diretiva de compila��o
	//*******************************************************************
	//defini��es
	#define max 50			//diretiva decompila�ao
	//*******************************************************************
	//vari�veis globais
	char buffer[max]="";
	//*******************************************************************
	void main (void)
	{
	stdout = _H_USER;					//ativa stream definida pelo usu�rio como sa�da padr�o
	printf("Quando penso em voce.\n");	//envia string para stdout
	while(1);							//loop infinito
	}
	//*******************************************************************
	int _user_putc (char c)
	{
	char i;							//declara��o de vari�vel local incializada	
	static char x=0;				//declara��o de vari�vel local est�tica incializada
		if(c!=0 && c!=0x0A)			//executa bloco de c�digo se c!=0 e c!=0Ah
		{
			buffer[x]=c;			//carrega caractere no �ndice do buffer apontado por x
			x++;					//incrementa a vari�vel x 
		}
		else 	if(c==0x0A)			//se n�o e se c==0Ah executa bloco de c�digo
				{
					buffer[x]=c;	//carrega o caractere recebido no �ndice apontado por x
					x++;			//incrementa x
					buffer[x]='\0';	//carrega caractere null no indice apontado por x
					x=0;			//x=0
				}
	//*******************************************************************
	}
