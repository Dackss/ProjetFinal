//
// Created by Thomas & Quentin on 14/06/2024.
//

#ifndef PROJETFINAL_MENU_H
#define PROJETFINAL_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "population.h"
#include "filemanager.h"
#include "advanced.h"
#include "person.h"

void startMenu();
void printPersonDetails(Person *person);
void printChildren(int num_children, Person *person);
void printSiblings(Person *person, int *numSiblings);
int isPerson(Person *person);
char *getFullName(Person *person);
char *getSpouseName(Person *person);

#endif //PROJETFINAL_MENU_H
