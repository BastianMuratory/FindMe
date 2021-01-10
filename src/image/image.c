#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./image.h"

CelluleImage* initCelImage(DescripteurImage el,int n_bits){
	CelluleImage* c = (CelluleImage*)malloc(sizeof(CelluleImage));
	c->suivant = NULL;
	affectDescripteurImage(&el,&(c->descripteur),n_bits);
	return c;
}

PileDescripteurImage initPileDescripteurImage(){
	PileDescripteurImage p;
	p.taille = 0;
	p.tete = NULL;
	return p;
}

PileDescripteurImage empileDescripteurImage(PileDescripteurImage p,DescripteurImage d,int n_bits){
	CelluleImage* c = initCelImage(d,n_bits);
	if(p.taille!=0){
		c->suivant = p.tete;
	}
	p.tete = c;
	p.taille++;
	return p;
}


// pas besoin de passer un pointeur de pile !!!!!!
DescripteurImage* getDescripteurImage(PileDescripteurImage p,int x){
	CelluleImage* courant = p.tete;
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

DescripteurImage* getDescripteurImageViaId(PileDescripteurImage p,int id){
	CelluleImage* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(getIdDescripteurImage(courant->descripteur)==id){
			pasTrouve = 0;
		}
		i++;
	}
	if(pasTrouve){
		//puts("Le descripteur n'a pas été trouvé");
		return NULL;
	}
	//puts("Le descripteur a été trouvé");
	return &(courant->descripteur);
}

DescripteurImage* getDescripteurImageViaNom(PileDescripteurImage p,char nom[50]){
	CelluleImage* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(strcmp( nom, getNomDescripteurImage(courant->descripteur))==0){
			pasTrouve = 0;
		}
		i++;
	}
	if(pasTrouve){
		//puts("Le descripteur n'a pas été trouvé");
		return NULL;
	}
	//puts("Le descripteur a été trouvé");
	return &(courant->descripteur);

}


void affichePileDescripteurImage(PileDescripteurImage p){
	printf("============================\nPile de [%d] descripteurs\n",p.taille);
	CelluleImage* courant;
	for(int i=0;i<p.taille;i++){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		printf("[%d]",i);
		afficheDescripteurImage(courant->descripteur);
		puts("");
	}
	puts("============================\n");
}

// modifiée
PileDescripteurImage depileDescripteurImage(PileDescripteurImage p){
	if(p.taille==0){
		//puts("Erreur : votre pile est déjà vide !");
	}else{
		CelluleImage* cel = p.tete;
		p.tete = p.tete->suivant;
		free(cel);
		p.taille--;
	}
	return p;
}

void freePileDescripteurImage(PileDescripteurImage* p){
	//printf("p->taille = %d\n",p->taille);
	int nombre = p->taille;
	if(nombre >0){
		for(int i =0;i<nombre;i++){
			*p = depileDescripteurImage(*p);
		}
		//puts("Pile Descripteur image vidée");
	}else{
		//puts("Pile deja vide");
	}
}


int toutDescripteurImage(char* nomDuFichier,PileDescripteurImage* p,PileLien* l,int bitFort, int ID){
	DescripteurImage desc = creerDescripteurImage(nomDuFichier,bitFort,ID);
	Lien lien = creerLien(desc.nom,desc.ID);
	*p = empileDescripteurImage(*p, desc,bitFort);
	*l = empileLien(*l, lien);
	return EXIT_SUCCESS;
}

// sauvegarde un descripteur dans un fichier
int SauvegardePileDescripteurImage(PileDescripteurImage p,PileLien l){
  int pourcentage;
	FILE* fichier = NULL;
	// Sauvegarde de la Pile de descripteurs
	fichier = fopen("./sauvegarde/Descripteur_image/base_descripteur_image","w");
	if(fichier == NULL){
		//puts("base_descripteur_image n'existe pas ou n'est pas trouvé");
	}
	printf("\x1b[33m");
	fprintf(fichier,"%d\n",p.taille);
	for(int i =0;i<p.taille;i++){
		sauvegarderDescripteurImage(fichier,*getDescripteurImage(p,i));
    pourcentage = ((i+1)*100)/p.taille;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	printf("\x1b[32m");
  printProgressBar(100);
  printf("\x1b[0m");
  printf("\n");
	//puts("sauvegarde pile desc fini");
	fclose(fichier);
	// Sauvegarde de la pile de liens
	sauvegardePileLien(l,"./sauvegarde/Descripteur_image/liste_base_image");
	return 0;
}

// charge un descripteur depuis un fichier
PileDescripteurImage chargePileDescripteurImage(int n_bits,int*id){
  int pourcentage;
	FILE* fichier = NULL;
	// Sauvegarde de la Pile de descripteurs
	int taille;
	PileDescripteurImage p = initPileDescripteurImage();
	fichier = fopen("./sauvegarde/Descripteur_image/base_descripteur_image","r");
	if(fichier == NULL){
		puts("base_descripteur_image n'existe pas ou n'est pas trouvé");
		return p;
	}
	fscanf(fichier,"%d\n",&taille);
	*id = taille;
	printf("\x1b[33m");
	for(int i =0;i<taille;i++){
		p = empileDescripteurImage(p,chargerDescripteurImage(fichier),n_bits);
    pourcentage = ((i+1)*100)/taille;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	printf("\x1b[32m");
  printProgressBar(100);
  printf("\x1b[0m");
  printf("\n");
	//puts("chargement pile desc fini");
	fclose(fichier);
	// Sauvegarde de la pile de liens
	return p;
}

