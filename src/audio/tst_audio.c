#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./audio.h"


//int main(int argc, char* argv[]){
int main(){
  /* Voici une proposition des tests de bases : */

  // test 1 : initialisation et l'affichage d'un descripteur

  // test 2 : initialisation et l'affichage d'une pile des descripteurs

  // test 3 : empiler la pile des descripteurs et afficher le resultat

  // test 4 : utiliser la fonciton getter pour recouperer un descripteur de la pile et l'afficher 

  // test 5 : initialisation et l'affichage d'un lien entre descripteur et fichier (il devrait etre vide)

  // test 6 : utiliser un setter pour creer un lien avec le fichie, ensuite un setter pour creer un lien avec le descripteur, afficher le lien (il devrait contenir le nom du fichier et son descripteur)


  // test 7 : initialisation de la pile qui contiendra des liens et l'affichage


  // test 8 : creer un nouveau descripteur, l'ajouter a la pile des descripteurs, creer un lien entre la pile et le nom du fichier et ajouter le lien a la pile correspendante. afficher la pile des descripteur et la pile des liens (il y devrait etre deux eleents)

  // test 9 : calculer la distance entre 2 descripteur crées precedament

	PileDescripteurAudio maPileDescripteurAudio = initPileDescripteurAudio();
	PileLien maPileLienAudio = initPileLien();

	puts("Premier");
	toutDescripteurAudio("jingle_fi15.txt",&maPileDescripteurAudio,&maPileLienAudio, 50, 1);
	puts("Premier");
	affichePileDescripteurAudio(maPileDescripteurAudio);
	affichePileLien(maPileLienAudio);

	toutDescripteurAudio("jingle_fi10.txt",&maPileDescripteurAudio,&maPileLienAudio, 50, 11);
	affichePileDescripteurAudio(maPileDescripteurAudio);
	affichePileLien(maPileLienAudio);

	toutDescripteurAudio("corpus_fi.txt",&maPileDescripteurAudio,&maPileLienAudio, 50, 2);
	affichePileDescripteurAudio(maPileDescripteurAudio);
	affichePileLien(maPileLienAudio);

	return EXIT_SUCCESS;
}