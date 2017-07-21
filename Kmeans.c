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
return m;
}



/* Aloca qualquer matriz de inteiros */
int** alocarMatrizInteiros(int Linhas, int Colunas)
{ 
  int i,j; 
 
  int **m = (int**)malloc(Linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros
 
  for (j = 0; j < Linhas; j++)
  { //Percorre as linhas do Vetor de Ponteiros
       m[j] = (int*) malloc(sizeof(int) * Colunas); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
       for (i = 0; i < Colunas; i++){ //Percorre o Vetor de Inteiros atual.
            m[j][i] = 0; //Inicializa com 0.
       }
  }
return m; 
}



/* Imprime qualquer matriz de float */
void imprimirMatriz(int Linhas, int Colunas, float **m)
{ 
  int i,j; 
 
  for (j = 0; j < Linhas; j++)
  { 
       for (i = 0; i < Colunas; i++)
	   { 
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
       for (i = 0; i < Colunas; i++)
	   { 
            printf ("%d ", m[j][i]); 
       }
       printf ("\n");
  }
  printf ("\n");
}


/* Calcula distancia de todos os pontos com os K pontos sorteados aleatoriamente para iniciar */
void calcularDistanciaInicial (float **matriz, float **matriz_distancias, int * media_inicial, int k)
{
	int i, j, l, vertice_a_colocar;
	float distancia = 0;
	for (l = 0; l < k; l++)
	{
		vertice_a_colocar = media_inicial[l];
		for (j = 0; j < qtd_linhas; j++)
		{
			if ( j != vertice_a_colocar)
			{	
				for (i = 0; i < qtd_posicao; i++)
				{
					distancia += (matriz[vertice_a_colocar][i] - matriz[j][i]) * (matriz[vertice_a_colocar][i] - matriz[j][i]);
				}
				matriz_distancias[l][j] = sqrt(distancia);
				distancia = 0;
			}
			else 
				matriz_distancias[l][j] = 0;
		}
	}
	
	
}



/* Calcula distancia de todos os pontos com os K pontos de media dos conjuntos */
void calcularDistancia (float **matriz, float **matriz_distancias, float ** matriz_medias, int k)
{
	int i, j, l, vertice_a_colocar;
	float distancia = 0;
	for (l = 0; l < k; l++)
	{
		for (j = 0; j < qtd_linhas; j++)
		{
				for (i = 0; i < qtd_posicao; i++)
				{
					distancia += (matriz_medias[l][i] - matriz[j][i]) * (matriz_medias[l][i] - matriz[j][i]);
				}
				matriz_distancias[l][j] = sqrt(distancia);
				distancia = 0;
		}
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
		
	/* Acha quantidade de linhas */
	while ( (fgets(dados, n, arquivo)) != NULL  )
    {    	
    	qtd_linhas++;
    }
   	
	/* Acha quantidade de colunas */
	while(dados[i] != '\0')
	{
		if (isspace(dados[i]) != 0)
			qtd_posicao++;
		i++;
	}
	qtd_posicao++;
	
	float **matriz;
	
	matriz = alocarMatriz(qtd_linhas, qtd_posicao);
	
	/* Coloca os elementos na matriz */
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



/* Sorteia K pontos iniciais */
int * sorteia_iniciais(int k, int * media_inicial)
{
	int vertice_a_iniciar, existe_vertice_a_iniciar = 0;
	int i = 0, j = 0;
	
	srand (time(NULL));
	for (i = 0; i < k; i++)
	{
	
		vertice_a_iniciar = rand() % qtd_linhas;
		//printf("vertice_a_colocar[%d]: %d\n", i, vertice_a_iniciar);
		for (j = 0; j < k; j++)
		{	if (media_inicial[j] == -1)
				break;
			else if (media_inicial[j] == vertice_a_iniciar)
			{
				existe_vertice_a_iniciar = 1;	
				break;
			}
			else continue;
		}
		if(existe_vertice_a_iniciar == 0)
		{
			media_inicial[i] = vertice_a_iniciar;
		}
		else 
		{
			i--;
			existe_vertice_a_iniciar = 0;
		}
		
	}
}


/* Verifica menores analisando em qual grupo cada ponto vai ficar */
void verificaMenores(float **matriz_distancias, int * menores, int k)
{
	int i, j, menor;
	for (i = 0; i < qtd_linhas; i++)
	{
		menor = 0;
		for (j = 1; j < k; j++)
		{
			if (matriz_distancias[j][i] < matriz_distancias[menor][i])
				menor = j;
		}
		menores[i] = menor;
	}
	printf ("Menores correspondentes a media:\n");
	imprimirVetorInteiros(menores, qtd_linhas);
}



/* Calcula media de todos grupos a partir de todos os pontos agrupados nos mesmos */
void calculaMediaMenores(float **matriz, int * menores, float ** matriz_medias, int k)
{
	
	int i, j, l, qtd_menores = 0;
	float media = 0;
	for (l = 0; l < k; l++)
	{
		for (i = 0; i < qtd_posicao; i++)
		{
			for (j = 0; j < qtd_linhas; j++)
			{
				if (menores[j] == l)
				{
							
					media += matriz[j][i];
					qtd_menores++;
				}			
			}
			matriz_medias[l][i] = media/qtd_menores;
			media = 0;
			qtd_menores = 0;
		}
	}
}

/* Copia vetor de menores (agrupamento) para possivel comparação mais tarde */
void copiarMenoresAntigos(int * menores, int * copia_menores)
{
	int i;
	for (i = 0; i < qtd_linhas; i++)
	{
		copia_menores[i] = menores[i];
	}	
}


/* Verifica se vetor de menores (agrupamento) antigo é igual vetor de menores (agrupamento) atual.
   Retorna 1 se forem iguais ou 0 se forem diferentes */
int verificarIgualdadeMenoresEMenoresAntigos(int * menores, int * copia_menores)
{
	int i;
	for (i = 0; i < qtd_linhas; i++)
	{
		if (copia_menores[i] != menores[i])
			return 0;
	}
	return 1;	
}



void kmeans (float **matriz, float **matriz_distancias, int * media_inicial, int * menores, int * copia_menores, float ** matriz_medias, int k)
{
	int igualdade;
	calculaMediaMenores(matriz, menores, matriz_medias, k);
	printf("Novos valores pontos (vertices):\n");
	imprimirMatriz(k, qtd_posicao, &(*matriz_medias));
	calcularDistancia (matriz, matriz_distancias, matriz_medias, k);
	printf("Distancias:\n");
	imprimirMatriz(k, qtd_linhas, &(*matriz_distancias));
	copiarMenoresAntigos(menores, copia_menores);
	verificaMenores(matriz_distancias, menores, k);
	igualdade = verificarIgualdadeMenoresEMenoresAntigos(menores, copia_menores);
	if (igualdade == 0)
		kmeans(matriz, matriz_distancias, media_inicial, menores, copia_menores, matriz_medias, k);
	else
	{
		printf("Novos valores pontos (vertices):\n");
	    imprimirMatriz(k, qtd_posicao, &(*matriz_medias));
		return;
	}
}


/* Funcao principal */
int main()
{	
	float **matriz;
	char arquivo_abrir[n];	
	printf ("Digite o nome do arquivo que possui sua base de dados:\n");
	scanf("%s", &arquivo_abrir);
	matriz = carregarArquivo(arquivo_abrir);
	if (matriz == NULL)
		return 0;

	int k;
	printf("Digite o valor de k desejado:\n");
	scanf("%d", &k);
	if (k < 1)
	{
		printf("Voce digitou um valor invalido!\n");
		return 0;
	}
	float **matriz_distancias = alocarMatriz(k, qtd_linhas);
	float ** matriz_medias = alocarMatriz(k, qtd_posicao);
	
	int media_inicial[k];
	int menores[qtd_linhas];
	int copia_menores[qtd_linhas];
	int i = 0, j = 0;
	for (i; i < k; i++)
	{
		media_inicial[i] = -1;
		menores[i] = -1;
		copia_menores[i] = -1;
	}
	for (i = k; i < qtd_linhas; i++)
	{
		menores[i] = -1;
	}
	printf("Vertices sorteados para iniciar:\n");
	sorteia_iniciais(k, media_inicial);
	imprimirVetorInteiros(media_inicial, k);
	calcularDistanciaInicial (matriz, matriz_distancias, media_inicial, k);
	printf("Media inicial:\n");
	imprimirMatriz(k, qtd_linhas, &(*matriz_distancias));
	verificaMenores(matriz_distancias, menores, k);
	kmeans (matriz, matriz_distancias, media_inicial, menores, copia_menores, matriz_medias, k);	    
	return 0;
}











