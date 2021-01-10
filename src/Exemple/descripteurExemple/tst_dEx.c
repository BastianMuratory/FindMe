#include<stdio.h>
#include<stdlib.h>

#include "dEx.h"

int main(int argc,char* argv[]){
	DescripteurExemple e = creerDecripteurDuExemple("10.txt");
	afficheDescripteurExemple(e);
	puts("\ntest affectation");
	DescripteurExemple e2; 
	affectDescripteurExemple(&e,&e2);
	//e2 = creerDecripteurDuExemple("12");
	afficheDescripteurExemple(e2);
	printf("\nLa distance entre e et e2 est %d\n",distanceDescripteurExemple(e,e2));

	return EXIT_SUCCESS;
}
