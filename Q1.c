#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <stdlib.h>


// Create the shared memory segment or use an already created shared memory segment (shmget())

// Attach the process to the already created shared memory segment (shmat())

// Detach the process from the already attached shared memory segment (shmdt())

// Control operations on the shared memory segment (shmctl())


//int shmget(key_t key, size_t size, int shmflg)
int shmget(121212, 1024, )