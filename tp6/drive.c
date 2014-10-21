#include "drive.h"


int is_valid_cylinder(unsigned int cylinder){
  if( cylinder<0 || cylinder>=HDA_MAXCYLINDER ){
    perror("Invalid cylinder\n");
    return 0;
  }
  return 1;
}


int is_valid_sector(unsigned int sector){
  if( sector<0   || sector>=HDA_MAXSECTOR ){
    perror("Invalid sector\n");
    return 0;
  }
  return 1;
}


int seek_sector(unsigned int cylinder, unsigned int sector){

  if(!is_valid_cylinder(cylinder) || !is_valid_sector(sector)){
    return 0;
  }


  /* On se position sur le disque dur */
  _out(HDA_DATAREGS, (cylinder>>8 & 0xFF) );
  _out(HDA_DATAREGS+1, (cylinder & 0xFF) );
  _out(HDA_DATAREGS+2, (sector>>8 & 0xFF) );
  _out(HDA_DATAREGS+3, (sector & 0xFF) );

  _out(HDA_CMDREG, CMD_SEEK);
  _sleep(HDA_IRQ);

  return 1;

}


void read_sector(unsigned int cylinder, unsigned int sector, unsigned char* buffer){
  read_sector_n(cylinder, sector, buffer, HDA_SECTORSIZE);
}


void read_sector_n(unsigned int cylinder, 
		   unsigned int sector, 
		   unsigned char* buffer, 
		   size_t n){

  int i;  


  if( !seek_sector(cylinder, sector) ){
    buffer = NULL;
    return;
  }


  /* Mettre dans MASTERBUFFER les donnees a cette emplacement */
  _out(HDA_DATAREGS, 1);
  _out(HDA_CMDREG, CMD_READ);
  _sleep(HDA_IRQ);


  /* exploiter les donnees de MASTERBUFFER */
  for(i=0; i<HDA_SECTORSIZE && i<n; i++){
    buffer[i] = (unsigned char)MASTERBUFFER[i];
  }
}


void write_sector(unsigned int cylinder, unsigned int sector, unsigned char* buffer){
  write_sector_n(cylinder, sector, buffer, HDA_SECTORSIZE);
}


void write_sector_n(unsigned int cylinder, 
		    unsigned int sector, 
		    unsigned char* buffer,
		    size_t n){
  
  int i;

  if( !seek_sector(cylinder, sector) ){
    buffer = NULL;
    return;
  }

  /* ecrire les donnees dans MASTERBUFFER */
  for(i=0; i<HDA_SECTORSIZE && i<n; i++){
    MASTERBUFFER[i] = buffer[i];
  }

  /* Mettre dans le disque les donnees de MASTERBUFFER */
  _out(HDA_DATAREGS, 0);
  _out(HDA_DATAREGS, 1);
  _out(HDA_CMDREG, CMD_WRITE);
  _sleep(HDA_IRQ);

}


void format_sector(unsigned int cylinder, 
		   unsigned int sector, 
		   unsigned int nsector, 
		   unsigned int value){
  
  if( !seek_sector(cylinder, sector) ){
    return;
  }

  _out(HDA_DATAREGS, (nsector>>8 & 0xFF) );
  _out(HDA_DATAREGS+1, (nsector & 0xFF) );
  _out(HDA_DATAREGS+2, (value>>24 & 0xFF) );
  _out(HDA_DATAREGS+3, (value>>16 & 0xFF) );
  _out(HDA_DATAREGS+4, (value>>8 & 0xFF) );
  _out(HDA_DATAREGS+5, (value & 0xFF) );

  _out(HDA_CMDREG, CMD_FORMAT);
  _sleep(HDA_IRQ);

}

void format_all(unsigned int value){

  unsigned int i, j;

  for(i=0; i<HDA_MAXCYLINDER; i++){
    for(j=0; j<HDA_MAXSECTOR; j++){
      format_sector(i, j, 0, value);
    }
  }
}

