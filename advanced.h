//
// Created by Thomas & Quentin on 14/06/2024.
//

#ifndef PROJETFINAL_ADVANCED_H
#define PROJETFINAL_ADVANCED_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "person.h"
#include "population.h"
#include <math.h>


Person** getSiblings(Person* person, int* count);

Person **ancestorsPersons(Population *population, Person *person);

#endif //PROJETFINAL_ADVANCED_H
