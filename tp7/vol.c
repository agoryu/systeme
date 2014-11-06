#include "vol.h"

static int current_vol;
static struct super_s current_super;

void init_super(const unsigned int vol) {

	struct super_s super;
	unsigned int free_size = -1;

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

	
}

