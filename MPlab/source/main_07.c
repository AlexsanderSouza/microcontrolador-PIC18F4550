/*********************************************************************
Nome do arquivo:	main_07.c            
Data:	    		20 de novembro de 2008          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
//delara��o de vari�vel global com endere�o fixo na mem�ria RAM
#pragma udata my_section=0x100		//cria se��o de dados na mem�ria RAM
float f1;							//declara��o de var�avel global n�o inicializada
float f2;							//declara��o de var�avel global n�o inicializada
#pragma udata						//termina se��o de dados
//*******************************************************************
void main(void)						//fun��o main					
{	
	f1 = 3.59375;					//atribui o valor 3,59375 � vari�vel f1
	f2 = 465.85;					//atribui o valor 465.85 � vari�vel f2
	while (1);						//loop infinito	
//*******************************************************************
}
