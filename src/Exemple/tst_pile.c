#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./pile.h"



int main(int argc, char* argv[]){
	PileDescripteurExemple maPileDescripteurExemple = initPileDescripteurExemple();
	PileLien maPileLienExemple = initPileLien();

	toutDescripteurExemple("10.txt",&maPileDescripteurExemple,&maPileLienExemple);
	affichePileDescripteurExemple(maPileDescripteurExemple);
	affichePileLien(maPileLienExemple);

	toutDescripteurExemple("66.txt",&maPileDescripteurExemple,&maPileLienExemple);
	affichePileDescripteurExemple(maPileDescripteurExemple);
	affichePileLien(maPileLienExemple);

	toutDescripteurExemple("180.txt",&maPileDescripteurExemple,&maPileLienExemple);
	affichePileDescripteurExemple(maPileDescripteurExemple);
	affichePileLien(maPileLienExemple);

	return EXIT_SUCCESS;
}