#ifndef MBR_H
#define MBR_H

#include "drive.h"

#define MAX_VOL 8

enum vol_type_e {VOLT_PR, VOLT_SND, VOLT_OTHER}

struct vol-s {
  unsigned vol_first_cylinder;
  unsigned col_first_sector;
  unsigned vol_n_sector;
  enum vol_type_e vol_type;
};

struct mbr_s {
  struct vol_s mbr_vol[MAX_VOL];
  

#endif
