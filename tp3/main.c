#include "context.h"

#define STACK_SIZE 16384

void f_ping(void *arg);
void f_pong(void *arg);
void f_pang(void *arg);

int main(int argc, char *argv[])
{
  if( ! create_ctx(STACK_SIZE, f_ping, NULL)){
    perror("Erreur creation de context");
    exit(EXIT_FAILURE);
  }
  if( ! create_ctx(STACK_SIZE, f_pong, NULL)){
    perror("Erreur creation de context");
    exit(EXIT_FAILURE);
  }
  if( ! create_ctx(STACK_SIZE, f_pang, NULL)){
    perror("Erreur creation de context");
    exit(EXIT_FAILURE);
  }
  yield();

  printf("\nRetour au main\n");

  if( ! create_ctx(STACK_SIZE, f_ping, NULL)){
    perror("Erreur creation de context");
    exit(EXIT_FAILURE);
  }
  if( ! create_ctx(STACK_SIZE, f_pong, NULL)){
    perror("Erreur creation de context");
    exit(EXIT_FAILURE);
  }
  if( ! create_ctx(STACK_SIZE, f_pang, NULL)){
    perror("Erreur creation de context");
    exit(EXIT_FAILURE);
  }
  yield();

  printf("\nFin du programme dans le main\n");

  exit(EXIT_SUCCESS);
}

void f_ping(void *args)
{

  printf("A") ;
  yield();
  printf("B") ;
  yield();
  printf("C") ;
  yield();

}

void f_pong(void *args)
{
  printf("1") ;
  yield();
  printf("2") ;
  yield();

}

void f_pang(void *args)
{
  printf("a") ;
  yield();
  printf("b") ;
  yield();
  printf("c") ;
  yield();
} 
