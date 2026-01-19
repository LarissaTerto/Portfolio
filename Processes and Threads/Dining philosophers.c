#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

//Declara semáforos mutex global e hashi para cada filósofo, e o booleano de controle se o filósofo já comeu ou não
sem_t mutex;
sem_t hashi[5];
bool comeu[5];

void *filosofo(void *arg) {
    int id = *(int *)arg;
    int time = 0;
    //Enquanto o filósofo não comeu pode entrar no ciclo de pensar e comer
    while (!comeu[id]) {
        //Pensa
        printf("Filósofo %d está pensando.\n", id);
        sleep(2);

        //Obtém mutex para pegar os hashis, vizinho espera pra obter seu hashi, libera o mutex para outro filósofo não vizinho pegar seus hashis
        sem_wait(&mutex);
        sem_wait(&hashi[id]);
        sem_wait(&hashi[(id + 1) % 5]);
        sem_post(&mutex);

        //Come pois obteve os hashi
        printf("Filósofo %d está comendo.\n", id);
        sleep(2); 

        //Termina de comer: larga hashis, vizinho pode obter o seu hashi
        sem_post(&hashi[id]);
        sem_post(&hashi[(id + 1) % 5]);

        //Sinal que terminou de comer
        comeu[id] = true;
        printf("Filósofo %d terminou de comer.\n", id);
    }
  return NULL;
}

int main() {
    //Define um conjunto de threads e ids para os filósofos
    pthread_t filosofos[5];
    int ids[5];

    //Inicializa os semáforo mutex e hashi
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < 5; i++) {
        comeu[i] = false;
        sem_init(&hashi[i], 0, 1);
    }

    //Define os ids de 1 a 5 e cria uma thread para cada filósofo
    for (int i = 0; i < 5; i++) {
        ids[i] = i;
        if (pthread_create(&filosofos[i], NULL, filosofo, &ids[i]) != 0) {
            perror("Erro na criação de thread\n");
            exit(EXIT_FAILURE);
        }
    }

    //Executa e espera as threads terminarem
    for (int i = 0; i < 5; i++) {
        if (pthread_join(filosofos[i], NULL) != 0) {
            perror("Erro na junção de thread\n");
            exit(EXIT_FAILURE);
        }
    }

    //Libera os semáforos
    sem_destroy(&mutex);
    for (int i = 0; i < 5; i++) {
        sem_destroy(&hashi[i]);
    }

    printf( "Todos os filósofos terminaram de comer.\n");
  
    return 0;
}
