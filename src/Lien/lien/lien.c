#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lien.h"

/*
typedef struct s_Lien{
	int ID; // ID du descripteur
	char nomFichier[100]; // nom du fichier decrit
}Lien;
*/

// Creation du descripteur
Lien creerLien(char* nomDuFichier,int ID){
	Lien l;
	strcpy(l.nomFichier,nomDuFichier);
	l.ID = ID;
	return l;
}

//getters
int getIdLien(Lien d){
	return d.ID;
}

char* getNomLien(Lien d){
	char* retour = malloc(100*sizeof(char));
	strcat(retour,d.nomFichier);
	return retour;
}

//affectation et copie
void affectLien(Lien* e,Lien* x){
	strcpy(x->nomFichier,e->nomFichier);
	x->ID = e->ID;
}

void afficheLien(Lien d){
	printf("Le texte %s est lié au descripteur %d\n",d.nomFichier,d.ID);
}

int sauvegarderLien(FILE* fichier,Lien d){
	fprintf(fichier,"%d,%s\n",d.ID,d.nomFichier);
	return 0;
}

Lien chargerLien(FILE* fichier){
	Lien d;
	fscanf(fichier, "%d,%s\n",&d.ID,d.nomFichier);
	return d;
}