#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#define MAX 100

typedef struct{
    int indice;
    int chave;
} ELEMENTO;

typedef struct heap{
    int t;
    int A[MAX];
    int indices[MAX];
    int tamanhoDoHeap;
 } HEAP;

//CASO 1 LINHAS 12 À 97
int particao(int n, int A[n], int p, int r){
    int aux;
    int x = A[r];
    int i = p - 1;
    for(int j = p; j<=r-1; j++){
        if (A[j] <= x){
            i = i + 1;
            aux = A[i];
            A[i] = A[j];
            A[j] = aux;
        }
    }
    aux = A[i+1];
    A[i+1] = A[r];
    A[r] = aux;
    return (i + 1);
}

int particaoAleatoria(int n, int A[n], int p, int r){
    int deslocamento, i;
    int temp;
    time_t t;
    srand( (unsigned)time(&t) );
    deslocamento = rand() % (r-p+1);
    i = p + deslocamento;
    temp = A[r];
    A[r] = A[i];
    A[i] = temp;
    return particao(n, A, p, r);
}

void quickSort(int n, int A[n], int p, int r){
    if(p<r){
        int q = particaoAleatoria(n, A, p, r);
        quickSort(n, A, p, q-1);
        quickSort(n, A, q+1, r);
    }
}

void organizaIndice(int n, int A[n], int indices[n], ELEMENTO e[n]){
    bool inB[n];
    bool inA[n];
    for(int a = 0; a<n; a++){
        for(int b = 0; b<n; b++){
            if(A[a]==e[b].chave && (!inB[b] && !inA[a])){
                indices[a] = e[b].indice;
                inB[b] = true;
                inA[a] = true;
            }
        }
    }
}

void gulosoCaso1(int n, int A[n], int tempo, int indices[n]){
    FILE *exit;
    exit = fopen("saida1.txt", "w");
    int i = 0, soma = 0, tam = 0;
    int tempoRest = tempo;
    int x;
    int s[tam];
    while(i<n && tempoRest>0){
        x = A[i];
        soma+=x;
        if(soma<=tempo){
            tempoRest-=x;
            tam++;
            s[i] = indices[i];
        }
        i++;
    }
    fprintf(exit, "%d ", tam);
    for(int a = 0; a<tam; a++){
        if(a != tam-1) fprintf(exit, "%d ", s[a]);
        else fprintf(exit, "%d \n", s[a]);
    }
}

void caso1(int n, int A[n], int tempo){
    int indices[n];
    ELEMENTO e[n];
    for(int a = 0; a<n; a++){
         e[a].chave = A[a];
         e[a].indice = a+1;
         indices[a] = a+1;
    }
    quickSort(n, A, 0, n-1);
    organizaIndice(n, A, indices, e);
    gulosoCaso1(n, A, tempo, indices);
}

//CASO 2 LINHAS 100 À 163
void refazHeapMinimo(int n, int A[n], int i){
    int esq, dir, aux, menor;
    esq = 2*i;
    dir = 2*i + 1;
    if (esq<=n && A[esq]<A[i]) menor = esq;
    else menor = i;
    if (dir<n && A[dir]<A[menor]) menor = dir;

    if(menor!=i){
        aux = A[i];
        A[i] = A[menor];
        A[menor] = aux;
        refazHeapMinimo(n, A, menor);
    }
}

void constroiHeapMinimo(int n, int A[n]){
    for(int i = n/2 - 1; i>=0; i--){
        refazHeapMinimo(n, A, i);
    }
}

void heapSort(int n, int A[n]){
    int temp;
    constroiHeapMinimo(n, A);
    for(int i = n; i>=2; i--){
        temp = A[0];
        A[0] = A[i];
        A[0] = temp;
        n--;
        refazHeapMinimo(n, A, i);
    }
}

int acharIndice(HEAP* h, int i){
    int ind = h->tamanhoDoHeap+1;
    for(int a = 0; a<h->tamanhoDoHeap; a++){
        if(h->indices[a] == i){
            ind = a;
        }
    }
    if(ind<h->tamanhoDoHeap) return ind;
}

void decrementaChave(HEAP* h, int i, int chave, int origem){
    int aux, pai;
    int a;
    if(origem==1) a = acharIndice(h, i);
    else if(origem==2) a = i;
    h->A[a] = chave;
    if(chave>h->A[a]) printf("ERRO: nova chave maior que chave atual");
    while(a>1 && h->A[(a-1)/2]>h->A[a]){
        pai = (a-1)/2;
        aux = h->A[a];
        h->A[a] = h->A[pai];
        h->A[pai] = aux;
        a = pai;
    }
    refazHeapMinimo(h->tamanhoDoHeap, h->A, 0);
}

void insereHeap(HEAP* h, int chave){
    h->tamanhoDoHeap++;
    decrementaChave(h, h->tamanhoDoHeap-1, chave, 2);
}

void excluiHeap(HEAP* h, int i) {
    if (h->tamanhoDoHeap > 0) {
        h->A[i] = h->A[h->tamanhoDoHeap-1];
        h->tamanhoDoHeap--;
    }
}

bool solucao(int chave, int tam, int s[tam]){
    for(int a = 0; a<tam; a++){
        if(chave == s[a]) return false;
    }
    return true;
}

void organizaIndiceHeap(HEAP* h, int n, ELEMENTO e[n], int tam, int s[tam]){
    bool inB[n];
    bool inA[h->tamanhoDoHeap];
    bool ok;
    int c = 0;
    for(int a = 0; a<h->tamanhoDoHeap; a++){
        for(int b = 0; b<n; b++){
            if(h->A[a]==e[b].chave && !inB[b] && !inA[a]){
                ok = solucao(e[b].indice, tam, s);
                if(ok){
                    h->indices[a] = e[b].indice;
                    inB[b] = true;
                    inA[a] = true;
                }
            }
        }
    }
}

void gulosoCaso2(HEAP* h, int tempo, int nlin, int at[nlin][3], char atTipo[nlin], ELEMENTO e[h->tamanhoDoHeap]){
    FILE *exit;
    exit = fopen("saida2.txt", "w");
    int n = h->tamanhoDoHeap;
    int cont = 0;
    int i = 0, soma = 0, tam = 0;
    int tempoRest = tempo;
    int x;
    int s[tam];
    while(i<tam+1 && tempoRest>0){
        x = h->A[0];
        soma+=x;
        if(soma<=tempo){
            tempoRest-=x;
            tam++;
            s[i] = h->indices[0];
            fflush(stdout);
            excluiHeap(h, 0);
            refazHeapMinimo(h->tamanhoDoHeap, h->A, 0);
            for(int p = 0; p<h->tamanhoDoHeap; p++) h->indices[p] = h->indices[p+1];      
            refazHeapMinimo(h->tamanhoDoHeap, h->A, 0);
            organizaIndiceHeap(h, n, e, tam, s);
            cont+=x;
        }
        for(int a = 0; a<nlin; a++){
            if(at[a][0]<=cont){
                if(atTipo[a] == 'i'){
                    n++;
                    e[n-1].chave = at[a][2];
                    e[n-1].indice = n;
                    insereHeap(h, at[a][2]);
                    organizaIndiceHeap(h, n, e, tam, s);
                    atTipo[a] = 'x';
                }
                if(atTipo[a] == 'c'){
                    for(int p = 0; p<n; p++){
                        if(e[p].indice == at[a][1]){
                            e[p].chave = at[a][2];
                        }
                    }
                    decrementaChave(h, at[a][1], at[a][2], 1);
                    organizaIndiceHeap(h, n, e, tam, s);
                    atTipo[a] = 'x';
                }
            }
        }
        i++;
        refazHeapMinimo(h->tamanhoDoHeap, h->A, i);
        organizaIndiceHeap(h, n, e, tam, s);
    }
    fprintf(exit, "%d ", tam);
    for(int a = 0; a<tam; a++){ 
        if(a != tam-1) fprintf(exit, "%d ", s[a]);
        else fprintf(exit, "%d \n", s[a]);
    }
}

void caso2(HEAP* h, int tempo, int nlin, int at[nlin][3], char atTipo[nlin]){
    int s[1] = {h->tamanhoDoHeap+1};
    ELEMENTO e[h->tamanhoDoHeap];
    for(int a = 0; a<h->tamanhoDoHeap; a++){
        e[a].chave = h->A[a];
        e[a].indice = a+1;
    }
    heapSort(h->tamanhoDoHeap, h->A);
    organizaIndiceHeap(h, h->tamanhoDoHeap, e, 1, s);
    gulosoCaso2(h, tempo, nlin, at, atTipo, e);
}

int main(int argc, char** argv) {
    bool tempoValido, arqValido;

    int tempo = atoi(argv[1]);
    if(tempo>=14 || tempo<=20) tempoValido = true;
    else printf("Erro: tempo inválido!");

    if(strcmp(argv[3], "entrada1.txt") == 0 || strcmp(argv[3], "entrada2.txt") == 0) arqValido = true;
    else printf("Erro: arquivo inválido!");

    if(tempoValido && arqValido){
        FILE* arq;
        arq = fopen(argv[3], "r");
        int n;
        fscanf(arq, "%d \n", &n);
        int V[n];
        
        if(atoi(argv[2]) == 1){
            for(int i = 0; i<=n; i++){
                if(i>0) {
                    fscanf(arq, "%d \n", &V[i-1]);
                }
             }
            caso1(n, V, tempo);
        }
        else if(atoi(argv[2]) == 2){
            int lin = 0;
            char c;
            FILE* arq2 = fopen(argv[3], "r");
            while((c=fgetc(arq2))!=EOF){
                if(c == 'i' || c == 'c') lin++;
            }
            fclose(arq2);

            char atTipo[lin];
            int at[lin][3];
            for(int i = 0; i<=lin; i++){
                if(i==0){
                    for(int j = 0; j<=n; j++){
                        if(j>0){
                            fscanf(arq, "%d \n", &V[j-1]);
                        }
                    }
                }
                if(i>0){
                    fscanf(arq, "%c %d %d %d \n", &atTipo[i-1], &at[i-1][0], &at[i-1][1], &at[i-1][2]);
                }
            }

            int tamV = sizeof(V)/sizeof(int);
            HEAP* h =(HEAP*)malloc(sizeof(struct heap));
            h->t = MAX;
            h->tamanhoDoHeap = tamV;
            for(int i = 0; i<h->tamanhoDoHeap; i++){
                h->A[i] = V[i];
                h->indices[i] = i;
            }
            caso2(h, tempo, lin, at, atTipo);
        }
        else printf("Erro: caso inválido!");
        fclose(arq);
    }
}

