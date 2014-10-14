#include "drive.h"

int main() {

	unsigned char buffer[SECTOR_SIZE];
	init_hardware("disque.ini");
	read_sector(0, 0, buffer);
	dump(buffer, SECTOR_SIZE, 1, 0);

	return EXIT_SUCCESS;
}
