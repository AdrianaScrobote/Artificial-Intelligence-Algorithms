//Autora: Adriana Scrobote

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>   
#include <math.h>

#define n 100

int qtd_linhas, qtd_posicao;


/* Aloca qualquer matriz de float */
float** alocarMatriz(int Linhas, int Colunas)
{ 
  int i,j; 
 
  float **m = (float**)malloc(Linhas * sizeof(float*)); //Aloca um Vetor de Ponteiros
 
  for (j = 0; j < Linhas; j++)
  { //Percorre as linhas do Vetor de Ponteiros
       m[j] = (float*) malloc(sizeof(float) * Colunas); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
       for (i = 0; i < Colunas; i++){ //Percorre o Vetor de Inteiros atual
            m[j][i] = 0; //Inicializa com 0
       }
  }
return m; //Retorna o Ponteiro para a Matriz Alocada
}



/* Aloca qualquer matriz de inteiros */
int** alocarMatrizInteiros(int Linhas, int Colunas)
{ 
  int i,j; //Variáveis Auxiliares
 
  int **m = (int**)malloc(Linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros
 
  for (j = 0; j < Linhas; j++)
  { //Percorre as linhas do Vetor de Ponteiros
       m[j] = (int*) malloc(sizeof(int) * Colunas); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
       for (i = 0; i < Colunas; i++){ //Percorre o Vetor de Inteiros atual.
            m[j][i] = 0; //Inicializa com 0.
       }
  }
return m; //Retorna o Ponteiro para a Matriz Alocada
}



/* Imprime qualquer matriz de float */
void imprimirMatriz(int Linhas, int Colunas, float **m)
{ 
  int i,j; 
 
  for (j = 0; j < Linhas; j++)
  { 
       for (i = 0; i < Colunas; i++){ 
            printf ("%.2f ", m[j][i]);
       }
       printf ("\n");
  }
  printf ("\n");
}


/* Imprime qualquer matriz de inteiros */
void imprimirMatrizInteiros(int Linhas, int Colunas, int **m)
{ 
  int i,j;
 
  for (j = 0; j < Linhas; j++)
  { 
       for (i = 0; i < Colunas; i++){ 
            printf ("%d ", m[j][i]); 
       }
       printf ("\n");
  }
  printf ("\n");
}


/* Calcula distancias dos pontos */
void calcularDistancia (float **matriz, int vertice_a_colocar, float * distancias)
{
	int i = 0, j = 0;
	float distancia = 0;
	for (; j < qtd_linhas; j++)
	{
		if ( j != vertice_a_colocar)
		{	
			for (; i < qtd_posicao; i++)
			{
				distancia += (matriz[vertice_a_colocar][i] - matriz[j][i]) * (matriz[vertice_a_colocar][i] - matriz[j][i]);
			}
			distancias[j] = sqrt(distancia);
			distancia = 0;
			i = 0;
		}
		else 
			distancias[j] = 0;
	}
	
}


/* Imprime qualquer vetor de float */
void imprimirVetor (float * vetor)
{
	int i = 0;
	for (; i < qtd_linhas; i++)
		printf ("%.2f ", vetor[i]);
	printf ("\n");
}


/* Imprime qualquer vetor de inteiros */
void imprimirVetorInteiros (int * vetor, int linhas)
{
	int i = 0;
	for (; i < linhas; i++)
		printf ("%d ", vetor[i]);
	printf ("\n");
}


/* Encontra menores distancias dos pontos */
int achaMenor (float * vetor) 
{
	int i = 0, posicao_menor;
	float menor;
	
	menor = vetor[i];
	while (i < qtd_linhas)
	{
		if(menor == 0)
		{
			i++;
			menor = vetor[i];
		}
		else
		{
			posicao_menor = i;
			break;
		}
	}
			
	for (i = i + 1; i < qtd_linhas;)
	{
		if (vetor[i] != 0)
		{
			if (menor > vetor[i])
			{
				menor = vetor[i];
				posicao_menor = i;
			}
			else if (menor == vetor[i])
				i++;
			else i++;
		}
		else i++;			
	}
	vetor[posicao_menor] = 0;
	return posicao_menor;
}


/* Carrega arquivo em matriz */
float** carregarArquivo (char * arquivo_abrir)
{
	int i = 0, j, ac = 0, al = 0;
	float c;
	char dados[n];
	char valor[4];
	
	FILE * arquivo = NULL;
	
	qtd_linhas = 0;
	qtd_posicao = 0;
	
	arquivo = fopen (arquivo_abrir, "rb");
	if (arquivo == NULL)
	{
		printf("Nao achei o arquivo!\n");
		return NULL;
	}
		
	/* Acha quantas linhas */
	while ( (fgets(dados, n, arquivo)) != NULL  )
    {    	
    	qtd_linhas++;
    }
   	
	/* Acha quantas colunas */
	while(dados[i] != '\0')
	{
		if (isspace(dados[i]) != 0)
			qtd_posicao++;
		i++;
	}
	qtd_posicao++;
	
	float **matriz;
	
	matriz = alocarMatriz(qtd_linhas, qtd_posicao);
	
	// Coloca os elementos na matriz 
	fseek(arquivo, 0, SEEK_SET);
    while ( al < qtd_linhas )
    {   
    	i = 0;
		j = 0; 
    	(fgets(dados, n, arquivo));	
    	while(dados[i] != '\0')
		{
			if (isspace(dados[i]) == 0)
			{
				valor[j] = dados[i];
				j++;
				i++;
			}
			else 
			{
				valor[j] = '\0';
				c = atof(valor);
				matriz[al][ac]= c;
				ac++;
				i++;
				j = 0;
			}
		}
    	al++;
    	ac = 0;	
    }
	 fclose (arquivo);
	 return (&(*matriz));
}


/* Verifica pontos (vertices) marcados */
int verificaMarcados(int * marcados)
{
	int i = 0;
	for (; i < qtd_linhas; i++)
	{
		if (marcados[i] != 1)
			return 0;
	}
	return 1;
}


/* Funcao KNN */
void KNN(float ** matriz, float * distancias, int * marcados, int * classificacao, int k, int ** matriz_confusao, int posicao)
{
	if (verificaMarcados(marcados) == 0)
	{
		int i, menor, analise1 = 0, analise2 = 0, classificacao_final;
		
		
		for (i = 0; i < k; i++)
		{
			classificacao[i] = 0;
		}
		srand (time(NULL));
		int vertice_a_colocar = rand() % qtd_linhas; 
		while (marcados[vertice_a_colocar] != 0)
		{
			srand (time(NULL));
			vertice_a_colocar = rand() % qtd_linhas;
		}
		marcados[vertice_a_colocar] = 1;
		
		printf ("vertice_a_colocar: %d\n", vertice_a_colocar);
		
		calcularDistancia(&(*matriz), vertice_a_colocar, distancias);
		printf("Distancias:\n");
		imprimirVetor(distancias);
		for (i = 0; i < k; i++)
		{
			menor = achaMenor(distancias);
			classificacao[i] = menor;
		}
		printf("Vertices marcados:\n");
		imprimirVetorInteiros(marcados, qtd_linhas);
		printf("Indice das menores distancias escolhidas:\n");
		imprimirVetorInteiros(classificacao, k);
		
		for (i = 0; i < k; i++)
		{
			if (matriz[classificacao[i]][posicao-1] == 1)
				analise1++;
			else 
				analise2++;
			
		}
		if (analise1 > analise2)
			classificacao_final = 1;
		else
			classificacao_final = 0;
		printf ("classificacao: %d\n\n", classificacao_final);
		
		if (matriz[vertice_a_colocar][posicao-1] == 0)
		{
			if (classificacao_final == 0)
				matriz_confusao[0][0] += 1;
			else
				matriz_confusao[0][1] += 1;
		}
		else
		{
			if (classificacao_final == 1)
				matriz_confusao[1][1] += 1;
			else
				matriz_confusao[1][0] += 1;
		}
		KNN(&(*matriz), distancias, marcados, classificacao, k, &(*matriz_confusao), posicao);
	}
	else
	{
		return;
	}
		
}


/* Funcao principal */
int main()
{	
	float **matriz;
	int **matriz_confusao;
	char arquivo_abrir[n];	
	printf ("Digite o nome do arquivo que possui sua base de dados:\n");
	scanf("%s", &arquivo_abrir);
	matriz = carregarArquivo(arquivo_abrir);
	if (matriz == NULL)
		return 0;
	matriz_confusao = alocarMatrizInteiros(2, 2);
	float distancias[qtd_linhas];
	int marcados[qtd_linhas];
	int k;
	printf("Digite o valor de k desejado:\n");
	scanf("%d", &k);
	if (k < 1)
	{
		printf("Voce digitou um valor invalido!\n");
		return 0;
	}
	int classificacao[k];
	int i;
	for (i = 0; i < qtd_linhas; i++)
	{
		distancias[i] = 0;
		marcados[i] = 0;
	}
	
	KNN (matriz, distancias, marcados, classificacao, k, matriz_confusao, qtd_posicao);
	printf("Matriz de Confusao:\n");
	imprimirMatrizInteiros(2, 2, &(*matriz_confusao));
	    
	return 0;
}











