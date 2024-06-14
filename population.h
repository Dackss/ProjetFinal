//
// Created by Thomas & Quentin on 14/06/2024.
//

#ifndef PROJETFINAL_POPULATION_H
#define PROJETFINAL_POPULATION_H

#include "person.h"
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 41

typedef struct{
    Person* persons;
    int size;        // Nombre actuel de personnes dans la population
    int capacity;    // Taille maximale du tableau
} Population;

void insert(Population * p, int key, Person *data);
void addChild(Person *parent, Person *child);
void createTree(Person *person, Population *population);
void linkPopulation(Population *p);

#endif //PROJETFINAL_POPULATION_H
