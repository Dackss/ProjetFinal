//
// Created by Thomas & Quentin on 14/06/2024.
//

#ifndef PROJETFINAL_HTMLEXPORT_H
#define PROJETFINAL_HTMLEXPORT_H

#include "person.h"
#include "population.h"

int titreHTMLtoPerso(char * buffer, Person * p);
int treeToTableau(Population *p, Person *root, Person **tableau, int index);
void exportTableau_HTML(Population *p, const char *filename);

#endif //PROJETFINAL_HTMLEXPORT_H
