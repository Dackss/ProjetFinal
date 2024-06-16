//
// Created by Thomas & Quentin on 14/06/2024.
//
#include "../include/person.h"
#include "../include/population.h"
#define MAX_NAME_LETTER 25
#define MAX_HTML_LETTER 50

//Changer donner de la struct en html
int titleHTMLtoPerso(char * buffer, Person * p) {

    //vérifier pointeurs non nuls
    if(!buffer || !p){
        return 0; // echec
    }

    //générer le titre html
    int THtml = printf(buffer, MAX_HTML_LETTER, "<title> %d; %s %s </title>", p->id, p->firstname, p->lastname);

    //Vérifier la génération du titre
    if(THtml<0 || THtml >= MAX_HTML_LETTER){
        return 0;
    }
    return THtml;
}

//convertir un arbre en tableau
int  treeToTableau(Population *p, Person *root, Person **tableau, int index){

    //racine nulle
    if(root == 0){
        return index;
    }

    //Ajout d'une personne
    if(root == tableau[index]){
        return index++;
    }

    //Regarde si la personne a des enfants
    for(int i=0; i<root->num_children;i++){

        //appel recusif de la fonction treeToTableau lorsqu'un fils a été trouvé
        if(root->num_children!=0){
            index = treeToTableau(p,root->children[i], tableau, index);

        }
    }
}

void exportTableau_HTML(Population *p, const char *filename){

    }
}
