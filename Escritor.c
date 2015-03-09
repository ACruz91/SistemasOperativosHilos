/*Prioridad Escritores*/

/*Includes*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

/*Variables Globales*/

#define N 3
#define M 5

int global = 0;
int n_lectores = 0;
int n_escritores = 0;

/*Semáforos*/

pthread_mutex_t mutex1, mutex2, s_escritor, s_lector;

/*Funciones*/

void lector(int i);
void escritor(int i);

int main(int argc, char const *argv[])
{
	pthread_t lectores[N], escritores [N];
	extern pthread_mutex_t mutex, variable;
	int i,status;
	return 0;
}

