//Larissa Terto Alvim
//Nº USP: 13671765

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "grafo_listaadj.h"
//#include "grafo_matrizadj.h"

void exit(int status);

//Heaps
typedef struct vertice{
    int indice;
    int chave;
}VERTICE;

typedef struct heap{
    VERTICE* A;
    float chaves[MAXV];
    int tamanhoDoHeap;
 }HEAP;

void refazHeapMax(HEAP* h, int i){
    int n = h->tamanhoDoHeap;
    int esq, dir, maior;
    esq = 2*i;
    dir = 2*i + 1;
    if (esq<n && h->A[esq].chave > h->A[i].chave) maior = esq;
    else maior = i;
    if (dir<n && h->A[dir].chave > h->A[maior].chave) maior = dir;
    if(maior!=i){
        VERTICE aux = h->A[i];
        h->A[i] = h->A[maior];
        h->A[maior] = aux;
        refazHeapMax(h, maior);
    }
}

void constroiHeapMax(HEAP* h, float* chaves){
    int n = h->tamanhoDoHeap;
    for(int i = (n/2) - 1; i>=0; i--){
        refazHeapMax(h, i);
    }
}

void aumentaChave(float* chave, int i, HEAP* h){
    int pai = (i-1)/2;
    while(i > 0 && chave[h->A[i].indice] > chave[h->A[pai].indice]){
        VERTICE aux = h->A[i];
        h->A[i] = h->A[pai];
        h->A[pai] = aux;
        i = pai;
        pai = (i-1)/2;
    }
}

int extraiHeap(HEAP* h) {
    int resp;
    if(h->tamanhoDoHeap<=0){
        fprintf(stderr, "ERRO: Heap vazio");
    }
    resp = h->A[0].indice;
    h->A[0] = h->A[h->tamanhoDoHeap-1];
    h->tamanhoDoHeap--;
    refazHeapMax(h, 0);
    return resp;
}

void insereHeap(Grafo* g, HEAP* h, int w, float* chaves){
    VERTICE* vertice = malloc(sizeof(VERTICE));
    vertice->chave = chaves[w];
    vertice->indice = w;
    int i = h->tamanhoDoHeap;
    h->A[i] = *vertice;
    h->tamanhoDoHeap++;
    aumentaChave(chaves, i, h);
}

HEAP criaHeap(Grafo* g, float* chaves){
    HEAP h;
    h.tamanhoDoHeap = 0;
    h.A = (VERTICE*)malloc(MAXV * sizeof(VERTICE));
    for(int i = 0; i<g->numV; i++){
        insereHeap(g, &h, i, chaves);
    }
    return h;
}

//Algoritmos
void visitaBP(int i, Grafo* g, int* cor, int* ant){
    int u;
    cor[i] = 1;
    Apontador atual = recebePrimeiro(g, i);
    while(atual!=V_INVALIDO){
        u = recebeV(atual);
        if(cor[u]==0){
            ant[u] = i;
            visitaBP(u, g, cor, ant);
        }
        atual = recebeProx(g, i, atual);
    }
    cor[i] = 2;
}

void buscaP(Grafo* g, int* ant, int raiz){
    int cor[g->numV];
    for(int i = 0; i<g->numV; i++){
        cor[i] = 0;
        ant[i] = -1;
    }
    visitaBP(raiz, g, cor, ant);
}

void mst(int* ant, Grafo* t, float* chave) {
    for(int j = 0; j< t->numV; j++){
        if(ant[j]!=-1) insereAresta(ant[j], j, chave[j], t);
    }
}

void Prim(Grafo* g, int* ant, float* chave, int raiz, Grafo* t){
    int u, v;
    float peso;
    bool pertence[g->numV];
    for(int i = 0; i<g->numV; i++){
        ant[i] = -1;
        chave[i] = 0;
        pertence[i] = false;
    }
    chave[raiz] = MAXV;
    HEAP h = criaHeap(g, chave);
    inicializaGrafo(t, g->numV);
    while(h.tamanhoDoHeap>0){
        u = extraiHeap(&h);
        Apontador atual = recebePrimeiro(g, u);
        while(atual!=V_INVALIDO){
            v = recebeV(atual);
            peso = recebePeso(g, u, v);
            if(pertence[v]==false && chave[v]<peso){
                ant[v] = u;
                chave[v] = peso;
                aumentaChave(chave, v, &h);
            }
            atual = recebeProx(g, u, atual);
        }

        pertence[u] = true;
    }
    mst(ant, t, chave);
}

float caminho(Grafo* g, int v1, int v2, int* ant){
    float aresta = 99.0;
    int atual = v2;
    buscaP(g, ant, v1);
    while(atual!=v1 && ant[atual]!=-1){
        if(recebePeso(g, ant[atual], atual)<aresta) aresta = recebePeso(g, ant[atual], atual);
        atual = ant[atual];
    }
    return aresta;
}

float verificaCaminhao(float n){
    if (n<3.0 && n>=2.5)
        return 2.5;

    else if (n<3.5 && n>=3.0)
        return 3.0;

    else if (n<4.0 && n>=3.5)
        return 3.5;

    else if (n<4.5 && n>=4.0)
        return 4.0;

    else if (n>=4.5)
        return 4.5;

    else return -1;
}

int main(int argc, char** argv){
    if(argc != 2) {
        fprintf(stderr, "ERRO: numero errado de argumentos para a função main");
        exit(0);
    }
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "ERRO: arquivo de entrada não encontrado");
        exit(0);
    }

    int numVertices, numArestas, numConsultas;
    if (fscanf(fp, "%d %d %d\n", &numVertices, &numArestas, &numConsultas) != 3){
        fprintf(stderr, "ERRO: linha de entrada incompleta");
        exit(0);
    }

    Grafo g;
    inicializaGrafo(&g, numVertices);

    int a, b;
    float c;
    for(int i = 0; i<numArestas; i++){
        if (fscanf(fp, "%d %d %f\n", &a, &b, &c) != 3){
            fprintf(stderr, "ERRO: linha de entrada incompleta");
            exit(0);
        }
        insereAresta(a, b, c, &g);
    }


    int ant[g.numV];
    float chave[g.numV];
    Grafo t;
    Prim(&g, ant, chave, 1, &t);

    int v1, v2;
    float aresta, resp;
    FILE *exit;
    exit = fopen("saida.txt", "w");
    for(int i = 0; i<numConsultas; i++){
        if(fscanf(fp, "%d %d\n", &v1, &v2) != 2){
            fprintf(stderr, "ERRO: linha de entrada incompleta");
        }
        float aresta = caminho(&t, v1, v2, ant);
        float resp = verificaCaminhao(aresta);
        fprintf(exit, "%.1f \n", resp);
    }

    fclose(fp);
}
