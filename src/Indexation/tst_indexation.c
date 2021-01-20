#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "indexation.h"


int main(){
	//bool image = false;
	//bool audio = false;
	bool texte = true;

  // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	// $$$$$$$$$$ fichiers image $$$$$$$$$$
	// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

	/*
	if(image){
		int id = 0;
		int n_bits = 2;
		PileDescripteurImage p;
		PileLien l;
		bool charge = true;
		bool sauvegarde = true;
		if(charge){
			p = chargePileDescripteurImage(&id);
			l = chargePileLien
			("../../sauvegarde/Descripteur_image/liste_base_image");
		}else{
			p = initPileDescripteurImage();
			l = initPileLien();
		}
		

		//indexation_fichiers_images(&p,&l,n_bits,&id);
		//puts("###################\nINDEXATION TERMINEE\n###################");
		// somme des min
		//affichePileDescripteurImage(p);
		//affichePileLien(l);



		rechercher_image(&p,&l,n_bits,4);
		rechercher_image(&p,&l,n_bits,4);
		rechercher_image(&p,&l,n_bits,4);

		if(sauvegarde){
			SauvegardePileDescripteurImage(p,l);
			//puts("fichiers sauvegardés\n");
		}
	}
	// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	// $$$$$$$$$$ fichiers audio $$$$$$$$$$
	// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	if(audio){
		int id2 = 0;
		int nb_Intervalles=50;
		PileDescripteurAudio pileAudio;
		PileLien pileLienAudio;
		bool charge2 = true;
		bool sauvegarde2 = false;
		//puts("test1");
		if(charge2){
			pileAudio = chargePileDescripteurAudio(&id2);
			pileLienAudio = chargePileLien("../../sauvegarde/Descripteur_audio/Liste_base_audio");
		}else{
			pileAudio = initPileDescripteurAudio();
			pileLienAudio = initPileLien();
		}
		
		//int test;
		//test = indexation_fichiers_audio(&pileAudio, &pileLienAudio ,nb_Intervalles, &id2);
		//printf("test=%d\n",test);
		puts("###################\nINDEXATION TERMINEE\n###################");
		affichePileDescripteurAudio(pileAudio);
		rechercher_audio(&pileAudio,&pileLienAudio,nb_Intervalles,9);
		if(sauvegarde2){
			SauvegardePileDescripteurAudio(pileAudio,pileLienAudio);
			puts("\nLes fichiers sont sauvegardés\n");
		}
	}
	*/
	// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	// $$$$$$$$$$ fichiers texte $$$$$$$$$$
	// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

	if(texte){
		int id = 0;
		int n_mots = 20;
		PileDescripteurTexte p;
		PileLien l;
		bool charge = true;
		bool sauvegarde = true;
		if(charge){
			p = chargePileDescripteurTexte(&id);
			l = chargePileLien	("../../sauvegarde/Descripteur_texte/liste_base_texte");
		}else{
			p = initPileDescripteurTexte();
			l = initPileLien();
      indexation_fichiers_textes(&p,&l,n_mots,&id);
		}
		
		indexation_fichiers_textes(&p,&l,n_mots,&id);
		//puts("###################\nINDEXATION TERMINEE\n###################");
		
		//affichePileDescripteurTexte(p);
		//affichePileLien(l);

		rechercher_texte(&p,&l,n_mots,5);

		puts("===============================");
		
		rechercher_mots_texte(&p,5);


		//afficheDescripteurTexte(*getDescripteurTexteViaNom(p,"17-Une_équipe_française_a_réussi.xml"));
		//puts("");
		if(sauvegarde){
			SauvegardePileDescripteurTexte(p,l);
			//puts("fichiers sauvegardés\n");
		}

    freePileDescripteurTexte(&p);
	}

	return 0;
}