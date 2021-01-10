#include <stdio.h>
#include <stdlib.h>

#include "./chargement.h"

int main(int argc,char* argv[]){
	printf("Main\n");
	Pile* p = get_files("data/texte");
	affiche(p);
	destroy(p);

	p = get_files("src/chargement");
	affiche(p);
	destroy(p);

	return EXIT_SUCCESS;
}