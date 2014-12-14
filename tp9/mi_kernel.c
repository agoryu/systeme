#include "mi_syscall.h"

static int current_process;

static void 
switch_to_process0(void) 
{
    current_process = 0;
    _out(MMU_CMD, MMU_RESET);
}

static void
switch_to_process1(void) 
{
    current_process = 1;
    _out(MMU_CMD, MMU_RESET);
}

void init() {

	/* init hardware */
  	if(!init_hardware("hardware.ini")){
    	perror("Initialization error\n");
    	exit(EXIT_FAILURE);
  	}

  	IRQVECTOR[16] = switch_to_process0;
    IRQVECTOR[17] = switch_to_process1;
    _mask(0x1001);

}

void mmuhandler() {

	struct tlb_entity_s tlb;
	unsigned vaddr = _in(MMU_FAULT_ADDR);
	int ppage = ppage_of_vaddr(current_process, vaddr);

	if(ppage == -1) {
		printf("erreur dans la lecture de ppage");
		return
	}

	tlb.tlb_vpage = (vaddr >> 12) & 0xFFF;
	tlb.tlb_ppage = ppage;
	tlb.tlb_acces = 0x7;
	tlb.tlb_active = 1;

	_out(TLB_ADD_ENTRY, *(int*)(&tlb));
}

static int ppage_of_vaddr(const int process, const unsigned vaddr) {

	int vpage;

	//verification de la validité de l'adresse virtuel
	if(vaddr < VIRTUAL_MEMORY || vaddr > VIRTUAL_MEMORY + VM_SIZE) {
		printf("erreur l'adresse virtuel n'est pas valide");
		return -1;
	}


	vpage = (vaddr >> 12) & 0xFFF;

	//ya pas de raison de passé la dedans avec la verif du dessus
	if(vpage > N/2) {
		printf("erreur la page n'est pas bonne");
		return -1;
	}

	if(process == 0)
		ppage = vpage + 1;
	else if(process == 1)
		ppage = vpage + N/2 + 1;

	return ppage;
}

int 
main(int argc, char **argv) 
{

    init();
    user();
  	return EXIT_SUCCESS;
}