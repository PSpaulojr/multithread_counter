#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define NMAX         64
#define N_THREADS    4

unsigned int verifica_primo (unsigned int N);
void* funcao_thread(void *arg);

pthread_mutex_t trava;

unsigned int vetor_numeros[NMAX];
int qntd_numeros = 0;
int abrir_threads = 0;
int qntd_primos = 0;

int main () {

  int thread_args[N_THREADS];

  for(int b = 0; b < NMAX; b++) {   /*forma de 'zerar' meu vetor que tem os numeros a serem analisados*/
    vetor_numeros[b] = 0;
  }
  
  while(scanf("%u ", &vetor_numeros[qntd_numeros]) != EOF ){  /*Conto quantos numeros que precisaram ser analisados*/
    qntd_numeros++;
  }

  pthread_t threads[4];
  
  if (qntd_numeros > 4){
    abrir_threads = 4;
  }
  else{
    abrir_threads = qntd_numeros;
  }
  
/* Inicializo minhas threads */

  for (int i = 0; i < (abrir_threads) ; i++) {
    thread_args[i] = i;
    pthread_create(&(threads[i]), NULL, funcao_thread, &(thread_args[i]) );
  }

/*Espero minha threads finalizarem */

  for (int i = 0; i < abrir_threads; i++) {
    pthread_join(threads[i], NULL);
  }

/*Imprimo resultado final*/

  printf("%d\n", qntd_primos);

  return 0;
}

void* funcao_thread(void *arg) {
  int* N = (int*)arg;
  int M = (*N);

  for( int k = M ; k  < qntd_numeros ; k += N_THREADS ){
    pthread_mutex_lock(&trava);
    qntd_primos += verifica_primo( vetor_numeros[k] );
    pthread_mutex_unlock(&trava);
  }
  return 0;
}

unsigned int verifica_primo (unsigned int N){
  int divisores = 0;
  int ehprimo = 0;
  
  for (unsigned int i = 1; i <= N; i++) {
    if (divisores > 3){
      break;
    }

    if (N % i == 0) { 
     divisores++;
    }
  }

  if (divisores == 2){
    ehprimo = 1;
  }

  return ehprimo;
}
