// Autora: Adriana Scrobote 
/* Algoritmo gen�tico para maximizar a fun��o f(x)=x� no intervalo [0,31]. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

/* Inicializa vetor com 0 */
void inicializaVetor(int *vetor, int tamanho)
{
	int i;
	for (i = 0; i < tamanho; i++)
		vetor[i] = 0;
}

/* Inicializa vetor com -1 */
void inicializaVetorNegativo(int *vetor, int tamanho)
{
	int i;
	for (i = 0; i < tamanho; i++)
		vetor[i] = -1;
}

/* Imprime qualquer vetor de inteiros */
void imprimeVetor(int *vetor, int tamanho)
{
	int i;
	for (i = 0; i < tamanho; i++)
		printf ("%d ", vetor[i]);
	printf ("\n");
}

/* Imprime a popula��o bin�ria */
void imprimeVetorString (char populacao[][6], int tamanho)
{
	int i;
	for (i = 0; i < tamanho; i++)
    {
        printf ("\n%s ", populacao[i]);
    }
}


/* Verifica se determinado indiv�duo j� est� est� presente na popula��o atual ou n�o */
int verificaElemento (int *populacao, int tamanho, int valor)
{
	int i;
	for (i = 0; i < tamanho; i++)
		if (populacao[i] == valor)
			return 1;
	return 0;
}


/* Sorteia popula��o inicial */
void sorteiaIniciais (int *populacao, int tamanho)
{
	int i;
	int valor, verificacao;
	
	for (i = 0; i < tamanho; i++)
	{
		valor = rand() % 32;
		verificacao = verificaElemento(populacao, tamanho, valor);
		while (verificacao == 1)
		{
			valor = rand() % 32;
			verificacao = verificaElemento(populacao, tamanho, valor);
		}
		populacao[i] = valor;
				
	}
}


/* Fun��o de Aptid�o */
void funcaoAdaptacao (int *populacao_num, int * resultado_funAdaptacao, int tamanho)
{
	int i;
	for (i = 0; i < tamanho; i++)
	{
		resultado_funAdaptacao[i] = populacao_num[i] * populacao_num[i];
	}
}


/* Calcula a probabilidade de sele��o de cada indiv�duo */
void calculaPorcentagem (int *resultado_funAdaptacao, int *porcentagem_selecao, int tamanho)
{
	int i, soma = 0;
	int teste;
	for (i = 0; i < tamanho; i++)
	{
		soma += resultado_funAdaptacao[i];
	}
	
	for (i = 0; i < tamanho; i++)
	{
		teste = round((((float)(resultado_funAdaptacao[i]) / soma) * 100));
		porcentagem_selecao[i] = teste;
	}
}


/* Calcula porcentagem na roleta para cada indiv�duo de acordo com sua probabilidade de sele��o */
void calculaPorcentagemRoleta (int *porcentagem_roleta, int *porcentagem_selecao, int tamanho)
{
	int i, aux;
	for (i = 0; i < tamanho; i++)
	{
		aux = round(porcentagem_selecao[i] * 3.6);
		porcentagem_roleta[i] = aux;
	}
}


/* Completa popula��o bin�ria com zeros � esquerda quando necess�rio */
void ajustaPopulacao (char populacao[][6], int tamanho)
{
	int i = 0, j, l, m;
	char aux[6];
	for (i = 0; i < tamanho; i++)
	{
		j = 0;
		
		while (populacao[i][j] != '\0')
		{
			aux[j] = populacao[i][j];
			j++;
	    }
	    aux[j] = '\0';
	    
	    for (m = 0; m < 6 - j; m++)
	    {
	    	populacao[i][m] = '0';
		}
		l = 0;
		for (m = m-1; m < 6-1; m++)
		{
			populacao[i][m] = aux[l];
			l++;	
		}
		populacao[i][m] = '\0';
	}
}


/* Ajusta intervalo de porcentagem referente a cada indiv�duo de acordo com seu intervalo na roleta */
void ajustaIntervaloRoleta (int *porcentagem_roleta, int *intervalo_roleta, int tamanho)
{
	int i;
	if (intervalo_roleta[0] != 0)
	{
		intervalo_roleta[0] = porcentagem_roleta[0] - 1;
		for (i = 1; i < tamanho-1; i++)
		{
			intervalo_roleta[i] = intervalo_roleta[i-1] + porcentagem_roleta[i];
		}
		intervalo_roleta[i] = 359;
	}
	else
	{
		intervalo_roleta[0] = porcentagem_roleta[0];
		for (i = 1; i < tamanho-1; i++)
		{
			intervalo_roleta[i] = intervalo_roleta[i-1] + porcentagem_roleta[i];
		}
		intervalo_roleta[i] = 359;
	}
	
}


/* M�todo da Roleta */
void metodoDaRoleta (int *selecao, int *porcentagem_roleta, int tamanho)
{
	int i;
	for (i = 0; i < tamanho; i++)
	{
		selecao[i] = rand() % 360; 
	}
}


/* Ajusta selecionados de acordo com o sorteio feito na roleta */
void verificaSelecionados (int *selecao, int *intervalo_roleta, int tamanho)
{
	int i, j;
	for (i = 0, j = 1; i < tamanho; i++)
	{
		for (j = 0; j < tamanho; j++)
		{
			if (selecao[i] < intervalo_roleta[j])
			{
				selecao[i] = j;
				break;
			}
		}
	}
}


/* Sorteia ordem dos pares para fazer o crossover */
void sorteiaOrdem (int *ordem_crossover, int tamanho)
{
	int i;
	int valor, verificacao;
	
	for (i = 0; i < tamanho; i++)
	{
		valor = rand() % tamanho;
		verificacao = verificaElemento(ordem_crossover, tamanho, valor);
		while (verificacao == 1)
		{
			valor = rand() % tamanho;
			verificacao = verificaElemento(ordem_crossover, tamanho, valor);
		}
		ordem_crossover[i] = valor;
				
	}
}


/* Crossover*/
void crossOver (char populacao[][6], int *ordem_crossover, int tamanho)
{
	int i, j, ponto_corte, par1, par2, par3, par4;
	for (i = 0; i < tamanho; i++)
	{
		if (ordem_crossover[i] == 0)
			par1 = i;
		else if (ordem_crossover[i] == 1)
			par2 = i;
		else if (ordem_crossover[i] == 2)
			par3 = i;
		else
			par4 = i;
	}
	ponto_corte = rand() % 3 + 1;
	ponto_corte ++;
	char aux[6];
	for (i = ponto_corte, j = 0; i <= tamanho; i++, j++) 
	{
		aux[j] = populacao[par1][i];
		populacao[par1][i] = populacao[par2][i];
		populacao[par2][i] = aux[j];
	}
	ponto_corte = rand() % 3 + 1;
	ponto_corte ++;
	for (i = ponto_corte, j = 0; i <= tamanho; i++, j++) 
	{
		aux[j] = populacao[par3][i];
		populacao[par3][i] = populacao[par4][i];
		populacao[par4][i] = aux[j];
	}	
}


/* Muta��o */
void Mutacao (char populacao[][6], int tamanho)
{
	int i, ponto_corte;
	for (i = 0; i < tamanho; i++)
	{
		ponto_corte = rand() % 3 + 1;
		ponto_corte++;	
		if (populacao[i][ponto_corte] == '0')
			populacao[i][ponto_corte] = '1';
		else 
			populacao[i][ponto_corte] = '0';
	}
}


/* Altera popula��o num�rica(que representa bin�ria nos c�lculos) atual de acordo com a popula��o bin�ria */
void ajustaNovaPopulacaoNum (char populacao[][6], int *populacao_num, int tamanho)
{
	int i, j, l, valor, aux;
	for (i = 0; i < tamanho; i++)
	{
		valor = 0;
		l = 0;
		for (j = 4; j >= 0; j--)
		{
			if (populacao[i][j] == '1')
			{
				aux = pow(2, l);
				valor += aux;
			}
			l++;
		}
		populacao_num[i] = valor;
	}
}


/* Altera popula��o bin�ria atual de acordo com o sorteio da roleta */
void ajustaPopulacaoFaixaSorteada (char populacao[][6], int *selecao, int tamanho)
{
	int i, j, indice;
	char pop_aux[4][6], aux[6];
	for (i = 0; i < tamanho; i++)
	{
		for (j = 0; j < 6; j++)
		{
			pop_aux[i][j] = populacao[i][j];
		}
	}
	for (i = 0; i < tamanho; i++)
	{
		indice = selecao[i];
		strcpy (aux, pop_aux[indice]);
		strcpy (populacao[i], aux);	
	}
}


/* Verifica se j� encontrou a solu��o final desejada */
int achouSolucao (int *populacao_num, int tamanho)
{
	int i, resultado = 0;
	for (i = 0; i < tamanho; i++)
	{
		if (populacao_num[i] != 31)
		{
			resultado = 1;
			return resultado;
		}
	}
	return resultado;
}


/* Fun��o Principal */
int main ()
{
	int n = 4, i = 0, populacao_num[n], resultado_funAdaptacao[n], selecao[n], intervalo_roleta[n], resultado;
	int porcentagem_selecao[n], porcentagem_roleta[n], ordem_crossover_mutacao[n];
	char populacao[n][6];
	inicializaVetor(populacao_num, n);
	inicializaVetor(resultado_funAdaptacao, n);
	inicializaVetor(porcentagem_selecao, n);
	inicializaVetor(porcentagem_roleta, n);
	inicializaVetor(selecao, n);
	inicializaVetor(intervalo_roleta, n);
	sorteiaIniciais(populacao_num, n);
	printf ("Populacao inicial: ");
	imprimeVetor(populacao_num, n);
	
	for (i = 0; i < n; i++)
    {
        itoa (populacao_num[i], populacao[i], 2);
        
    }
    
    while(1)
    /* Este programa poderia ser feito com outra condi��o de parada: um determinado n�mero de itera��es */
    /*EX: for (i = 0; i < 10; i++) */
    {
    	printf ("\nIteracao: %d\n", i);
    	printf ("Populacao:");
    	ajustaPopulacao (populacao, n);
	    imprimeVetorString (populacao, n);
	    funcaoAdaptacao(populacao_num, resultado_funAdaptacao, n);
	    printf ("\nFuncao Adaptacao: ");
	    imprimeVetor(resultado_funAdaptacao, n);
	    calculaPorcentagem (resultado_funAdaptacao, porcentagem_selecao, n);
	    printf ("Porcentagem Selecao: ");
	    imprimeVetor(porcentagem_selecao, n);
	    calculaPorcentagemRoleta (porcentagem_roleta, porcentagem_selecao, n);
	    printf ("Porcentagem Roleta: ");
	    imprimeVetor(porcentagem_roleta, n);
	    printf ("Intervalo Roleta: ");
	    ajustaIntervaloRoleta (porcentagem_roleta, intervalo_roleta, n);
	    imprimeVetor(intervalo_roleta, n);
	    printf ("Metodo da Roleta: ");
	    metodoDaRoleta (selecao, porcentagem_roleta, n);
	    imprimeVetor(selecao, n);
	    printf ("Faixa Selecionada: ");
		verificaSelecionados (selecao, intervalo_roleta, n);
		imprimeVetor(selecao, n);
		printf ("Populacao ajustada coonforme faixa da roleta sorteada:");
		ajustaPopulacaoFaixaSorteada (populacao, selecao, n);
		imprimeVetorString (populacao, n);
		inicializaVetorNegativo(ordem_crossover_mutacao, n);
		printf ("\nOrdem dos pares crossover: ");
		sorteiaOrdem (ordem_crossover_mutacao, n);
		imprimeVetor(ordem_crossover_mutacao, n);
		printf ("Crossover: ");
		crossOver (populacao, ordem_crossover_mutacao, n);
		imprimeVetorString (populacao, n);
		printf ("\nMutacao:");
		Mutacao (populacao, n);
		imprimeVetorString (populacao, n);
		printf ("\nNova Populacao:\n");
		ajustaNovaPopulacaoNum (populacao, populacao_num, n);
		imprimeVetor(populacao_num, n);
		resultado = achouSolucao (populacao_num, n);
		if (resultado == 0)
		{
			funcaoAdaptacao(populacao_num, resultado_funAdaptacao, n);
		    printf ("Funcao Adaptacao: ");
		    imprimeVetor(resultado_funAdaptacao, n);
			break;
		}
		i++;
	}
	return 0;
}
