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
  start_sched();

  printf("\nRetour au main\n");

  exit(EXIT_SUCCESS);
}

void f_ping(void *args)
{
	  printf("A") ;
	  sleep(2);
	  printf("B") ;
	  sleep(2);
	  printf("C") ;

}

void f_pong(void *args)
{
	  printf("1") ;
	  sleep(2);
	  printf("2") ;
	  sleep(2);
	  printf("3");

}

void f_pang(void *args)
{
	  printf("a") ;
	  sleep(2);
	  printf("b") ;
	  sleep(2);
	  printf("c") ;
} 
