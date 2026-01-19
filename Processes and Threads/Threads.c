#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errors.h"
#include <string.h>

//Processo a ser executado por cada thread
void* processo(){
  printf("hello world \n");
}

int main() {
  
  //Criação e inicialização de cada thread com encerramento em caso de erro
  pthread_t tid_1, tid_2, tid_3, tid_4;
  if(pthread_create(&tid_1, NULL, &processo, NULL) != 0){
      printf("Erro de criação de thread \n%d\n", errno);
      exit(EXIT_FAILURE);
  }
  if(pthread_create(&tid_2, NULL, &processo, NULL) != 0){
      printf("Erro de criação de thread \n%d\n", errno);
      exit(EXIT_FAILURE);
  }
  if(pthread_create(&tid_3, NULL, &processo, NULL) != 0){
      printf("Erro de criação de thread \n%d\n", errno);
      exit(EXIT_FAILURE);
  }
  if(pthread_create(&tid_4, NULL, &processo, NULL) != 0){
      printf("Erro de criação de thread \n%d\n", errno);
      exit(EXIT_FAILURE);
  }

  //Execução de cada thread e espera pela execução das outras através da junção, encerra em caso de erro 
  if(pthread_join(tid_1, NULL) != 0){
    printf("Erro de junção de thread \n%d\n", errno);
      exit(EXIT_FAILURE);
  }
  if(pthread_join(tid_2, NULL) != 0){
    printf("Erro de junção de thread \n%d\n", errno);
      exit(EXIT_FAILURE);
  }
  if(pthread_join(tid_3, NULL) != 0){
    printf("Erro de junção de thread \n%d\n", errno);
      exit(EXIT_FAILURE);
  }
  if(pthread_join(tid_4, NULL) != 0){
    printf("Erro de junção de thread \n%d\n", errno);
      exit(EXIT_FAILURE);
  }
  
  return 0;
}