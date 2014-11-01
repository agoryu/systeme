#ifndef _MBR_H_
#define _MBR_H_

#include "drive.h"

#define MAX_VOL 8

#define MBR_MAGIC 0xDEADC0DE

enum vol_type_e {VOLT_PR, VOLT_SND, VOLT_OTHER};

struct vol_s {
  unsigned vol_first_cylinder;
  unsigned vol_first_sector;
  unsigned vol_n_sector;
  enum vol_type_e vol_type;
};

struct mbr_s {
  struct vol_s mbr_vol[MAX_VOL];
  unsigned mbr_n_vol;
  unsigned mbr_magic;
};


/**
 * Initialise le Master Boot Record pour une premiere utilisation
 */
void init_mbr();

/**
 * Charge le Master Boot Record si possible.
 * @return 1 en cas de succes sinon 0
 */
int load_mbr();

/**
 * Sauvegarde, sur le premier cylindre et premier secteur, le 
 * Master Boot Record courant.
 * @return 1 en cas de succes sinon 0
 */
int save_mbr();

void read_bloc(const unsigned int vol, 
	       const unsigned int nbloc, 
	       unsigned char* buffer);

void write_bloc(const unsigned int vol, 
		const unsigned int nbloc, 
	        const unsigned char* buffer);

void format_vol(const unsigned int vol);

int mkvol(const unsigned cylindre, const unsigned sector, const unsigned nb_bloc);

#endif
