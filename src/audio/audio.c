#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "./audio.h"

CelluleAudio* initCelAudio(DescripteurAudio el){
	CelluleAudio* c = (CelluleAudio*)malloc(sizeof(CelluleAudio));
	c->suivant = NULL;
	//puts("debut affectation");
	affectDescripteurAudio(&el,&(c->descripteur));
	//puts("fin affectation");

	return c;
}

PileDescripteurAudio initPileDescripteurAudio(){
	PileDescripteurAudio p;
	p.taille = 0;
	p.tete = NULL;
	return p;
}

PileDescripteurAudio empileDescripteurAudio(PileDescripteurAudio p,DescripteurAudio d){
	CelluleAudio* c = initCelAudio(d);
	if(p.taille!=0){
		c->suivant = p.tete;
	}
	p.tete = c;
	p.taille++;
	return p;
}

PileDescripteurAudio depileDescripteurAudio(PileDescripteurAudio p){
	if(p.taille==0){
		printf("Erreur : votre pile est déjà vide !\n");
	}else{
		CelluleAudio* cel = p.tete;
		p.tete = p.tete->suivant;
		free(cel);
		p.taille--;
	}
	return p;
}


// pas besoin de passer un pointeur de pile !!!!!!
DescripteurAudio* getDescripteurAudio(PileDescripteurAudio p,int x){
	CelluleAudio* courant = p.tete;
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

DescripteurAudio* getDescripteurAudioViaId(PileDescripteurAudio p,int id){
	CelluleAudio* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(getIdDescripteurAudio(courant->descripteur)==id){
			pasTrouve = 0;
		}
		i++;
	}
	if(pasTrouve){
		puts("Le descripteur n'a pas été trouvé");
		return NULL;
	}
	//puts("Le descripteur a été trouvé");
	return &(courant->descripteur);
}

DescripteurAudio* getDescripteurAudioViaNom(PileDescripteurAudio p,char nom[50]){
	CelluleAudio* courant;
	int i = 0;
	int pasTrouve = 1;
	while(i<p.taille && pasTrouve){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		if(strcmp( nom, getNomDescripteurAudio(courant->descripteur))==0){
			pasTrouve = 0;
		}
		i++;
	}
	if(pasTrouve){
		puts("Le descripteur n'a pas été trouvé");
		return NULL;
	}
	//puts("Le descripteur a été trouvé");
	return &(courant->descripteur);

}


void affichePileDescripteurAudio(PileDescripteurAudio p){
	printf("============================\nPile de [%d] descripteurs\n",p.taille);
	CelluleAudio* courant;
	for(int i=0;i<p.taille;i++){
		if(i==0){
			courant = p.tete;
		}else{
			courant = courant->suivant;
		}
		printf("[%d] ",i);
		afficheDescripteurAudio(courant->descripteur);
		puts("");
	}
	puts("============================");
}

void freePileDescripteurAudio(PileDescripteurAudio* p){
	//printf("p->taille = %d\n",p->taille);
	int nombre = p->taille;
	if(nombre >0){
		for(int i =0;i<nombre;i++){
			*p = depileDescripteurAudio(*p);
		}
		//puts("\nPile detruite\n");
	}else{
		//puts("\nPile deja vide\n");
	}
}


int toutDescripteurAudio(char* nomDuFichier,PileDescripteurAudio* p,PileLien* l,int nombreIntervalle,int ID){
	DescripteurAudio desc = creerDescripteurAudio(nomDuFichier,nombreIntervalle,ID);
	//puts("creation du descripteur fini");
	Lien lien = creerLien(desc.nom,desc.ID);
	//puts("creation du lien fini");
	*p = empileDescripteurAudio(*p, desc);
	//puts("fin empilement1");
	*l = empileLien(*l, lien);
	//puts("fin empilement2\n");
	return EXIT_SUCCESS;
}



int SauvegardePileDescripteurAudio(PileDescripteurAudio p,PileLien l){
  
	FILE* fichier = NULL;
	// Sauvegarde de la Pile de descripteurs
	fichier = fopen("./sauvegarde/Descripteur_audio/Base_descripteur_audio","w");
	if(fichier == NULL){
		puts("Base_descripteur_audio n'existe pas ou n'est pas trouvé");
	}
	fprintf(fichier,"%d\n",p.taille);
	int pourcentage;
	printf("\x1b[33m");
	for(int i =0;i<p.taille;i++){
		sauvegarderDescripteurAudio(fichier,*getDescripteurAudio(p,i));
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
	sauvegardePileLien(l,"./sauvegarde/Descripteur_audio/Liste_base_audio");
	return 0;
}


PileDescripteurAudio chargePileDescripteurAudio(int*id){
  int pourcentage;
	FILE* fichier = NULL;
	// Sauvegarde de la Pile de descripteurs
	int taille;
	PileDescripteurAudio p = initPileDescripteurAudio();
	fichier = fopen("./sauvegarde/Descripteur_audio/Base_descripteur_audio","r");
	if(fichier == NULL){
		puts("Base_descripteur_audio n'existe pas ou n'est pas trouvé");
		return p;
	}
	fscanf(fichier,"%d\n",&taille);
	*id = taille;
	printf("\x1b[33m");
	for(int i =0;i<taille;i++){
		p = empileDescripteurAudio(p,chargerDescripteurAudio(fichier));
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

