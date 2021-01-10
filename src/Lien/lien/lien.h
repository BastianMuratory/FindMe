#ifndef __fichier_h__
#define __fichier_h__



typedef struct s_Lien{
	int ID; // ID du descripteur
	char nomFichier[100]; // nom du fichier decrit
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
