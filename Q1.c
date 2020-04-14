#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

char* buffer;
sem_t *sem1;
sem_t *sem2;

void *Producer(void *param ){
	printf("Hello producer\n");
}

void *Consumer(void *param ){
	printf("Hello consumer\n");
}


int main(){
	
	pthread_t id1, id2;

	int id_sem=shmget(990, 1024, 0666 | IPC_CREAT);
	if(id_sem == -1){
		printf("Error!\n");
		return 1;
	}

	buffer = (char*) shmat(id_sem, NULL, 0);
	if (buffer == -1){
		printf("Shared memory not created\n");
	}
	printf("Shared memory created\n");


	if (pthread_create(&id1, NULL, & Producer, NULL) < 0) {
    	printf("Thread not created\n");
  	}
	if (pthread_create(&id2, NULL, & Consumer, NULL) < 0) {
    	printf("Thread not created\n");
  	}

  	if (pthread_join(id1, NULL) < 0) {
    	printf("Thread not created\n");
  	}
  	if (pthread_join(id2, NULL) < 0) {
   	 	printf("Thread not created\n");
  	}

  	//shmdt(id_sem);
  	//shmctl(id_sem, IPC_RMID, 0);
  	printf("Shared memory was destroyed\n");

}