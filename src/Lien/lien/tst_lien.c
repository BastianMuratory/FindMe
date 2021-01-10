#include<stdio.h>
#include<stdlib.h>

#include "lien.h"



int main(int argc,char* argv[]){
	Lien e = creerLien("10.txt",10);
	afficheLien(e);
	puts("\ntest affectation");
	Lien e2; 
	affectLien(&e,&e2);
	afficheLien(e2);
	return EXIT_SUCCESS;
}
