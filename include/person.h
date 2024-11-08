//
// Created by Thomas & Quentin on 14/06/2024.
//

#ifndef PROJETFINAL_PERSON_H
#define PROJETFINAL_PERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10

//This structure brings together all the important elements of a person
typedef struct person {
    int id;
    int father_id;
    int mother_id;
    char lastname[20];
    char firstname[20];
    int birthday; int birthmonth; int birthyear;
    char region_naissance[30];
    struct person *p_father; // Pointeur vers la structure Person du père
    struct person *p_mother; // Pointeur vers la structure Person de la mère
    struct person *p_spouse; // Pointeur vers le conjoint
    struct person **children; // Tableau de pointeurs vers les enfants
    int num_children; // Nombre d'enfants
    int max_children; // Nombre maximal d'enfants
    int gender;
} Person;

Person * initPerson(char *csvline);

#endif //PROJETFINAL_PERSON_H
