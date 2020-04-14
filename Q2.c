#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem1;
sem_t sem2;
sem_t sem3;
int i;

void* Print_A (void* b){

    while(1){
      sem_wait(&sem3);
      printf("a");
      sem_post(&sem1);
    }
}

void* Print_B (void* b){

   while(1){
    sem_wait(&sem2);
    printf("b");
    sem_post(&sem3);
	}
}

void *Print_C(void* b){

   while(1){
     sem_wait(&sem1);
     printf("c");
     sem_post(&sem2);
	}
}

int main(){

  pthread_t t1, t2, t3;
  sem_init(&sem2, 0, 0);//b
  sem_init(&sem3, 0, 0);//a
  sem_init(&sem1, 0, 1);//c

  pthread_create(&t1, NULL, &Print_A, NULL);
  pthread_create(&t2, NULL, &Print_B, NULL);
  pthread_create(&t3, NULL, &Print_C, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);

}
