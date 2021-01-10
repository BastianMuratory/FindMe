#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "./texte.h"

CelluleTexte* initCelTexte(DescripteurTexte el){
	CelluleTexte* c = (CelluleTexte*)malloc(sizeof(CelluleTexte));
	c->suivant = NULL;
	affectDescripteurTexte(&el,&(c->descripteur));
	return c;
}

PileDescripteurTexte initPileDescripteurTexte(){
	PileDescripteurTexte p;
	p.taille = 0;
	p.tete = NULL;
	return p;
}

PileDescripteurTexte empileDescripteurTexte(PileDescripteurTexte p,DescripteurTexte d){
	CelluleTexte* c = initCelTexte(d);
	if(p.taille!=0){
		c->suivant = p.tete;
	}
	p.tete = c;
	p.taille++;
	return p;
}

PileDescripteurTexte depileDescripteurTexte(PileDescripteurTexte p){
	if(p.taille==0){
		printf("Erreur : votre pile est déjà vide !\n");
	}else{
		CelluleTexte* cel = p.tete;
		p.tete = p.tete->suivant;
		free(cel);
		p.taille--;
	}
	return p;
}


// pas besoin de passer un pointeur de pile !!!!!!
DescripteurTexte* getDescripteurTexte(PileDescripteurTexte p,int x){
	CelluleTexte* courant = p.tete;
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

DescripteurTexte* getDescripteurTexteViaId(PileDescripteurTexte p,int id){
	CelluleTexte* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(getIdDescripteurTexte(courant->descripteur)==id){
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

DescripteurTexte* getDescripteurTexteViaNom(PileDescripteurTexte p,char nom[50]){
	CelluleTexte* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(strcmp( nom, getNomDescripteurTexte(courant->descripteur))==0){
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


void affichePileDescripteurTexte(PileDescripteurTexte p){
	printf("============================\nPile de [%d] descripteurs\n",p.taille);
	CelluleTexte* courant;
	for(int i=0;i<p.taille;i++){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		printf("[%d]",i);
		afficheDescripteurTexte(courant->descripteur);
		puts("");
	}
	puts("============================");
}

void freePileDescripteurTexte(PileDescripteurTexte* p){
	//printf("p->taille = %d\n",p->taille);
	int nombre = p->taille;
	if(nombre >0){
		for(int i =0;i<nombre;i++){
			*p = depileDescripteurTexte(*p);
		}
		//puts("\nPile detruite\n");
	}else{
		//puts("\nPile deja vide\n");
	}
}


int toutDescripteurTexte(char* nomDuFichier,PileDescripteurTexte* p,PileLien* l,int nmbMots,int ID){
	DescripteurTexte desc = creerDescripteurTexte(nomDuFichier,nmbMots,ID);
	Lien lien = creerLien(desc.nom,desc.ID);
	*p = empileDescripteurTexte(*p, desc);
	*l = empileLien(*l, lien);
	return EXIT_SUCCESS;
}


int SauvegardePileDescripteurTexte(PileDescripteurTexte p,PileLien l){
  int pourcentage;
	FILE* fichier = NULL;
	// Sauvegarde de la Pile de descripteurs
	fichier = fopen("./sauvegarde/Descripteur_texte/base_descripteur_texte","w");
	if(fichier == NULL){
		puts("base_descripteur_texte n'existe pas ou n'est pas trouvé");
	}
	fprintf(fichier,"%d\n",p.taille);
	printf("\x1b[33m");
	for(int i =0;i<p.taille;i++){
		sauvegarderDescripteurTexte(fichier,*getDescripteurTexte(p,i));
    pourcentage = ((i+1)*100)/p.taille;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	printf("\x1b[32m");
  printProgressBar(100);
  printf("\x1b[0m");
  printf("\n");
	fclose(fichier);
	// Sauvegarde de la pile de liens
	sauvegardePileLien(l,"./sauvegarde/Descripteur_texte/liste_base_texte");
	return 0;
}


PileDescripteurTexte chargePileDescripteurTexte(int*id){
	int pourcentage;
	FILE* fichier = NULL;
	// Sauvegarde de la Pile de descripteurs
	int taille;
	PileDescripteurTexte p = initPileDescripteurTexte();
	fichier = fopen("./sauvegarde/Descripteur_texte/base_descripteur_texte","r");
	if(fichier == NULL){
		puts("base_descripteur_texte n'existe pas ou n'est pas trouvé");
		return p;
	}
	printf("\x1b[33m");
	fscanf(fichier,"%d\n",&taille);
	*id = taille;
	for(int i =0;i<taille;i++){
		p = empileDescripteurTexte(p,chargerDescripteurTexte(fichier));
    pourcentage = ((i+1)*100)/taille;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	printf("\x1b[32m");
  printProgressBar(100);
  printf("\x1b[0m");
  printf("\n");
	puts("chargement pile desc fini");
	fclose(fichier);
	// Sauvegarde de la pile de liens
	return p;
}





