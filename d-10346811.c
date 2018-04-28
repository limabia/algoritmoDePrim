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
	for(int i = 0; i < (grafo->nVertices); i++) {
		grafo->vertices[i].vizinhos = NULL;
	}
	
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

void saida(char *nomeSaida, double custo[], int anterior[], int n) {
	printf("Arquivo de saida: %s\n", nomeSaida);
	FILE *saida = fopen(nomeSaida, "w");
	
	// soma custo total da nova arvore de acordo com os custos obtidos 
	double custoTotalArvore = 0.0;
	for (int i=0; i < n; i++) {
		custoTotalArvore += custo[i];
	}

	// adc ao arquivo o custo total da arvore geradora minima 
	fprintf(saida, "%lf\n", custoTotalArvore);
	
	// adc as arestas da arvore ao arquivo, excluindo o anterior a raiz
	for(int i = 1; i < n; i++) {
		fprintf(saida, "%d %d\n", anterior[i], i);
	}

	fclose(saida);

}

void executaPrim(GRAFO *grafo, double custo[], int anterior[]) {
	bool conjuntoVerticesArvore[grafo->nVertices];

	// inicializa as variaveis
	for (int i=0; i < grafo->nVertices; i++) {
		conjuntoVerticesArvore[i] = false;
		custo[i] = infinito;
		anterior[i] = -1;
	}

	// menor custo, ponto de partida do algoritmo
	custo[0] = 0;

	// ja que a condicao de parada do while eh quando u == -1 
	while(1){
		int u = -1;
		double custoU = infinito;
		// encontra o vertice de menor custo entre os vertices que ainda nao estao na nova arvore
		for (int i=0; i < grafo->nVertices; i++) {
			if (conjuntoVerticesArvore[i] == false && custo[i] < custoU) {
				custoU = custo[i];
				u = i;
			}
		}
		// nao tem mais nenhum vertice que nao foi percorrido
		if (u == -1)
			break;

		// adiciona o vertice a arvore
		conjuntoVerticesArvore[u] = true;
		// pega a lista de vizinhos do vertice adicionado a nova arvore
		VIZINHO *vizinho = grafo->vertices[u].vizinhos;
		/* para cada vizinho dessa lista verifica se existe uma aresta de melhor custo para chegar nele
		dado que ele ainda nao foi adicionado a nova arvore */ 
		while(vizinho != NULL) {
			int w = vizinho->vertice;
			if (conjuntoVerticesArvore[w] == false && custo[w] > vizinho->peso) {
				custo[w] = vizinho->peso;
				anterior[w] = u;
			}
			vizinho = vizinho->prox;
		}
	}
}

void liberaGrafo(GRAFO *grafo){
	// libera as memorias alocadas para uso do grafo
	for(int i= 0; i < grafo->nVertices; i++){
		VIZINHO *viz = grafo->vertices[i].vizinhos;
		VIZINHO *vizProx;
		while(viz != NULL){
			vizProx = viz->prox; 
			free(viz);
			viz = vizProx;
		}
	}
	free(grafo->vertices);
	free(grafo);
}

int main(int argc, char **argv) {
	// se existe arquivo de entrada o le, executa o algoritmo de prim e imprime a saida
	if (argc == 3) {
		GRAFO *grafo = leEntrada(argv[1]);
		if (grafo != NULL) {	
			double custo[grafo->nVertices]; 
			int anterior[grafo->nVertices];
			
			executaPrim(grafo, custo, anterior);
			saida(argv[2], custo, anterior, grafo->nVertices);
		} else {
			printf("Arquivo de entrada nao encontrado, tente novamente. \n");
		}
		liberaGrafo(grafo);
	} else {
		printf("Numero de argumentos errado. \n");
	}
	
	return 0;
} 
