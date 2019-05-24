#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define NMAX         64
#define N_PROCESSOS  4

unsigned int verifica_primo (unsigned int N);
void* funcao_thread(void *arg);

pthread_mutex_t trava;

unsigned int vetor_numeros[NMAX];
int qntd_numeros = 0;
int abrir_threads = 0;
int qntd_primos = 0;
int primos[64];

int main () {

  int thread_args[N_PROCESSOS];

  for(int b = 0; b < NMAX; b++) {   /*forma de 'zerar' meu vetor*/
    vetor_numeros[b] = 0;
  }

  for(int j; j < NMAX; j++ ) {  /*'zero' meu vetor cujo conteudo de cada indice eh 1 ou 0 (primo ou nao) */
    primos[j] = '\0'; 
  }
  
  while(scanf("%u ", &vetor_numeros[qntd_numeros]) != EOF ){
    qntd_numeros++;
  }

  printf("Qntd_numeros:\t%d\n", qntd_numeros);

  pthread_t threads[4];
  
  if (qntd_numeros > 4){
    abrir_threads = 4;
  }
  else{
    abrir_threads = qntd_numeros;
  }
  
  
  for (int i = 0; i < (abrir_threads) ; i++) {
    thread_args[i] = i;
    pthread_create(&(threads[i]), NULL, funcao_thread, &(thread_args[i]) );
  }


  for (int i = 0; i < abrir_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  /* for(int k = 0 ; k  < qntd_numeros ; k += N_PROCESSOS) {
    pthread_mutex_lock(&trava);
    qntd_primos += verifica_primo( vetor_numeros[k] );
    pthread_mutex_unlock(&trava);
    printf("Principal - Numero: %d\tIndice: [%d]\tQntd_Primo %d\n", vetor_numeros[k], k, qntd_primos);
  }
  */

  printf("%d\n", qntd_primos);

  return 0;
}

void* funcao_thread(void *arg) {
  int* N = (int*)arg;
  int M = (*N);

  for( int k = M ; k  < qntd_numeros ; k += N_PROCESSOS ){
    pthread_mutex_lock(&trava);
    qntd_primos += verifica_primo( vetor_numeros[k] );
    printf("Thread %d - Numero: %d\tIndice: [%d]\tQntd_Primo %d\n", M, vetor_numeros[k], k, qntd_primos);
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
