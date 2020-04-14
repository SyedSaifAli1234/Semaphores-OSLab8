#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/shm.h>    
#include <errno.h>
#include <fcntl.h>

char* buffer;
sem_t *sem1;	//EMPTY
sem_t *sem2;    //FULL
sem_t *mutex;	//LOCK

void* Producer(void* param ){
	printf("Inside the producer\n");
	int size = *(int*)param; 
	printf("Size = %d\n", size);
	buffer = (char*) malloc(size * sizeof(char));
	printf("%s\n", buffer);
 //    sem_wait(mutex);
	// // do buffer stuff
 //    printf("sem_wait(mutex) tak fine\n");
	// int i =0;
	// for (i =0; i < size; i++){
	// 	sem_wait(sem1);
	// 	printf("sem_wait(sem1) called\n");
	// 	*buffer[i] = 'a'+i;
	// 	printf("%s\n", *buffer[i]);
 //        sem_post(sem2);
	// }
	// sem_post(mutex);
	pthread_exit(0);
}

void *Consumer(void *param ){
	printf("Hello consumer\n");
	pthread_exit(0);
}







int main(){
	
	pthread_t id1, id2;

	int buff_shm=shmget(990, 1024, 0666 | IPC_CREAT);								//shared memory created for buffer
	if(buff_shm == -1){
		printf("Error!\n");
		return 1;
	}
	buffer = (char*) shmat(buff_shm, NULL, 0);										//shared memory attached for buffer
	if (buffer == -1){																
		printf("Shared memory not created\n");
	}
	printf("Shared memory created for buffer\n");


	int n = 0;
	printf("Input N : ");
	scanf("%d", &n);


	int sem_shm1=shmget(991, 1024, 0666 | IPC_CREAT);								//shared memory created for semaphore
	if(sem_shm1 == -1){
		printf("Error!\n");
		return 1; 
	}
	sem1 = (sem_t*) shmat(sem_shm1, NULL, 0);										//shared memory attached for semaphore
	if (sem1 == -1){																//Sem 1 = EMPTY
		printf("Shared memory not created\n");
	}
	printf("Shared memory created for Sem1\n");
	sem_open("sem1", O_CREAT|O_EXCL, 0644, n);
	sem_unlink("sem1");




	int sem_shm2=shmget(992, 1024, 0666 | IPC_CREAT);								//shared memory created for semaphore
	if(sem_shm2 == -1){
		printf("Error!\n");
		return 1; 
	}
	sem2 = (sem_t*) shmat(sem_shm2, NULL, 0);										//shared memory attached for semaphore
	if (sem2 == -1){																//Sem 2 = FULL
		printf("Shared memory not created\n");
	}
	printf("Shared memory created for Sem2\n");
	sem_open("sem2", O_CREAT|O_EXCL, 0644, 1);
	sem_unlink("sem2");


    mutex = sem_open("mutex", O_CREAT|O_EXCL, 0666, 1);
    sem_unlink("mutex");
    printf("mutex done\n");



	if (pthread_create(&id1, NULL, Producer, &n) < 0) {
    	printf("Thread not created\n");
  	}
  	sleep(1);
	if (pthread_create(&id2, NULL, Consumer, NULL) < 0) {
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
  	shmdt(sem_shm2);
  	shmctl(sem_shm2, IPC_RMID, 0);

  	printf("Shared memory was destroyed\n");

}