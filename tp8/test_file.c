#include "inode.h"
#include "ifile.h"
#include "tools.h"

static void empty_it(){
  return;
}

int main(int argc, char**argv){

  unsigned int i;
  unsigned int inumber;
  file_desc_t fd;

  char buf[1024];

  /* init hardware */
  if(!init_hardware(HW_CONFIG)) {
    fprintf(stderr, "Initialization error\n");
    exit(EXIT_FAILURE);
  }

  /* Interreupt handlers */
  for(i=0; i<NB_EMPTY_FUNCTION; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);

  /* chargement du mbr */
  if(!load_mbr()){
    fprintf(stderr, "Erreur lors du chargement du Master Boot Record.\n");
    exit(EXIT_FAILURE);
  }

  /* initialise le super du premier volume */
  init_super(CURRENT_VOLUME);

  /* charge le super du premier volume dans la variable globale */
  load_super(CURRENT_VOLUME);

  /* Test fichier */
  inumber = create_ifile(IT_FILE);
  if(!inumber){
    fprintf(stderr, "Erreur lors de la creation du fichier\n");
  }

  if(open_ifile(&fd, inumber) == RETURN_FAILURE){
    fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
    exit(EXIT_FAILURE);
  }

  if(write_ifile(&fd, "bonjour", 7) == RETURN_FAILURE){
    fprintf(stderr, "Erreur lors de l'ecriture dans le fichier\n");
    exit(EXIT_FAILURE);
  }

  seek2_ifile(&fd, 0); 

  if(read_ifile(&fd, buf, 7) == RETURN_FAILURE){
    fprintf(stderr, "Erreur lors de la lecture dans le fichier\n");
    exit(EXIT_FAILURE);
  }

  flush_ifile(&fd);
  close_ifile(&fd);

  for (i = 0; i < 7; i++) {
    printf("%c", buf[i]);
  }
  printf("\n");


  exit(EXIT_SUCCESS);
}
