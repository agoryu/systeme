#include "inode.h"

void read_inode(const unsigned int inumber, struct inode_s *inode){
  read_bloc_n(current_vol, inumber, inode, sizeof(struct inode_s));
}

void write_inode(const unsigned int inumber, const struct inode_s *inode){
  write_bloc_n(current_vol, inumber, inode, sizeof(struct inode_s));
}
