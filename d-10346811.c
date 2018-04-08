/* Nome: Bianca Lima Santos  		Nº USP: 10346811 */

#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

typedef int bool;


typedef struct vizinho {
	int vertice;
	int peso;
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
void leEntrada() {
	FILE *entrada;
	entrada = fopen("grafo.txt", "r");
	
	// verifica se existe conteudo no arquivo
	if (entrada == NULL){
	    printf("Arquivo nao encontrado. \n");
	    return;
	} 
	// criacao do grafo e atribuicao da quantidade de vertices e arestas
	GRAFO* grafo = (GRAFO*)malloc(sizeof(grafo));
	fscanf(entrada, "%d %d", &grafo->nVertices, &grafo->arestas);
	// criacao dos vertices
	grafo->vertices = (VERTICE*)malloc((grafo->nVertices) * sizeof(VERTICE));
	
	// varre linha a linha do arquivo e preenche o grafo, os vertices e os vizinhos
	int v1, v2;
	double peso;
	for(int i = 0; i < (grafo->nVertices * 2); i++){
		fscanf(entrada, "%d %d %lf", &v1, &v2, &peso);
		printf("%d %d %lf \n", v1, v2, peso );
		VIZINHO* vizinho = malloc(sizeof(VIZINHO));
		vizinho->vertice = v2;
		vizinho->peso = peso;
		vizinho->prox = grafo->vertices[v1].vizinhos;
		grafo->vertices[v1].vizinhos = vizinho;
	}
	fclose(entrada);
}

void saida(){

}


int main() {

	leEntrada();
	return 0;
} 





















/*
o algoritmo recebe um grafo
G = (V, E) e devolve uma árvore T = (S, E0
).
*/