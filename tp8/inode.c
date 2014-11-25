#include "inode.h"

void read_inode(const unsigned int inumber, struct inode_s *inode){
  read_bloc_n(current_vol, inumber, (unsigned char*)inode, sizeof(struct inode_s));
}

void write_inode(const unsigned int inumber, const struct inode_s *inode){
  write_bloc_n(current_vol, inumber, (unsigned char*)inode, sizeof(struct inode_s));
}

unsigned int create_inode(const enum inode_type_e type){
  
  unsigned int inumber;
  struct inode_s inode;

  if( !memset(&inode, 0, sizeof(struct inode_s)) ){
    fprintf(stderr, 
	    "Erreur lors du remplissage de la zone mémoire de l'inode lors de sa création");
    return 0;
  }

  inode.in_type = type;
  inumber = new_bloc();

  if( !inumber ){
    fprintf(stderr, "Disque plein, impossible de créer un nouvel inode");
    return 0;
  }

  write_inode(inumber, &inode);

  return inumber;
}

int delete_inode(const unsigned int inumber){
  
  struct inode_s inode;

  read_inode(inumber, &inode);
  free_blocs(inode.in_direct, N_DIRECT);

  /* TODO delete indirect et double indirect */
}

