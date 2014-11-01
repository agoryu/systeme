#include "mbr.h"

int main(int argc, char**argv)
{
	
	int size, cylindre, secteur;
	int i;
	unsigned char* buffer;

	size = cylindre = secteur = -1;

	/* vérification des arguments entree par l'utilisateur */
	if(argc < 7)
	{
		printf("Il vous manque un argument pour créer votre volume\n");
		return EXIT_FAILURE;
	}

	for(i=1; i<argc-1; i++)
	{
		if(strcmp(argv[i], "-s") == 1)
		{
			size = atoi(argv[i+1]);
			if(size == NULL)
				printf("La taille du volume n'est pas du bon type\n");
		}

		if(strcmp(argv[i], "-fc") == 1)
		{
			cylindre = atoi(argv[i+1]);
			if(cylindre == NULL)
				printf("La valeur pour le cylindre n'est pas du bon type\n");
		}
		if(strcmp(argv[i], "-fs") == 1)
		{
			secteur = atoi(argv[i+1]);
			if(cylindre == NULL)
				printf("La valeur pour le secteur n'est pas du bon type\n");
		}
	}

	if(size == -1 || secteur == -1 || cylindre == -1) {
		printf("Il manque un argument pour pouvoir créer le volume\n");
		return EXIT_FAILURE;
	}

	/* chargement du mbr */
	load_mbr();

	/* allocation du buffer avec la taille fournit par l'utilisateur */
	buffer = malloc(sizeof(unsigned char) * size);

	write_bloc(const unsigned int vol, size, buffer);

	/* sauvegarde de tous les changements effectué sur le mbr */
	save_mbr();
	return EXIT_SUCCESS;
}