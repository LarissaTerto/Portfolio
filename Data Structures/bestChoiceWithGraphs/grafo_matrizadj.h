#include <stdbool.h>

#define MAXV 100
#define AN -1
#define V_INVALIDO -1

typedef float Peso;
typedef int Apontador;

typedef struct{
    Peso listaAdj[MAXV+1][MAXV+1];
    int numV;
    int numA;
} Grafo;

bool inicializaGrafo(Grafo* g, int nv);
void insereAresta(int v1, int v2, Peso peso, Grafo* g);
int recebeV(Apontador atual);
float recebePeso(Grafo* g, int u, int v);
Apontador recebeProx(Grafo* g, int u, Apontador v);
Apontador recebePrimeiro(Grafo* g, int u);
