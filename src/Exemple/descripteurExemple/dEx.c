#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dEx.h"

/*
typedef struct s_DescripteurExemple{
	char nom[50];
	int id;
}DescripteurExemple;
*/


// Creation du descripteur
DescripteurExemple creerDecripteurDuExemple(char nomDuFichier[50]){
	DescripteurExemple d;
	char nom[50];
	strcpy(nom,nomDuFichier);
	nom[strlen(nom) - 4] = '\0';
	strcpy(d.nom,nomDuFichier);
	d.ID = atoi(nom);

	return d;
}
//getters et setters
int getIdDescripteurExemple(DescripteurExemple d){
	return d.ID;
}
char* getNomDescripteurExemple(DescripteurExemple d){
	char* nom = malloc(50*sizeof(char));
	strcpy(nom,d.nom);
	return nom;
}

int setValueDescripteurExemple(DescripteurExemple* pointeur_d,int x){
	pointeur_d->ID = x;
	return 0;
}
//affectation et affichage
void affectDescripteurExemple(DescripteurExemple* e1,DescripteurExemple* e2){
	e2->ID = e1->ID;
	strcpy(e2->nom,e1->nom);
}
void afficheDescripteurExemple(DescripteurExemple d){
	printf("[nom = %s | ID = %d]",d.nom,d.ID);
}

// calcul distance
int distanceDescripteurExemple(DescripteurExemple d1,DescripteurExemple d2){
	return d1.ID-d2.ID;
};