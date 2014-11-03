#include "mbr.h"


struct mbr_s mbr;


void init_mbr(){
  mbr.mbr_n_vol = 0;
  mbr.mbr_magic = MBR_MAGIC;
}


int load_mbr() {
  
  char reponse_utilisateur;

  /* si le mbr est plus grand que le secteur on ne pourra pas le mettre dedans */
  if(sizeof(struct mbr_s) > HDA_SECTORSIZE) {
    perror("Erreur : le secteur size est plus petit que la taille du mbr");
    return 0;
  }

  /* lecture du mbr */
  read_sector_n(0, 0, (unsigned char*)&mbr, sizeof(struct mbr_s));

  /* premiere fois que le disque est utilisé */
  if(mbr.mbr_magic != MBR_MAGIC) {

    do {
      printf("Le disque est vierge, voulez-vous continuer les traitements? (y/n)");
      reponse_utilisateur = getchar();

      if(reponse_utilisateur!='y' || reponse_utilisateur!='n'){
	printf("%c n'est pas un choix valide.\n", reponse_utilisateur);
      }

    } while(reponse_utilisateur!='y' || reponse_utilisateur!='n');
    
    if(reponse_utilisateur == 'y'){
      init_mbr();
    } else {
      printf("Chacun changement effectue sur le disque.\n");
      exit(EXIT_SUCCESS);
    }
  }

  return 1;
}


int save_mbr() {
  write_sector_n(0, 0, (unsigned char*)&mbr, sizeof(struct mbr_s));
  return 1;
}


void read_bloc(const unsigned int vol, 
	       const unsigned int nbloc, 
	       unsigned char* buffer) {

  unsigned int secteur, cylindre;
  unsigned int fs, fc;

  fs = mbr.mbr_vol[vol].vol_first_sector;
  fc = mbr.mbr_vol[vol].vol_first_cylinder;

  /* passage de cylindre a volume et de secteur a bloc */
  secteur = (fs + nbloc) % HDA_MAXSECTOR;
  cylindre = fc + (fs + nbloc) / HDA_MAXSECTOR;

  read_sector(cylindre, secteur, buffer);
}


void write_bloc(const unsigned int vol, 
		const unsigned int nbloc, 
	        const unsigned char* buffer) {

  unsigned int secteur, cylindre;
  unsigned int fs, fc;

  fs = mbr.mbr_vol[vol].vol_first_sector;
  fc = mbr.mbr_vol[vol].vol_first_cylinder;

  /* passage de cylindre a volume et de secteur a bloc */
  secteur = (fs + nbloc) % HDA_MAXSECTOR;
  cylindre = fc + (fs + nbloc) / HDA_MAXSECTOR;

  write_sector(cylindre, secteur, buffer);
}


void format_vol(const unsigned int vol) {

  unsigned int secteur, cylindre;
  unsigned int fs, fc, nb_bloc;
  int i;

  fs = mbr.mbr_vol[vol].vol_first_sector;
  fc = mbr.mbr_vol[vol].vol_first_cylinder;
  nb_bloc = mbr.mbr_vol[vol].vol_n_sector;

  for(i=0; i<nb_bloc; i++){

    /* passage de cylindre a volume et de secteur a bloc */
    secteur = (fs + i) % HDA_MAXSECTOR;
    cylindre = fc + (fs + i) / HDA_MAXSECTOR;

    /* revoir la valeur a mettre dans le dernier parametre */
    format_sector(cylindre, secteur, 1, 0);

  }
}


int make_vol(const unsigned cylinder, 
	  const unsigned sector, 
	  const unsigned nbloc){

  if(mbr.mbr_n_vol >= MAX_VOL){
    perror("Impossible de creer un nouveau volume.\n");
    perror("Le nombre de volume sur le disque est a son maximum.\n");
    return 0;
  }

  mbr.mbr_vol[mbr.mbr_n_vol].vol_first_cylinder = cylinder;
  mbr.mbr_vol[mbr.mbr_n_vol].vol_first_sector = sector;
  mbr.mbr_vol[mbr.mbr_n_vol].vol_n_sector = nbloc;
  mbr.mbr_vol[mbr.mbr_n_vol].vol_type = VOLT_PR;

  mbr.mbr_n_vol++;

  return 1;
}

void display_vol(){
  int i, nvol;

  if(mbr.mbr_n_vol == 0){
    printf("Aucun volume sur le disque.\n");
    return;
  }
  
  nvol = mbr.mbr_n_vol;

  printf("Il y a %d volume(s) sur le disque.\n\n", nvol);

  for(i=0; i<nvol; i++){
    printf("Volume %d:\n", i+1);
    printf("\t - Commence au cylindre %d.\n", mbr.mbr_vol[i].vol_first_cylinder); 
    printf("\t - Commence au secteur %d.\n", mbr.mbr_vol[i].vol_first_sector);
    printf("\t - Nombre de blocs : %d.", mbr.mbr_vol[i].vol_n_sector);
    printf("\t - Type de volume: ");
    switch(mbr.mbr_vol[i].vol_type){
    case VOLT_PR:
      printf("PRIMAIRE.\n");
      break;
    case VOLT_SND:
      printf("SECONDAIRE.\n");
      break;
    case VOLT_OTHER:
      printf("AUTRE.\n");
      break;
    }
    printf("\n");
  }

}
