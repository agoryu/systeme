#include "mbr.h"

void usage(){
  printf("Utilisation: dvol\n");
  printf("\n");
  printf("Permet d'afficher les volumes");
  printf("\n");
  printf("Exemples:\n");
  printf("\t$dvol\n");
}

int main(int argc, char**argv){

  if(argc!=1){
    usage();
  }
	
  /* chargement du mbr */
  load_mbr();
  if(!load_mbr()){
    perror("Erreur lors du chargement du Master Boot Record.");
    exit(EXIT_FAILURE);
  }

  /* afficher les volumes */
  display_vol();

  exit(EXIT_SUCCESS);
}
