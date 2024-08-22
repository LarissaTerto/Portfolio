#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

// elemento da lista
typedef struct estr {
        int valor;
        struct estr* prox;
} NO;

// Busca
NO* buscaSeqOrd(int ch, NO* p, NO* *ant) {
    *ant = NULL;
    while(p) {
        if(p->valor >= ch) break;
        *ant = p;
        p = p->prox;
    }
    if(p) {
        if(p->valor == ch) return(p);
    }
    return(NULL);
}

// Inser��o
bool inserir(int ch , NO* p) {
    NO* novo;
    NO* ant;

    novo = buscaSeqOrd(ch, p, &ant);
    if(novo) return(false);
    novo = (NO*) malloc(sizeof(NO));
    novo->valor = ch;

    if(!p) {
        p->valor = novo->valor;
        novo->prox = NULL;
    }
    else {
        if(!ant) {
            novo->prox = p;
            p->valor = novo->valor;
        }
        else {
            novo->prox = ant->prox;
            ant->prox = novo;
        }
    }
    return(true);
}

//fun�ao principal
NO* uniao(NO* p1, NO* p2) {
	NO* resp = NULL;
	if(!p1 && !p2) resp = NULL;

	else {
        resp = (NO*) malloc(sizeof(NO));
        resp->prox = NULL;
        if(p1 && !p2){
            while(p1){
                inserir(p1->valor, resp);
                p1=p1->prox;
            }
        }

        else if(p2 && !p1){
            while(p2){
                inserir(p2->valor, resp);
                p2=p2->prox;
            }
        }

        else if(p1 && p2){
            while(p1 && p2){
                if(p1->valor == p2->valor){
                    inserir(p1->valor, resp);
                    p1 = p1->prox;
                    p2 = p2->prox;
                }
                else {
                    while(p1){
                        inserir(p1->valor, resp);
                        p1 = p1->prox;
                    }
                    while(p2){
                        inserir(p2->valor, resp);
                        p2 = p2->prox;
                    }
                }
            }
        }
	}
	return resp;
}


int main() {

    NO* p1 = NULL;
	NO* p2 = NULL;

    NO* teste = NULL;
	teste = uniao(p1,p2);

    return 0;
}

