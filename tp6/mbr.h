#ifndef _MBR_H_
#define _MBR_H_

#include "drive.h"

#define MAX_VOL 8

#define MBR_MAGIC 0xDEADC0DE

/**
 * \Brief Type de volume
 * \enum vol_type_e mbr.h "mbr.h"
 */
enum vol_type_e {
  /** Volume de base pour le systeme de fichier */
  VOLT_PR, 
  /** Volume annexe du systeme de fichiers */
  VOLT_SND, 
  /** Autre type de volume qui ne peut etre associe au systeme de fichiers */
  VOLT_OTHER
};

/**
 * \brief Structure qui decrit un volume
 * \struct vol_s mbr.h "mbr.h"
 */
struct vol_s {
  /** Commence a partir de ce cylindre */
  unsigned vol_first_cylinder;
  /** 
   * Commence a partir de ce secteur 
   * dans le cylindre \a vol_first_cylinder 
   */
  unsigned vol_first_sector;
  /** Nombre de secteur dont est compose le volume */
  unsigned vol_n_sector;
  /** Type du volume */
  enum vol_type_e vol_type;
};

/**
 * \brief Structure qui decrit le Master Boot Record
 * \struct mbr_s mbr.h "mbr.h"
 */
struct mbr_s {
  /** Tableau des volumes present sur le disque */
  struct vol_s mbr_vol[MAX_VOL];
  /** Nombre de volumes sur le disque */
  unsigned mbr_n_vol;
  /** Nombre magique */
  unsigned mbr_magic;
};


/**
 * Initialise le Master Boot Record pour une premiere utilisation
 */
void init_mbr();

/**
 * Charge le Master Boot Record si possible.
 * \return 1 en cas de succes sinon 0
 */
int load_mbr();

/**
 * Sauvegarde, sur le premier cylindre et premier secteur, le 
 * Master Boot Record courant.
 * \return 1 en cas de succes sinon 0
 */
int save_mbr();

/**
 * Lit le \a nbloc eme bloc du volume \a vol.
 * \param[in] vol Le volume sur lequel sont ecrite les donnees que l'on veut 
 *                recuperer.
 * \param[in] nbloc Le numero du bloc que l'on veut lire dans le volume 
 *                  \a vol.
 * \param[out] buffer Buffer dans lequel sont ecrite les donnees lues.  
 */
void read_bloc(const unsigned int vol, 
	       const unsigned int nbloc, 
	       unsigned char* buffer);

/**
 * Ecrit le contenu de \a buffer sur le \a nbloc eme 
 * bloc du volume \a vol.
 * \param[in] vol Le volume sur lequel on veut ecrire les donnees.
 * \param[in] nbloc Le numero du bloc sur lequel on veut ecrire les donnees 
 *                  dans le volume \a vol.
 * \param[in] buffer Buffer qui contient les donnees que l'on veut écrite sur 
 *                   le disque.
 */
void write_bloc(const unsigned int vol, 
		const unsigned int nbloc, 
	        const unsigned char* buffer);

/**
 * Supprime les donnees du volume \a vol sans supprime le volume \a vol
 * \param[in] vol Le volume a formate.
 */
void format_vol(const unsigned int vol);


/**
 * Cree un volume a partir du couple \a cylinder et \a sector 
 * de \a nbloc bloc.
 * \param[in] cylinder Commence a partir de ce cylindre.
 * \param[in] sector Commence a partir de ce secteur 
 *                   dans le cylindre \a cylinder.
 * \param[in] nbloc Nombre de bloc pour le volume.
 * \return 1 en cas de succes sinon 0.
 */
int make_vol(const unsigned cylinder, 
	  const unsigned sector, 
	  const unsigned nbloc);

/**
 * Affiche les volume presents sur le disque.
 */
void display_vol();

#endif
