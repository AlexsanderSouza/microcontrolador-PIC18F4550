/*********************************************************************
Nome do arquivo:	DSP_7Seg_x4.c            
Data:	    		14 de mar�o de 2010          
Versao:				1.0                              
MPLAB IDE:			v8.20a 
Autor:				Wagner Zanco              
*********************************************************************/
#include <p18cxxx.h>			//diretiva de compila��o
#include "DSP_7Seg_x4.h"		//diretiva de compila��o
//********************************************************************
void Aciona_DPS_7_seg (unsigned char Dsp4, unsigned char Dsp3, unsigned char Dsp2, unsigned char Dsp1)
{
static unsigned char Atual_Dsp = 1;			//declara��o  de vari�vel local static inicializada
const char tabela[] = {
						0x3F,	// n�mero 0
						0x06,	// n�mero 1
						0x5B,	// n�mero 2
						0x4F,	// n�mero 3
						0x66,	// n�mero 4
						0x6D,	// n�mero 5
						0x7C,	// n�mero 6
						0x07,	// n�mero 7
						0x7F,	// n�mero 8
						0x67,	// n�mero 9
						0x00	//apaga display
					  };
//********************************************************************
//configura��o dos pinos
	L_DADOS = 0x00;			//configura pinos das linhas de dados como sa�da
	ADCON1 = 0x0F;			//configura Port A e Port E como pinos digitais
	DIR_A1 = 0;				//configura linha de endere�o A1 como sa�da
	DIR_A2 = 0;				//configura linha de endere�o A2 como sa�da
	DIR_A3 = 0;				//configura linha de endere�o A3 como sa�da
	DIR_A4 = 0;				//configura linha de endere�o A4 como sa�da
//********************************************************************
//atualiza display
if(Atual_Dsp==1)				//atualizar display 1
	{
      	PORTD = tabela[Dsp1];	//atualiza display 1
      	DSP_1 = 1;				//ativa linha A1
      	DSP_2 = 0;				//desativa linha A2
      	DSP_3 = 0;				//desativa linha A3
      	DSP_4 = 0;				//desativa linha A4
		Atual_Dsp = 2;			//aponta endere�o para o pr�ximo display
	}
	else 	if(Atual_Dsp==2)	//atualizar display 2
	{
   		PORTD = tabela[Dsp2];	//atualiza display 2
   		DSP_1 = 0;				//desativa linha A1
    	DSP_2 = 1;				//ativa linha A2
    	DSP_3 = 0;				//desativa linha A3
    	DSP_4 = 0;				//desativa linha A4
		Atual_Dsp = 3;			//aponta endere�o para o pr�ximo display
	}
 	else	if(Atual_Dsp==3)	//atualizar display 3
	{
		PORTD = tabela[Dsp3];	//atualiza display 3
		DSP_1 = 0;				//desativa linha A1
		DSP_2 = 0;				//desativa linha A2
		DSP_3 = 1;				//ativa linha A3
		DSP_4 = 0;				//desativa linha A4
		Atual_Dsp = 4;			//aponta endere�o para o pr�ximo display
	}
 	else	if(Atual_Dsp==4)	//atualizar display 4
	{
		PORTD = tabela[Dsp4];	//atualiza display 4
		DSP_1 = 0;				//desativa linha A1
		DSP_2 = 0;				//desativa linha A2
		DSP_3 = 0;				//desativa linha A3
		DSP_4 = 1;				//ativa linha A4
		Atual_Dsp = 1;			//aponta endere�o para o pr�ximo display
	}
//*********************************************************************
}