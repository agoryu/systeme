TP5 : Accès au materiel
=======================



# Auteurs

- Elliot VANEGUE
- Gaëtan DEFLANDRE



# Description


## Bibliotheque drive

La bibliotheque d'acces au materiel *drive* est ecrite dans 
les fichers suivant:

- drive.h
- drive.c

On y retrouve les fonctions:

   int seek_sector(unsigned int cylinder, unsigned int sector);

   void read_sector(unsigned int cylinder, unsigned int sector, unsigned char* buffer);

   void write_sector(unsigned int cylinder, unsigned int sector, unsigned char* buffer);

   void format_sector(unsigned int cylinder, 
   		      unsigned int sector, 
		      unsigned int nsector, 
		      unsigned int value);

   void format_all(unsigned int value);


## Commandes dmps et frmt 

Les fichier *dmps.c* et *frmt.c* contiennent le code des 
commandes *dmps* et *frmt* qui servent:
-dmps: lire d'une donnee a un cylindre et sector en paramtre.
-frmt: format l'enssemble du materiel. 


## Utilisation

   $ ./dmps c s

Lire la donnée au cylindre c et au sector s.

   $ ./frmt

Format les donnees du disque.