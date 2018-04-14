/* Nome: Bianca Lima Santos  		Nº USP: 10346811 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#define true 1
#define false 0
#define infinito FLT_MAX/2

typedef int bool;

typedef struct vizinho {
	int vertice;
	double peso;
	struct vizinho *prox;
} VIZINHO;

typedef struct vertice {
	VIZINHO *vizinhos;
} VERTICE;

typedef struct grafo {
	int nVertices;
	int nArestas;
	VERTICE *vertices;
} GRAFO;


/* le o arquivo de entrada e armazena os dados nas entruturas declaradas */
GRAFO* leEntrada(char *nomeEntrada) {
	printf("Arquivo de entrada: %s\n", nomeEntrada);

	FILE *entrada;
	entrada = fopen(nomeEntrada, "r");
	
	// verifica se existe conteudo no arquivo
	if (entrada == NULL){
	    return NULL;
	} 
	// criacao do grafo e atribuicao da quantidade de vertices e arestas
	GRAFO *grafo = (GRAFO*)malloc(sizeof(grafo));
	fscanf(entrada, "%d %d", &grafo->nVertices, &grafo->nArestas);
	// criacao dos vertices
	grafo->vertices = (VERTICE*)malloc((grafo->nVertices) * sizeof(VERTICE));
	
	// varre linha a linha do arquivo e preenche o grafo, os vertices e os vizinhos
	int v1, v2;
	double peso;
	
	for(int i = 0; i < (grafo->nArestas); i++){
		// leitura do arquivo
		fscanf(entrada, "%d %d %lf", &v1, &v2, &peso);
		// cria vertice de v1 para v2
		VIZINHO* vizinho1 = malloc(sizeof(VIZINHO));
		vizinho1->vertice = v2;
		vizinho1->peso = peso;
		vizinho1->prox = grafo->vertices[v1].vizinhos;
		grafo->vertices[v1].vizinhos = vizinho1;
		// cria vertice de v2 para v1
		VIZINHO* vizinho2 = malloc(sizeof(VIZINHO));
		vizinho2->vertice = v1;
		vizinho2->peso = peso;
		vizinho2->prox = grafo->vertices[v2].vizinhos;
		grafo->vertices[v2].vizinhos = vizinho2;
		
	}
	
	fclose(entrada);

	return grafo;
}

void saida(char *nomeSaida, double custoTotalArvore) {
	printf("Arquivo de saida: %s\n", nomeSaida);
	FILE *saida = fopen(nomeSaida, "w");

	fprintf(saida, "%f", custoTotalArvore);
	//  aresta da arvore
}

double executaPrim(GRAFO *grafo) {
	double custoTotalArvore = 0.0;
	bool conjuntoVerticesArvore[grafo->nVertices];
	double custo[grafo->nVertices]; 
	int anterior[grafo->nVertices];

	for (int i=0; i < grafo->nVertices; i++) {
		conjuntoVerticesArvore[i] = false;
		custo[i] = infinito;
		anterior[i] = -1;
	}
	// menor custo, ponto de partida do algoritmo
	custo[0] = 0;

	while(1){
		int u = -1;
		double custoU = infinito;
		for (int i=0; i < grafo->nVertices; i++) {
			if (conjuntoVerticesArvore[i] == false && custo[i] < custoU) {
				custoU = custo[i];
				u = i;
			}
		}
		conjuntoVerticesArvore[u] = true;
		// printf("%d %lf\n", u, custoU);
		if (u == -1)
			// nao tem mais nenhum vertice que nao foi percorrido
			break;

		VIZINHO *vizinho = grafo->vertices[u].vizinhos;
		while(vizinho != NULL) {
			int w = vizinho->vertice;
			if (conjuntoVerticesArvore[w] == false && custo[w] > vizinho->peso) {
				custo[w] = vizinho->peso;
				anterior[w] = u;
			}
			vizinho = vizinho->prox;
		}
	}
	for (int i=0; i < grafo->nVertices; i++) {
		printf("%d %lf %d\n", i, custo[i], anterior[i]);
		custoTotalArvore += custo[i];
	}
	printf("%f",custoTotalArvore);

	return custoTotalArvore;
}

int main(int argc, char **argv) {
	if (argv[1]) {
		GRAFO *grafo = leEntrada(argv[1]);
		double custoTotalArvore = executaPrim(grafo);
		
		if(argv[2]){
			saida(argv[2], custoTotalArvore);
		}
		else{
			printf("Nome do arquivo de saida nao encontrado. \n");
		}
	}
	else {
		printf("Arquivo de entrada nao encontrado. \n");
	}
	
	return 0;
} 
