#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

// no da arvore
typedef struct estr {
    int chave;
    struct estr *esq;
	struct estr *dir;
} NO;

// no de lista ligada
typedef struct estrL {
    int chave;
    struct estrL *prox;
} NOL;

void inicializar(NO* *raiz) {
    *raiz = NULL;
}

void inicializarLista(NOL* *l) {
    *l = NULL;
}

NO* busca(NO* raiz, int chave, NO** pai){
    *pai = NULL;
    if(!raiz) return NULL;
    NO* p = raiz;
    while(p && p->chave != chave){
        *pai = p;
        if(p->chave > chave) p = p->esq;
        else p = p->dir;
    }
    if(p && p->chave == chave) return p;
    else return NULL;
}

bool inserir(NO* *raiz, int chave){
    NO* pai;
    if(busca(*raiz, chave, &pai)) return false;
    NO* novo = (NO*)malloc(sizeof(NO));
    novo -> chave = chave;
    novo -> esq = NULL;
    novo -> dir = NULL;

    if(!pai) *raiz = novo;
    else{
        if(pai->chave > chave) pai -> esq = novo;
        else pai -> dir = novo;
    }
    return true;
}

void inserirLista(NO* p, NOL* *inicio){
    if(p){
        inserirLista(p->dir, inicio);
        NOL* novo = (NOL*)malloc(sizeof(NOL));
        novo->chave = p->chave;
        novo->prox = *inicio;
        *inicio = novo;
        inserirLista(p->esq, inicio);
    }
}

NOL* final(NOL* l){
    NOL* p = l;
    while(p->prox){
        p = p->prox;
    }
    return p;
}

NOL* pontoMedio(NOL* l, NOL* f){
    int q=0;
    NOL* p = l;
    while (p!=f){
        p = p->prox;
        q++;
    }
    p = l;
    int c = 0;
    while(c<q/2){
        p = p->prox;
        c++;
    }
    return p;
}

void insereMedio(NO* *raiz, NOL* l, NOL* fim){
    NOL* m = pontoMedio(l, fim);
    if(l!=fim){
        inserir(raiz, m->chave);
        insereMedio(raiz, l, m);
        insereMedio(raiz, m->prox, fim);
    }
    if(l==fim){
        inserir(raiz, l->chave);
    }
}

NO* copiaCompleta(NO* raiz) {
    NO* resp;
    inicializar(&resp);

	NOL* l;
    inicializarLista(&l);
    inserirLista(raiz, &l);
    NOL* fim = final(l);

    insereMedio(&resp, l, fim);
    return resp;
}

int main() {

}

