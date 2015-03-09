/*Problema de los Filósofos*/

/*Includes*/

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/*Variables Globales*/

#define N 5						/*Número de Filósofos*/
#define IZQUIERDA(x)			(((x)>0) ? (x)-1 : N-1)
#define DERECHA(x)				(((x)+1)%N)

/*Enumeración*/

typedef enum{
	Pensando,Hambriento,Comiendo
}estados;

estados vector[N];

/*Semáforos*/

sem_t mutex; 
sem_t s[N];

/*Funciones*/

void filosofo(int i);
void cogerTenedores(int i);
void soltarTenedores(int i);
void comprobar(int i);

/*Main*/

int main(int argc, char const *argv[])
{
	int i,status;
	pthread_t Filosofo[N];

	/*Inicialización de los Semáforos*/

	for (i = 0; i < N; ++i)
		sem_init(&s[i],0,0);
	
	sem_init(&mutex,0,1);

	/*Inicialización de las Variables*/

	for (i = 0; i < N; i++)
		vector[N]= Pensando;
	

	/*Creación de las Hebras*/

	for (i = 0; i < N; i++){
		if((status = pthread_create(&Filosofo[i],NULL,(void *)filosofo,(void *)i)))
			exit(status);
	}

	for (i = 0; i < N; i++)
		pthread_join(Filosofo[i],NULL);
	

	return 0;
}

void filosofo(int i){
	/*El Filósofo solo hace coger tenedores y soltar tenedores*/

	/*Pensar*/
	printf("El Filósofo %d está Pensando\n",i);
	sleep(3);

	cogerTenedores(i);

	/*Comer*/
	printf("El Filósofo %d está Comiendo\n",i);
	sleep(3);

	soltarTenedores(i);
}
void cogerTenedores(int i){
	
	sem_wait(&mutex);
		vector[i] = Hambriento;
		comprobar(i);
	sem_post(&mutex);
	sem_wait(&s[i]);
}

void comprobar(int i){

	if( vector[i] == Hambriento && vector[IZQUIERDA(i)] != Comiendo && vector[DERECHA(i)] != Comiendo){
		vector[i] = Comiendo;
		sem_post(&s[i]);
	}
}

void soltarTenedores(int i){

	sem_wait(&mutex);
		vector[i] = Pensando;
		comprobar(IZQUIERDA(i));
	comprobar(DERECHA(i));
	sem_post(&mutex);
}

