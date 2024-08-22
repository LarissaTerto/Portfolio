//Larissa Terto Alvim 13671765
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define t 3

typedef int TipoChave;

typedef struct str_no {
    TipoChave chave[2*t-1];
    struct str_no* filhos[2*t];
    int numChaves;
    bool folha;
    struct str_no* irmao;
    struct str_no* pai;
} NO;

typedef struct {
    NO* raiz;
} ArvB;

typedef struct{
	NO* x;
	int i;
} Pair;

bool criaArvoreB(ArvB* T){
    NO* x;
    if(!(x = (NO*) malloc(sizeof(NO)))) {
        printf("ERRO: falha na cria��o da �rvore B");
        return false;
    }
    x->folha = true;
    x->numChaves = 0;
    T->raiz = x;
    x->irmao = NULL;
    return true;
}

Pair* searchParent(NO* raiz, NO* x) {
    Pair* p;
    int i = 0;
    while (i < raiz->numChaves && raiz->filhos[i]->chave[0] < x->chave[0]) {
        i++;
    }

    if (i < raiz->numChaves && raiz->filhos[i] == x) {
        p = (Pair*)malloc(sizeof(Pair));
        p->x = raiz;
        p->i = i;
        return p;
    }

    if (raiz->filhos[i]->folha == true) {
        p = (Pair*)malloc(sizeof(Pair));
        p->x = raiz;
        p->i = i;
        return p;
    }
    else {
        return searchParent(raiz->filhos[i-1], x);
    }

}

Pair* searchBTree(NO* x, TipoChave k) {
    int i = 0;
    while (i < x->numChaves && k > x->chave[i]) {
        i++;
    }
    if (i < x->numChaves && k == x->chave[i]) {
        Pair* p;
        p = (Pair*)malloc(sizeof(Pair));
        p->x = x;
        p->i = i;
        return p;
    }
    if (x->folha == true)
        return NULL;
    else
        return searchBTree(x->filhos[i], k);
}

void insertBTreeNotFull(ArvB* T, NO* x, TipoChave k, bool folha);

NO* splitBTree(NO* x, int i, NO* y) {
    NO* z = (NO*)malloc(sizeof(NO));
    z->folha = y->folha;
    z->irmao = y->irmao;
    y->irmao = z;

    if(z->folha){
        z->numChaves = t;
        for(int a = 0; a<t; a++) {
            z->chave[a] = y->chave[a+t-1];
        }
    }

    if(!z->folha){
        z->numChaves = t-1;
        for (int a = 0; a < t - 1; a++) {
            z->chave[a] = y->chave[a + t];
        }
    }

    if (y->folha == false) {
        for (int b = 0; b<t; b++) {
            z->filhos[b] = y->filhos[b+t];
        }
    }

    y->numChaves = t-1;
    for (int c = x->numChaves; c > i; c--) {
        x->filhos[c+1] = x->filhos[c];
    }
    x->filhos[i+1] = z;

    if(x->chave[i]!=y->chave[t-1]){
        for (int d = x->numChaves - 1; d >= i; d--) {
            x->chave[d+1] = x->chave[d];
        }

        x->chave[i] = y->chave[t - 1];
        x->numChaves++;
    }
    return z;
}

void insertBTree(ArvB* T, NO* x, TipoChave k);

void insertBTreeNotFull(ArvB* T, NO* x, TipoChave k, bool folha) {
    int i;
    if (folha == true) {
        for (i = x->numChaves - 1; i >= 0 && k < x->chave[i]; i--) {
            x->chave[i + 1] = x->chave[i];
        }
        x->chave[i + 1] = k;
        x->numChaves++;

    }
    else {
        for (i = 0; i < x->numChaves && k > x->chave[i]; i++) {
        }
        if (x->filhos[i]->numChaves == 2 * t - 1) {
            splitBTree(x, i, x->filhos[i]);
            if (k > x->chave[i]) {
                i++;
            }
        }
        insertBTreeNotFull(T, x->filhos[i], k, x->filhos[i]->folha);
    }
}

void insertBTree(ArvB* T, NO* x, TipoChave k) {
    if (x->numChaves == 2*t-1) {
        NO* s = (NO*)malloc(sizeof(NO));
        s->folha = false;
        s->filhos[0] = x;
        s->irmao = NULL;
        s->numChaves = 0;
        x->pai = s;
        if(x == T->raiz) T->raiz = s;
        NO* z = splitBTree(s, 0, x);
        if(k<z->chave[0]) {insertBTreeNotFull(T, x, k, x->folha);}
        else {insertBTreeNotFull(T, z, k, z->folha);}
    }
    else {
        insertBTreeNotFull(T, x, k, x->folha);
    }
}

void mergeWithParent(NO* x, NO* esq, NO* dir, int i) {
    for (int a = 0; a < dir->numChaves; a++) {
        esq->chave[t + a] = dir->chave[a];
    }

    if (!esq->folha) {
        for (int b = 0; b <= dir->numChaves; b++) {
            esq->filhos[t + b] = dir->filhos[b];
        }
    }

    for (int c = i+1; c < x->numChaves; c++) {
        x->chave[c - 1] = x->chave[c];
    }

    for (int d = i + 1; d <= x->numChaves; d++) {
        x->filhos[d] = x->filhos[d + 1];
    }

    esq->numChaves += dir->numChaves + 1;
    x->numChaves--;

    free(dir);
}


void merge(NO* x, NO* esq, NO* dir, int i) {
    esq->chave[t-1] = x->chave[i-1];

    for (int a = 1; a < dir->numChaves; a++) {
        esq->chave[t + a] = dir->chave[a];
    }

    if (!esq->folha) {
        for (int b = 0; b <= dir->numChaves; b++) {
            esq->filhos[t + b] = dir->filhos[b];
        }
    }

    esq->numChaves += dir->numChaves;

    for (int c = i; c < x->numChaves; c++) {
        x->chave[c - 1] = x->chave[c];
    }

    for (int d = i + 1; d <= x->numChaves; d++) {
        x->filhos[d - 1] = x->filhos[d];
    }

    x->numChaves--;

    free(dir);
}

void borrowLeft(NO* pai, NO* x, NO* esq, int j) {
    if (pai->chave[j - 1] == x->chave[0]) {
        pai->chave[j - 1] = esq->chave[esq->numChaves - 1];
    }

    for (int a = x->numChaves; a > 0; a--) {
        x->chave[a] = x->chave[a - 1];
    }

    for (int b = x->numChaves + 1; b > 0; b--) {
        x->filhos[b] = x->filhos[b - 1];
    }

    x->chave[0] = esq->chave[esq->numChaves - 1];
    x->numChaves++;

    esq->numChaves--;
}


void borrowRight(NO* pai, NO* x, NO* dir, int j) {
    x->chave[0] = pai->chave[j-1];

    for (int i = 0; i < dir->numChaves; i++) {
        dir->chave[i] = dir->chave[i + 1];
    }

    if (!dir->folha) {
        for (int i = 0; i <= dir->numChaves; i++) {
            dir->filhos[i] = dir->filhos[i + 1];
        }
    }
    x->numChaves++;
}

void borrowParent(NO* pai, NO* x, int j){
    x->chave[0] = pai->chave[j-1];
}

void removeInternal(NO* x, int i, TipoChave k, ArvB* T);
void deleteFromBTree(NO* raiz, NO* x, int i, TipoChave k, ArvB* T);
void deleteTree(ArvB* T, TipoChave k);

void removeLeaf(NO* raiz, NO* x, int i, TipoChave k, ArvB* T) {
    if(x->numChaves>=t){
        for(int j = i+1; j<x->numChaves; j++)
            x->chave[j-1] = x->chave[j];
        x->numChaves--;
    }
    else if(x->numChaves==t-1){
        Pair* pai = searchParent(raiz, x);
        if(pai->x!=NULL){
           int j = pai->i;
           NO* irmaoEsq = pai->x->filhos[j-1];
           NO* irmaoDir = pai->x->filhos[j+1];
           if(irmaoEsq!=NULL){
                if(irmaoEsq->numChaves>t-1) borrowLeft(pai->x, x, irmaoEsq, j);
                else if(irmaoDir!=NULL && irmaoDir->numChaves>t-1) borrowParent(pai->x, x, j);
                else merge(pai->x, irmaoEsq, x, j);
            }
            else if(irmaoDir!=NULL){
                if(irmaoEsq->numChaves>t-1) borrowRight(pai->x, x, irmaoDir, j);
                else if(irmaoEsq!=NULL && irmaoEsq->numChaves>t-1) borrowParent(pai->x, x, j);
                else merge(pai->x, irmaoDir, x, j);
            }
        }
    }
}

void deleteFromBTree(NO* raiz, NO* x, int i, TipoChave k, ArvB* T){
    if(x->folha == true)
        removeLeaf(raiz, x, i, k, T);
    else
        removeInternal(x, i, k, T);
}

void removeInternal(NO* x, int i, TipoChave k, ArvB* T) {
    NO* esq = x->filhos[i];
    NO* dir = x->filhos[i+1];
    if(esq->numChaves > t-1) {
        TipoChave ant = esq->chave[esq->numChaves-1];
        x->chave[i] = ant;
       removeLeaf(T->raiz, esq, esq->numChaves-1, ant, T);
    } else if (dir->numChaves >= t-1 ) {
        TipoChave prox = dir->chave[0];
        if(x->chave[i] == prox && dir->numChaves>t-1) removeLeaf(T->raiz, dir, 0, prox, T);
        else if (x->chave[i] != prox) x->chave[i] = prox;
        else if(esq->numChaves==t-1 && dir->numChaves==t-1){
            mergeWithParent(x, esq, dir, i);
            for(int a = 0; a<esq->numChaves; a++){
                if(esq->chave[a] == k) removeLeaf(T->raiz, esq, a, k, T);
            }
        }
    }
}

void deleteFromRoot(ArvB* T, TipoChave k){
    NO* r = T->raiz;
    Pair* p = searchBTree(r, k);

    if(r->numChaves == 0) return;
    else deleteFromBTree(r, p->x, p->i, k, T);

    if(r->numChaves==0 && r->folha==false){
        T->raiz = r->filhos[0];
        free(r);
    }

    if(r->numChaves==0 && r->folha==true){
        T->raiz = NULL;
        free(r);
    }
}

void deleteTree(ArvB* T, TipoChave k){
    Pair* p = searchBTree(T->raiz, k);
    if(p->x == T->raiz) deleteFromRoot(T, k);
    else if (p->x!=T->raiz) deleteFromBTree(T->raiz, p->x, p->i, k, T);
    Pair* occurency = searchBTree(T->raiz, k);
    if(occurency!=NULL){
        deleteTree(T, k);
    }
}

void printTree(ArvB* T, NO* x, FILE* exit){
    if(x == NULL || (x==T->raiz && x->numChaves == 0)) fprintf(exit, "Vazia");
    else{
        int i = 0;
        fprintf(exit, "(");
        while(i<=x->numChaves-1){
            if(x->folha){
                fprintf(exit, "%d", x->chave[i]);
                if(i!=x->numChaves-1) fprintf(exit, " ");
            } else {
                if(x->filhos[i]!=NULL) printTree(T, x->filhos[i], exit);
                fprintf(exit, " ");
                fprintf(exit, "%d", x->chave[i]);
                if(i!=x->numChaves-1) fprintf(exit, " ");
            }
            i++;
        }
        if(x->folha==false && x->filhos[i]!=NULL){
            fprintf(exit, " ");
            printTree(T, x->filhos[i], exit);
        }
        fprintf(exit, ")");
    }
}

int main(int argv, char** argc) {
    if(argv!=3){
        printf("ERRO: Numero insuficiente de argumentos");
        return 0;
    }
    FILE *arq;
	char op;
	TipoChave k;
	arq = fopen(argc[1],"r");

	if (arq==NULL){
        printf("ERRO: Arquivo de entrada n�o encontrado.");
	}

	else{
        FILE* exit = fopen(argc[2], "w");
        ArvB* T = (ArvB*) malloc (sizeof(ArvB));
        criaArvoreB(T);
        while(op!='f' && !feof(arq)){
            fscanf(arq, "%c", &op);
            if(op =='p'){
                printTree(T, T->raiz, exit);
                fprintf(exit, "\n");
                fscanf(arq, " \n");
            }
            else if(op == 'i'){
                fscanf(arq, "%d \n", &k);
                insertBTree(T, T->raiz, k);
            }
            else if(op == 'r'){
                fscanf(arq, "%d \n", &k);
                deleteTree(T, k);
            }
        }
	}

	fclose(arq);
    return 0;
}

