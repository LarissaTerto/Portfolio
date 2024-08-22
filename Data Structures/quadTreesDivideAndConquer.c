#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

//Larissa Terto Alvim 13671765

typedef struct{
    int tamanho;
    int brancos;
    int pretos;
} QUADRANTE;

int calculaLog_2(int n){
    int log_n = ceil(log(n)/log(2));
    return (int)(log_n);
}

int verificarCor(int n, int k, int m[k][k], int lininicial, int linfinal, int colinicial, int colfinal, QUADRANTE quad[calculaLog_2(k)+1]){
    int cor, cor1, cor2, cor3, cor4;

    if(n>1){
        cor1 = verificarCor(n/2, k, m, lininicial, lininicial+n/2, colinicial, colinicial+n/2, quad);
        cor2 = verificarCor(n/2, k, m, lininicial+n/2, lininicial+n, colinicial, colinicial+n/2, quad);
        cor3 = verificarCor(n/2, k, m, lininicial, lininicial+n/2, colinicial+n/2, colinicial+n, quad);
        cor4 = verificarCor(n/2, k, m, lininicial+n/2, lininicial+n, colinicial+n/2, colinicial+n, quad);

        if(cor1==cor2 && cor2==cor3 && cor3==cor4 && cor4==1) cor=1;
        else if(cor1==cor2 && cor2==cor3 && cor3==cor4 && cor4==0) cor=0;
        else cor = 2;

        int indice = calculaLog_2(n);
        quad[indice].tamanho = n;
        if(cor==1){
            quad[indice].brancos++;
            quad[indice-1].brancos-=4;
        } else if(cor==0){
            quad[indice].pretos++;
            quad[indice-1].pretos-=4;
        }
    }

    if(n==1){
        cor = m[lininicial][colinicial];
        if(cor==0) quad[0].pretos++;
        else quad[0].brancos++;
        quad[0].tamanho = 1;
    }
    return cor;
}

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    int k = n;
    int log_n = calculaLog_2(n);
    int mat[n][n];

    FILE *arq;
    arq = fopen(argv[2], "r");
    int nelem = 0;
    char elem;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            fscanf(arq, "%c \n", &elem);
            mat[i][j] = (int)elem-48;
        }
    }

    QUADRANTE quad[log_n+1];
    for(int a=0; a<=log_n; a++){
        quad[a].brancos = 0;
        quad[a].pretos = 0;
    }

    verificarCor(n, k, mat, 0, n, 0, n, quad);

    FILE *exit;
    exit = fopen("saida.txt", "w");
    for(int b=log_n; b>=0; b--){
        fprintf(exit, "%dx%d %d %d \n", quad[b].tamanho, quad[b].tamanho, quad[b].brancos, quad[b].pretos);
    }

    fclose(arq);
    fclose(exit);
    return 0;
}
