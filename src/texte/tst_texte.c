#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./texte.h"


int main(int argc, char* argv[]){
	int nmbMots = 10;
	int ID = 0;


	PileDescripteurTexte maPileDescripteurTexte = initPileDescripteurTexte();
	PileLien maPileLienTexte = initPileLien();

	toutDescripteurTexte("03-Des_chercheurs_parviennent_à_régénérer.xml",&maPileDescripteurTexte,&maPileLienTexte,nmbMots,ID);
	affichePileDescripteurTexte(maPileDescripteurTexte);
	affichePileLien(maPileLienTexte);
	ID++;
/*
	toutDescripteurTexte("66.txt",&maPileDescripteurTexte,&maPileLienTexte,nmbMots,ID);
	affichePileDescripteurTexte(maPileDescripteurTexte);
	affichePileLien(maPileLienTexte);
	ID++;

	toutDescripteurTexte("180.txt",&maPileDescripteurTexte,&maPileLienTexte,nmbMots,ID);
	affichePileDescripteurTexte(maPileDescripteurTexte);
	affichePileLien(maPileLienTexte);
	ID++;
*/
	puts("debut de la sauvegarde");
	SauvegardePileDescripteurTexte(maPileDescripteurTexte,maPileLienTexte);
	puts("fin de la sauvegarde");

	return EXIT_SUCCESS;
}