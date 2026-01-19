#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <stdbool.h>
#include "errors.h"
#include <string.h>

volatile bool loop;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int vez = 0;
int count = 0;

void* secao_critica(){
    pthread_mutex_lock(&mutex);
    count += 1;
    pthread_mutex_unlock(&mutex);
}

void* processo_zero(){
    int meu_id = 0;
    int outro = 1;
    loop = true;
    while(loop){
        while (vez != meu_id);
        secao_critica(count);
        vez = outro;
        printf("Fim do processo 0 \n");
        loop = false;
    }
    pthread_exit(NULL);
}

void* processo_um(){
    int meu_id = 1;
    int outro = 0;
    loop = true;
    while(loop){
        while (vez != meu_id);
        secao_critica(count);
        vez = outro;
        printf("Fim do processo 1 \n");
        loop = false;
    }
    pthread_exit(NULL);
}

int main(){

    pthread_t tid_1, tid_2;
    if(pthread_create(&tid_1, NULL, &processo_zero, NULL) != 0){
        printf("Erro de criação de thread \n%d\n", errno);
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&tid_2, NULL, &processo_um, NULL) != 0){
        printf("Erro de criação de thread \n%d\n", errno);
        exit(EXIT_FAILURE);
    }

    if(pthread_join(tid_1, NULL) != 0){
      printf("Erro de junção de thread \n%d\n", errno);
        exit(EXIT_FAILURE);
    }
    if(pthread_join(tid_2, NULL) != 0){
      printf("Erro de junção de thread \n%d\n", errno);
        exit(EXIT_FAILURE);
    }

    printf("Count: %d", count);

    return 0;
}