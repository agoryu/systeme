#ifndef _INODE_H
#define _INODE_H

#include "vol.h"

/**
 * \file inode.h
 * \brief Gestionnaire des inodes des fichiers
 * \author Elliot Vanegue et Gaëtan Deflandre
 * \version 1
 */

 /** Magique */
#define SUPER_MAGIC 0xDEADC0DE

/** Nombre de bloc directe */
#define N_DIRECT 2

/** Definition d'un bloc null */
#define BLOC_NULL 0

/** Nombre de bloc indirecte */
#define NNBPB (BLOC_SIZE / sizeof(int))

/**
 * \Brief Type d'inode
 * \enum inode_type_e mbr.h "inode.h"
 */
enum inode_type_e {
  IT_FILE,
  IT_DIR,
  IT_OTHER
};

/**
 * \brief Représente un l'inode d'un fichier
 * \struct inode_s "inode.h"  
 */
struct inode_s {
	/** type d'inode */
	enum inode_type_e in_type;
	/** taille en octet du fichier */
	unsigned int in_size;
	/** bloc direct */
	unsigned int in_direct[N_DIRECT];
	/** bloc indirect composé de bloc direct */
	unsigned int indirect;
	/** bloc double indirect composé de plusieurs bloc indirecte */
	unsigned int in_d_indirect;
}

/**
 * \brief Lit un inode à partir du inumber du fichier 
 * \param[in] inumber Numéro du fichier traité
 * \param[out] inode Structure contenant le résultat de la lecture
 * \return void
 */
void read_inode(const unsigned int inumber, struct inode_s *inode);

/**
 * \brief Ecrit un inode à partir du inumber du fichier 
 * \param[in] inumber Numéro du fichier traité
 * \param[in] inode Structure contenant les données à écrire
 * \return void
 */
void write_inode(const unsigned int inumber, const struct inode_s *inode);

/**
 * \brief Création d'un inode sur le disque 
 * \param[in] type Type de fichier traité
 * \return Le numéro l'inode créé
 */
unsigned int create_inode(const enum file_type_e type);

/**
 * \brief Suppression d'un inode 
 * \param[in] inumber Numéro du fichier à supprimer
 * \return 1 si la suppression réussi, 0 sinon
 */
int delete_inode(const unsigned int inumber);

/**
 * \brief Méthode permettant de récupérer le numéro du fbloc-ieme bloc de l'inode
 * \param[in] inumber Numéro du fichier traité
 * \param[in] fbloc Numéro du bloc dont on veut sa position
 * \param[in] do_allocate Si vrai on alloue un bloc qui serait vide
 * \return Position du bloc demandé. Retourne null si le bloc est null et que do_allocate est vrai.
 */
unsigned int vbloc_of_fbloc(const unsigned int inumber, 
                            const unsigned int fbloc,
                            const bool_t do_allocate);


#endif
