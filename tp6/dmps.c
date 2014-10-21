#include "drive.h"

static void empty_it(){
    return;
}


int main(int argc, char* argv[]){

  unsigned int cylinder, sector;
  unsigned char* buffer = malloc(HDA_SECTORSIZE);
  unsigned char* buffer2 = malloc(HDA_SECTORSIZE);
  int i;

  if(argc!=3 || (argc>1  && strcmp(argv[1], "-h")==0) ){
    printf("Usage:\n");
    printf("\t$dmps cylindre secteur\n");
    exit(EXIT_SUCCESS);
  }

  cylinder = atoi(argv[1]);
  sector = atoi(argv[2]);

  /* init hardware */
  if(!init_hardware("hardware.ini")){
    perror("Initialization error\n");
    exit(EXIT_FAILURE);
  }

  /* Interreupt handlers */
  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);

  buffer = "Bonjours le monde";
  write_sector_n(cylinder, sector, buffer, 8);
  read_sector_n(cylinder, sector, buffer2, 8);

  if(!buffer){
    perror("Couldn't read hardware\n");
    exit(EXIT_FAILURE);
  } 

  printf("%s\n", buffer2);

  free(buffer);

  exit(EXIT_SUCCESS);
}
