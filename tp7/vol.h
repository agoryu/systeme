#ifndef VOL_H
#define VOL_H

/**
 * \file vol.h
 * \brief Gestionnaire de bloc
 * \author Elliot Vanegue et Gaëtan Deflandre
 * \version 1
 */

#include "mbr.h"

/** Position du super dans la liste de bloc */
#define SUPER 0
/** Magique utilisé pour Le bloc super */
#define SUPER_MAGIC 0xDEADC0DE

/** récupération du mbr du disque disponible dans le fichier mbr.c */
extern struct mbr_s mbr;

/**
 * \brief Représente le premier bloc qui indique 
 *	où se trouve le premier bloc libre
 * \struct super_s "vol.h"  
 */
struct super_s {
  /** numéro magique */
	unsigned super_magic;
  /** premier bloc libre dans la liste de bloc */
	unsigned super_first_free;
  /** nombre de bloc libre dans la liste de bloc */
	unsigned super_n_free;
};

/**
 * \brief Représente un ensemble contigue de bloc libre
 * \struct free_bloc_s "vol.h" 
 */
struct free_bloc_s {
  /** nombre de bloc libre à la suite */
	unsigned fb_n_free;
  /** prochain ensemble de bloc libre */
	unsigned fb_next;
};

/**
  * \brief Initialise le super bloc d'un volume
  * \param[in] vol numero du volume a initialiser
  * \return void
  */
void init_super(const unsigned int vol);

/**
  * \brief Charge le super bloc dans une variable globale
  * \param[in] vol numero du volume à charger
  * \return 1 si le chargement a été chargé, 0 sinon
  */
int load_super(const unsigned int vol);

/**
  * \brief Retourne l'emplacement d'un bloc disponible
  * \return L'emplacement du bloc disponible
  */
unsigned int new_bloc();

/**
  * \brief Libere un bloc dans la liste de bloc
  * \param[in] bloc numéro du bloc à libérer
  */
void free_bloc(const unsigned int bloc);
#endif
