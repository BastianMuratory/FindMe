#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "./pile.h"

/*
typedef struct s_CelExemple{ // le descripteur de Exemple
	DescripteurExemple descripteur;
	struct s_CelExemple* suivant;
}CelluleExemple;

typedef struct s_pileDescripteurExemple{
	int taille;
	CelluleExemple* tete;
}PileDescripteurExemple;
*/

CelluleExemple* initCel(DescripteurExemple el){
	CelluleExemple* c = (CelluleExemple*)malloc(sizeof(CelluleExemple));
	c->suivant = NULL;
	affectDescripteurExemple(&el,&(c->descripteur));
	return c;
}

PileDescripteurExemple initPileDescripteurExemple(){
	PileDescripteurExemple p;
	p.taille = 0;
	p.tete = NULL;
	return p;
}

PileDescripteurExemple empileDescripteurExemple(PileDescripteurExemple p,DescripteurExemple d){
	CelluleExemple* c = initCel(d);
	if(p.taille!=0){
		c->suivant = p.tete;
	}
	p.tete = c;
	p.taille++;
	return p;
}

PileDescripteurExemple depileDescripteurExemple(PileDescripteurExemple p){
	if(p.taille==0){
		printf("Erreur : votre pile est déjà vide !\n");
	}else{
		CelluleExemple* cel = p.tete;
		p.tete = p.tete->suivant;
		free(cel);
		p.taille--;
	}
	return p;
}


// pas besoin de passer un pointeur de pile !!!!!!
DescripteurExemple* getDescripteurExemple(PileDescripteurExemple p,int x){
	CelluleExemple* courant = p.tete;
	if(x>p.taille-1){
		printf("Il n'y a pas assez de descripteur, le pointeur est null\n");
		return NULL;
	}else{
		for(int i=0;i<x;i++){
			courant = courant->suivant;
		}
	}
	return &(courant->descripteur);
}

DescripteurExemple* getDescripteurExempleViaId(PileDescripteurExemple p,int id){
	CelluleExemple* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(getIdDescripteurExemple(courant->descripteur)==id){
			pasTrouve = 0;
		}
		i++;
	}
	if(pasTrouve){
		puts("Le descripteur n'a pas été trouvé");
		return NULL;
	}
	puts("Le descripteur a été trouvé");
	return &(courant->descripteur);
}

DescripteurExemple* getDescripteurExempleViaNom(PileDescripteurExemple p,char nom[50]){
	CelluleExemple* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(strcmp( nom, getNomDescripteurExemple(courant->descripteur))==0){
			pasTrouve = 0;
		}
		i++;
	}
	if(pasTrouve){
		puts("Le descripteur n'a pas été trouvé");
		return NULL;
	}
	puts("Le descripteur a été trouvé");
	return &(courant->descripteur);

}


void affichePileDescripteurExemple(PileDescripteurExemple p){
	printf("============================\nPile de [%d] descripteurs\n",p.taille);
	CelluleExemple* courant;
	for(int i=0;i<p.taille;i++){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		printf("[%d]",i);
		afficheDescripteurExemple(courant->descripteur);
		puts("");
	}
	puts("============================");
}

void freePileDescripteurExemple(PileDescripteurExemple* p){
	printf("p->taille = %d\n",p->taille);
	int nombre = p->taille;
	if(nombre >0){
		for(int i =0;i<nombre;i++){
			*p = depileDescripteurExemple(*p);
		}
		puts("\nPile detruite\n");
	}else{
		puts("\nPile deja vide\n");
	}
}


int toutDescripteurExemple(char* nomDuFichier,PileDescripteurExemple* p,PileLien* l){
	DescripteurExemple desc = creerDecripteurDuExemple(nomDuFichier);
	Lien lien = creerLien(desc.nom,desc.ID);
	*p = empileDescripteurExemple(*p, desc);
	*l = empileLien(*l, lien);
	return EXIT_SUCCESS;
}




