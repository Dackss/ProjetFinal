//
// Created by Thomas & Quentin on 14/06/2024.
//

#ifndef PROJETFINAL_USER_INTERFACE_H
#define PROJETFINAL_USER_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "population.h"
#include "filemanager.h"
#include "advanced.h"
#include "person.h"

void printPersonDetails(Person *person);
void testAncestorsPersons(Population *population);
void start();

#endif //PROJETFINAL_USER_INTERFACE_H
