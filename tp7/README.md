Un systeme de fichiers a la Unix
===============================



# Auteurs

- Elliot VANEGUE
- Gaëtan DEFLANDRE



* * *


# TP5 : Acces au materiel


## Description


### Bibliotheque drive

La bibliotheque d'acces au materiel *drive* est ecrite dans 
les fichers suivant:

- drive.h
- drive.c

Ces fonctionnalites font partie de la premiere couche d'abtraction du materiels.

On y retrouve les fonctions:

	int is_valid_cylinder(const unsigned int cylinder);

	int is_valid_sector(const unsigned int sector);

	int seek_sector(const unsigned int cylinder, const unsigned int sector);

	void read_sector(const unsigned int cylinder, 
					 const unsigned int sector, 
					 unsigned char* buffer);

	void read_sector_n(const unsigned int cylinder, 
				       const unsigned int sector, 
				       unsigned char* buffer, 
				       const size_t n);

	void write_sector(const unsigned int cylinder, 
					  const unsigned int sector, 
					  const unsigned char* buffer);

	void write_sector_n(const unsigned int cylinder, 
						const unsigned int sector, 
						const unsigned char* buffer,
						const size_t n);

	void format_sector(const unsigned int cylinder, 
					   const unsigned int sector, 
					   const unsigned int nsector, 
					   const unsigned int value);

	void format_all(const unsigned int value);


### Commandes dmps et frmt 

Les fichier *dmps.c* et *frmt.c* contiennent le code des 
commandes *dmps* et *frmt* qui servent:

- dmps: lire d'une donnee a un cylindre et sector en parametre.
- frmt: format l'ensemble du materiel. 


### Utilisation

    $ ./dmps c s

Lire la donnee au cylindre c et au secteur s.

    $ ./frmt

Format les donnees du disque.



* * *


# TP6 : Gestion de volumes


## Description


### Bibliotheque mbr

La bibliotheque de gestion des volumes *mbr* est écrite dans les 
fichiers:

 - mbr.h
 - mbr.c

Ces fonctionnalites font partie de la deuxieme couche logiciel qui interagissent 
directement avec les fonction de la bicliotheque *drive* (premiere couche).

On y retrouve les fonctions:

	void init_mbr();

	int load_mbr();

	int save_mbr();

	void read_bloc(const unsigned int vol, 
				   const unsigned int nbloc, 
				   unsigned char* buffer);

	void write_bloc(const unsigned int vol, 
					const unsigned int nbloc, 
					const unsigned char* buffer);

	void format_vol(const unsigned int vol);

	int make_vol(const unsigned cylinder, 
				 const unsigned sector, 
				 const unsigned nbloc);

	void display_vol();


### Commandes mkvol et dvol

Les commandes mkvol et dvol sont implementees, mais ne sont pas encore fonctionnelles.
