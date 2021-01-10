#include <stdio.h>
#include <stdlib.h>
#include "./pile_dossier.h"


Pile* new_Pile(){
	Pile* p = (Pile*)malloc(sizeof(Pile));
	p->tete = NULL;
	p->taille = 0;
	return p;
}

void empile(Pile* p,char* nom_fichier){
	Element* ptr_e = (Element*)malloc(sizeof(Element));
	ptr_e->nom = nom_fichier;
	ptr_e->next = NULL;
	if(p->taille == 0){
		p->tete = ptr_e;
	}else{
		ptr_e->next = p->tete;
		p->tete = ptr_e;
	}
	p->taille++;
}

void affiche(Pile* p){
	Element* ptr_e;
	printf("[Pile de %d Fichier]\n",p->taille);
	for(int i=0;i<p->taille;i++){
		if(i==0){
			ptr_e = p->tete;
		}else{
			ptr_e = ptr_e->next;
		}
		printf("[%d] nom = %s\n",i,ptr_e->nom);

	}
	printf("[Fin Pile]\n");

}

void destroy(Pile* p){
	if(p->taille >0){
		Element* courant = p->tete;
		Element* prochain = courant->next;
		do {
			courant = prochain;
			prochain = prochain->next;
			free(courant);
		} while(prochain != NULL );
		free(p->tete);
	}
	free(p);
	printf("Pile detruite\n");
}
