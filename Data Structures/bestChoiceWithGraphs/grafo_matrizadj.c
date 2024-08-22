#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "grafo_matrizadj.h"

bool inicializaGrafo(Grafo* g, int nv){
    int i, j;
    if(nv>MAXV || nv<=0){
        fprintf(stderr, "ERRO na chamada de inicializaGrafo: numero de vertices deve ser positivo");
        return false;
    }
    g->numV = nv;
    g->numA = 0;
    for(i = 0; i<g->numV; i++){
        for(j = 0; j<g->numV; j++){
            g->listaAdj[i][j] = AN;
        }
    }
    return true;
}

void insereAresta(int v1, int v2, Peso peso, Grafo* g){
    if(v1<0 || v2<0 || v1>MAXV || v2>MAXV){
        fprintf(stderr, "ERRO: vertice invalido");
        return;
    }
    g->listaAdj[v1][v2] = peso;
    g->listaAdj[v2][v1] = peso;
    g->numA++;
}

int recebeV(Apontador atual){
    return atual;
}

float recebePeso(Grafo* g, int u, int v){
    float lu = g->listaAdj[u][v];
    float lv = g->listaAdj[v][u];
    if(lu) return lu;
    else return lv;
}

Apontador recebeProx(Grafo* g, int u, Apontador v){
    if(u<0 || u > MAXV) return V_INVALIDO;
    v++;
    while(v<=g->numV-1 && g->listaAdj[u][v]==AN){
        v++;
    }
    if(v>g->numV) return V_INVALIDO;
    return v;
}

Apontador recebePrimeiro(Grafo* g, int u){
    Apontador atual = recebeProx(g, u, -1);
    return atual;
}
