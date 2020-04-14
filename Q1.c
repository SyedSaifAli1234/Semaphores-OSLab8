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

	int buff_shm=shmget(990, 1024, 0666 | IPC_CREAT);									//shared memory created
	if(buff_shm == -1){
		printf("Error!\n");
		return 1;
	}

	buffer = (char*) shmat(buff_shm, NULL, 0);										//shared memory attached
	if (buffer == -1){																
		printf("Shared memory not created\n");
	}
	printf("Shared memory created for buffer\n");




	int sem_shm1=shmget(991, 1024, 0666 | IPC_CREAT);									//shared memory created
	if(sem_shm1 == -1){
		printf("Error!\n");
		return 1;
	}

	sem1 = (sem_t*) shmat(sem_shm1, NULL, 0);										//shared memory attached
	if (sem1 == -1){																
		printf("Shared memory not created\n");
	}
	printf("Shared memory created for Sem1\n");


    



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

  	shmdt(buff_shm);
  	shmctl(buff_shm, IPC_RMID, 0);
  	shmdt(sem_shm1);
  	shmctl(sem_shm1, IPC_RMID, 0);

  	printf("Shared memory was destroyed\n");

}