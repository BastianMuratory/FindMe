#ifndef __piledossier__
#define __piledossier__

typedef struct s_element{
	char* nom;
	struct s_element* next;
}Element;

typedef struct s_pile{
	int taille;
	Element* tete;
}Pile;

Pile* new_Pile();
void empile(Pile* p,char* nom_fichier);
void affiche(Pile* p);
void destroy(Pile* p);

#endif