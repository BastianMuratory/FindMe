#ifndef __F_main_H__
#define __F_main_H__

#include <stdbool.h>

void clear (void);

void color(char* couleur);

void connection(bool* admin);

void affichage(bool admin,int *x,int vT,int vI,int vA,bool indT,bool indI,bool indA,int der_texte,int der_image,int der_audio); // affiche le menu 


void logo();

void merci();
void erreur_relancer_indexation();


void changer_param_text(int* param,bool*); // renvoie false si le parramètre a été changé

void changer_param_image(int* param,bool*);

void changer_param_audio(int* param,bool*);



#endif

