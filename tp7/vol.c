#include "vol.h"

static int current_vol;
static struct super_s current_super;

void init_super(const unsigned int vol) {

  struct super_s super;
  unsigned int free_size = -1;

  if(vol > MAX_VOL) {
    printf("le volume en parametre depasse le nombre de volume possible.\n");
    return;
  }

  super.super_magic = SUPER_MAGIC;
  super.super_first_free = 1;

  free_size = mbr.mbr_vol[vol].vol_n_sector - 1;

  super.super_n_free = free_size;
  /* version du cour mais je ne suis pas d'accord car le 
     super représente un seul bloc et pas plusieurs */
  /*write_bloc_n(vol, SUPER, &super, sizeof(super));*/
  write_bloc(vol, SUPER, (unsigned char*)&super);
}

int load_super(const unsigned int vol) {

  if(vol > MAX_VOL) {
    printf("le volume en parametre depasse le nombre de volume possible.\n");
    return 0;
  }

  current_vol = vol;
  /*read_bloc_n(vol, SUPER, &current_super, sizeof(super));*/
  read_bloc(vol, SUPER, (unsigned char*)&current_super);
  return current_super.super_magic == SUPER_MAGIC;
}

unsigned int new_bloc() {
	
  struct free_bloc_s free_bloc;
  unsigned int new;

  if(current_super.super_n_free == 0)
    return 0;

  /*read_bloc_n(current_vol, current_super.super_first_free, &free_bloc, sizeof(free_bloc));*/
  read_bloc(current_vol, current_super.super_first_free, (unsigned char*)&free_bloc);
  new = current_super.super_first_free;

  if(free_bloc.fb_n_free == 1) {
    current_super.super_first_free = free_bloc.fb_next;
    current_super.super_n_free--;
  } else {
    current_super.super_n_free--;
    current_super.super_first_free++;
    free_bloc.fb_n_free--;

    /*write_bloc_n(current_vol, current_super.super_first_free, & free_bloc, sizeof(free_bloc));*/
    write_bloc(current_vol, current_super.super_first_free, (unsigned char*)&free_bloc);
  }

  return new;
}

void free_bloc(const unsigned int bloc) {

  /* nouveau bloc libre qui sera ajouté à la liste */
  struct free_bloc_s new_free_bloc;

  /* bloc libre permettant de trouver le bloc précédent
     le nouveau bloc libre */
  struct free_bloc_s current_free_bloc;

  unsigned int position = current_super.super_first_free;

  /* variable permettant de vérifier si bloc trouve sa place
     dans la chaine de bloc libre */
  unsigned int trouve = 0;

  if(bloc > mbr.mbr_vol[current_vol].vol_n_sector) {
    printf("le numero de bloc n'existe pas dans le volume courant\n");
    return;
  }

  /* on incremente le nombre de bloc libre */
  current_super.super_n_free++;

  /* cas ou le nouveau bloc libre est avant le premier bloc libre */
  if(current_super.super_first_free > bloc) {
    /* pour l'instant le nouveau bloc libre ne 
       sera pas fusionné a une liste de bloc qui serait
       a coté */
    new_free_bloc.fb_n_free = 1;
    new_free_bloc.fb_next = current_super.super_first_free;
    current_super.super_first_free = bloc;

  } else {
    /* premiere lecture pour ne pas prendre en compte le current_super */
    read_bloc(current_vol, position, (unsigned char*)&current_free_bloc);
    position = current_free_bloc.fb_next;

    /* on cherche le bloc précédent le nouveau bloc libre */
    while(position < bloc || position <= current_super.super_first_free) {
      read_bloc(current_vol, position, (unsigned char*)&current_free_bloc);
