#include <stdlib.h>
#include <stdio.h>
#include "hardware.h"
#include <string.h>

#define SYSCALL_SWITCH_0 16
#define SYSCALL_SWITCH_1 17
#define N 42

struct tlb_entity_s {
	unsigned tlb_rfu :8;
	unsigned tlb_vpage :12;
	unsigned tlb_ppage :8;
	unsigned tlb_acces :3;
	unsigned tlb_active :1;
};

static int sum(void *ptr);

void init();

static int ppage_of_vaddr(const int process, const unsigned vaddr);

void mmuhandler();

void user(); 