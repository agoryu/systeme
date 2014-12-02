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
  unsigned int blocs[NNBPB];
  unsigned int blocs2[NNBPB];
  int i;

  read_inode(inumber, &inode);
  free_blocs(inode.in_direct, N_DIRECT);

  read_bloc(current_vol, inode.in_indirect, (unsigned char*)blocs);
  free_blocs(blocs, NNBPB);
  free_bloc(inode.in_indirect);

  read_bloc(current_vol, inode.in_d_indirect, (unsigned char*)blocs);

  for(i=0; i<NNBPB; i++) {
    read_bloc(current_vol, blocs[i], (unsigned char*)blocs2);
    free_blocs(blocs, NNBPB);
  }

  free_bloc(inode.in_d_indirect);

  return 1;
}


unsigned int vbloc_of_fbloc(const unsigned int inumber, 
                            const unsigned int fbloc,
                            const unsigned int do_allocate){
  
  unsigned int position = fbloc;
  struct inode_s inode;
  unsigned int blocs[NNBPB];
  unsigned int blocs2[NNBPB];
  unsigned int i = 0;

  read_inode(inumber, &inode);

  if(position<N_DIRECT){
    return inode.in_direct[position];
  }

  position -= N_DIRECT;

  if(position<NNBPB){
    if(inode.in_direct == BLOC_NULL){
      return BLOC_NULL;
    }

    read_bloc(current_vol, inode.in_indirect, (unsigned char*)&blocs);
    return blocs[position];
  }

  position -= NNBPB;

  if(position < NNBPB*NNBPB){

    if(inode.in_d_indirect == BLOC_NULL){
      return BLOC_NULL;
    }

    read_bloc(current_vol, inode.in_d_indirect, (unsigned char*)&blocs);
    for(i=0; i<NNBPB; i++){

      if(position<NNBPB){
	
	if(blocs[i] == BLOC_NULL){
	  return BLOC_NULL;
	}

	read_bloc(current_vol, blocs[i], (unsigned char*)&blocs2);
	return blocs2[position];
      }

      position -= NNBPB;

    }
  }
  
  /* fbloc est superieur au max de bloc par inoeud */
  return BLOC_NULL;
}
