#include <sdtio.h>
#include <stdlib.h>


/**
 * La fonction bar ne fait oas grand chose,
 * exemple pour afficher la pile des variables.
 */
char bar(int index){

  char string[50] = "bonjour";
  int indexbis = 0;

  if (index<0 || index>50){
    indexbis =0;
  } else {
    indexbis = index++;
  }

  return string[indexbis];
}

/**
 * La fonction foo ne fait oas grand chose,
 * exemple pour afficher la pile des variables.
 */
int foo(int x, char c){

  int a = 42;
  int i = 0;

  char bares = bar(i);

  return (int)c + x - a;
}


int main(int argc, char* argv[]){

  int x = 50;
  int c = 'a';

  return foo(x,c);
}
