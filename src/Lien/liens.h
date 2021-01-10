#ifndef __F_l_H__
#define __F_l_H__
// ^ à changer en focntion du nom de votre fichier

#include "./lien/lien.h"

#define TAILLE_PROGRESS_BAR 50

/*============================================*/
typedef struct s_CelLien{ // la cellule qui contient le lien
	Lien descripteur;
	struct s_CelLien* suivant;
}CelluleLien;

typedef struct s_pileLien{
	int taille;
	CelluleLien* tete;
}PileLien;
/*============================================*/


//affiche la barre de progression selon le pourcentage
void printProgressBar(int pourcentage);

PileLien initPileLien();
PileLien empileLien(PileLien,Lien);
PileLien depileLien(PileLien);

Lien* getLien(PileLien,int);
Lien* getLienViaId(PileLien,int);
Lien* getLienViaNom(PileLien,char nom[50]);
void affichePileLien(PileLien);
int dejaVu(char* nomFichier,PileLien p);

void sauvegardePileLien(PileLien p,char* nomFichier);
PileLien chargePileLien(char* nomFichier);


void freePileLien(PileLien* p);

#endif
