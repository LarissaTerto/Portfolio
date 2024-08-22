#include <stdbool.h>

#define MAXV 100
#define AN NULL
#define V_INVALIDO NULL
typedef float Peso;

typedef struct str_aresta{
    int vdest;
    Peso peso;
    struct str_aresta * prox;
} Aresta;

typedef Aresta* Apontador;

typedef struct{
    Apontador* listaAdj;
    int numV;
    int numA;
} Grafo;

bool inicializaGrafo(Grafo* g, int nv);
void insereAresta(int v1, int v2, Peso peso, Grafo* g);

int recebeV(Apontador atual);
float recebePeso(Grafo* g, int u, int v);
Apontador recebeProx(Grafo* g, int u, Apontador v);
Apontador recebePrimeiro(Grafo* g, int u);
