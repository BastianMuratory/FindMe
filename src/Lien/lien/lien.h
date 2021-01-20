// Bastian : fonctions permettant d'utiliser un lien (reliant un id et un nom de descripteur)
#ifndef __fichier_h__
#define __fichier_h__

#define TAILLE_MAX 100

typedef struct s_Lien{
	int ID; // ID du descripteur
	char nomFichier[TAILLE_MAX+1]; // nom du fichier decrit
}Lien;

// Creation du descripteur
Lien creerLien(char* nomDuFichier,int ID);
//getters
int getIdLien(Lien d);
char* getNomLien(Lien d);
//affectation et copie
void affectLien(Lien* e,Lien* x);
void afficheLien(Lien d);

#endif
