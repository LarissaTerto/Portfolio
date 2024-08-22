#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "grafo_listaadj.h"

bool inicializaGrafo(Grafo* g, int nv){
    if(nv>MAXV){
        fprintf(stderr, "ERRO de inicializacao: Numero de vertices maior que o maximo permitido \n");
        return false;
    }
    if(nv<=0){
        fprintf(stderr, "ERRO de inicializacao: Numero de vertices deve ser positivo \n");
        return false;
    }
    g->numV = nv;
    if(!(g->listaAdj = (Apontador*) calloc(nv, sizeof(Apontador)))){
        fprintf(stderr, "ERRO: Falha na alocacao de memoria \n");
        return false;
    }
    g->numA = 0;
    return true;
}

void insereAresta(int v1, int v2, Peso peso, Grafo* g){
    Apontador p1, p2;
    if(v1<0 || v2<0 || v1>MAXV || v2>MAXV){
        fprintf(stderr, "ERRO: Vertice inválido \n");
        return;
    }
    if(!(p1 = (Apontador) calloc(1, sizeof(Aresta))) || !(p2 = (Apontador) calloc(1, sizeof(Aresta)))){
        fprintf(stderr, "ERRO: Falha na alocacao de memoria na funcao insereAresta \n");
        return;
    }

    p1->vdest = v2;
    p1->peso = peso;
    p1->prox = g->listaAdj[v1];
    g->listaAdj[v1] = p1;
    g->numA++;

    p2->vdest = v1;
    p2->peso = peso;
    p2->prox = g->listaAdj[v2];
    g->listaAdj[v2] = p2;
    g->numA++;
}

int recebeV(Apontador atual){
    return atual->vdest;
}

float recebePeso(Grafo* g, int u, int v){
    Apontador atual = g->listaAdj[u];
    while(atual!=NULL && atual->vdest!=v){
        atual = atual->prox;
    }
    if(atual!=NULL) return atual->peso;
    return -1;
}

Apontador recebeProx(Grafo* g, int u, Apontador v){
    return v->prox;
}

Apontador recebePrimeiro(Grafo* g, int u){
    return g->listaAdj[u];
}
