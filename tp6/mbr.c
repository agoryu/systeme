#include "mbr.h"

struct mbr_s mbr;

int load_mbr() {
  
  char reponse_utilisateur;

  /* lecture du mbr */
  read_sector_n(0, 0, (unsigned char*)mbr, sizeof(stuct mbr_s));

  /* si le mbr est plus grand que le secteur on pourra pas le mettre dedans */
  if(sizeof(struct mbr_s) > SECTOR_SIZE) {
    printf("Erreur : le secteur size est plus petit que la taille du mbr");
    return 0;
  }

  /* premiere fois que le disque est utilisé */
  if(mbr.mbr_magic != MBR_MAGIC) {
    mbr.mbr_n_vol = 0;
    mbr.mbr_magic = MBR_MAGIC;
    printf("Le disque est vierge, voulez-vous continuer les traitement? (y/n)");
    reponse_utilisateur = getchar();
    
    if(repons_utilisateur = 'n')
      exit(EXIT_SUCCESS);
  }

  return 1;
}

int save_mbr() {
  
  write_sector_n(0, 0, (unsigned char*)mbr, sizeof(struct mbr_s));
  return 1;
}

void read_bloc(const unsigned int vol, 
	       const unsigned int nbloc, 
	       unsigned char* buffer) {

  unsigned int secteur, cylindre;
  unsigned int fs, fc;

  fs = mbr.mbr_vol[vol].first_sector;
  fc = mbr.mbr_vol[vol].first_cylindre;

  /* passage de cylindre a volume et de secteur a bloc */
  secteur = (fs + nbloc) % MAX_SECTOR;
  cylindre = fc + (fs + secteur) / MAX_SECTOR;

  read_sector(cylindre, secteur, buffer);
}

void write_bloc(const unsigned int vol, 
	       const unsigned int nbloc, 
	       const unsigned char* buffer) {

  unsigned int secteur, cylindre;
  unsigned int fs, fc;

  fs = mbr.mbr_vol[vol].first_sector;
  fc = mbr.mbr_vol[vol].first_cylindre;

  /* passage de cylindre a volume et de secteur a bloc */
  secteur = (fs + nbloc) % MAX_SECTOR;
  cylindre = fc + (fs + secteur) / MAX_SECTOR;

  write_sector(cylindre, secteur, buffer);
}

void format_vol(const unsigned int vol) {

  unsigned int secteur, cylindre;
  unsigned int fs, fc;

  fs = mbr.mbr_vol[vol].first_sector;
  fc = mbr.mbr_vol[vol].first_cylindre;

  /* passage de cylindre a volume et de secteur a bloc */
  secteur = (fs + nbloc) % MAX_SECTOR;
  cylindre = fc + (fs + secteur) / MAX_SECTOR;

  /* revoir la valeur a mettre dans le dernier parametre */
  format_sector(cylindre, secteur, MAX_SECTOR, 0);
}
