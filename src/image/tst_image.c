#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./image.h"


int main(int argc, char* argv[]){
	int nmb_bits = 2;
	int id = 0;
	bool chargement = true;
	bool sauvegarde = false;

	PileLien maPileLienImage;
	PileDescripteurImage maPileDescripteurImage;

	if(chargement){
		maPileDescripteurImage = chargePileDescripteurImage(nmb_bits,&id); 
		maPileLienImage =chargePileLien("../../sauvegarde/Descripteur_image/liste_base_image");
	}else{
		PileDescripteurImage maPileDescripteurImage = initPileDescripteurImage();
		PileLien maPileLienImage = initPileLien();
		
		toutDescripteurImage("01.txt",&maPileDescripteurImage,&maPileLienImage,nmb_bits,id);
		id++;
		toutDescripteurImage("02.txt",&maPileDescripteurImage,&maPileLienImage,nmb_bits,id);
		id++;
		toutDescripteurImage("51.txt",&maPileDescripteurImage,&maPileLienImage,nmb_bits,id);
	}




	
	affichePileLien(maPileLienImage);
	affichePileDescripteurImage(maPileDescripteurImage);

	printf("%d id (3 normalement)\n",id);
	if(sauvegarde){
		SauvegardePileDescripteurImage(maPileDescripteurImage,maPileLienImage);
	}
	
	return EXIT_SUCCESS;
}