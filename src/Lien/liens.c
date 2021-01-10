#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "./liens.h"

#define tailleMax 50
/*
typedef struct s_CelExemple{ // le descripteur de Exemple
	Lien descripteur;
	struct s_CelExemple* suivant;
}CelluleLien;

typedef struct s_pileLien{
	int taille;
	CelluleLien* tete;
}PileLien;
*/

void printProgressBar(int pourcentage) {
  int fill_bar = pourcentage/(100/TAILLE_PROGRESS_BAR);
  printf("\r[");
  for(int i=0; i<TAILLE_PROGRESS_BAR; i++) {
    if(i+1 <= fill_bar) {
      printf("#");
    } else {
      printf("-");
    }
  }
  printf("]%3d%%", pourcentage);
}

CelluleLien* initialiseCellule(Lien el){
	CelluleLien* c = (CelluleLien*)malloc(sizeof(CelluleLien));
	c->suivant = NULL;
	affectLien(&el,&(c->descripteur));
	return c;
}

PileLien initPileLien(){
	PileLien p;
	p.taille = 0;
	p.tete = NULL;
	return p;
}

PileLien empileLien(PileLien p,Lien d){
	CelluleLien* c = initialiseCellule(d);
	if(p.taille!=0){
		c->suivant = p.tete;
	}
	p.tete = c;
	p.taille++;
	return p;
}




// pas besoin de passer un pointeur de pile !!!!!!
Lien* getLien(PileLien p,int x){
	CelluleLien* courant = p.tete;
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

Lien* getLienViaId(PileLien p,int id){
	CelluleLien* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(getIdLien(courant->descripteur)==id){
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

Lien* getLienViaNom(PileLien p,char nom[50]){
	CelluleLien* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(strcmp( nom, getNomLien(courant->descripteur))==0){
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


void affichePileLien(PileLien p){
	printf("============================\nPile de [%d] Liens\n",p.taille);
	CelluleLien* courant;
	for(int i=0;i<p.taille;i++){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		printf("[%d]",i);
		afficheLien(courant->descripteur);
	}
	puts("============================");
}

//retourne l'indice si nomFichier est un fichier déjà présent dans la pile de liens sinon -1
int dejaVu(char* nomFichier,PileLien p){
	CelluleLien* courant;
	int present = -1;
	for(int i=0;i<p.taille;i++){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(strcmp(courant->descripteur.nomFichier,nomFichier)==0)present = i;
	}
	return present;
}

PileLien depileLien(PileLien p){
	if(p.taille==0){
		printf("Erreur : votre pile est déjà vide !\n");
	}else{
		CelluleLien* cel = p.tete;
		p.tete = p.tete->suivant;
		free(cel);
		p.taille--;
	}
	return p;
}

void freePileLien(PileLien* p){
	int nombre = p->taille;
	if(nombre >0){
		for(int i =0;i<nombre;i++){
			*p = depileLien(*p);
		}
		//puts("Pile liens vidée");
	}else{
		//puts("Pile liens deja vide");
	}
}

void sauvegardePileLien(PileLien p,char* nomFichier){
	FILE* fichier = NULL;
	fichier = fopen(nomFichier,"w");
	if(fichier==NULL)puts("fichier pas bon\n");

	CelluleLien* courant;
	fprintf(fichier,"%d\n",p.taille);
	for(int i = 0;i<p.taille;i++){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		fprintf(fichier,"ID=%d,NOM=%s\n",courant->descripteur.ID,courant->descripteur.nomFichier);
	}
}

PileLien chargePileLien(char* nomFichier){
	FILE* fichier = NULL;
	PileLien p = initPileLien();
	fichier = fopen(nomFichier,"r");
	if(fichier == NULL){
		printf("Le fichier de liens n'existe pas\n");
		return p;
	}
	int taille = 0;
	fscanf(fichier,"%d\n",&taille);
	
	for(int i = 0;i<taille;i++){
		char nom[tailleMax];
		int id = -1;
		fscanf(fichier,"ID=%d,NOM=%s\n",&id,nom);
		Lien l = creerLien(nom,id);
		p = empileLien(p,l);
	}
	return p;
}





