//
// Created by Thomas & Quentin on 14/06/2024.
//

#ifndef PROJETFINAL_PERSON_H
#define PROJETFINAL_PERSON_H

typedef struct {
    int id;
    int father_id;
    int mother_id;
    char lastname[20];
    char firstname[20];
    int birthday; int birthmonth; int birthyear;
    char birthzipcode[30];
    struct person * p_father;
    struct person * p_mother;
    struct person ** children;
    int num_children;
} Person;

#endif //PROJETFINAL_PERSON_H
