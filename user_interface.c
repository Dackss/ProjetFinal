//
// Created by Thomas & Quentin on 14/06/2024.
//

#include "user_interface.h"
#include <math.h>

void start() {
    Population population = readCSV("../resources/200.csv");
    linkPopulation(&population);

    // Test de la fonction printPersonDetails qui inclut le test pour getSiblings
    for (int i = 0; i < population.size; i++) {
        printPersonDetails(&population.persons[i]);
    }
    testAncestorsPersons(&population);
    free(population.persons);
}

int isPerson(Person *person) {
    return person && person->id != 0;
}

char *getFullName(Person *person) {
    static char name[100]; // adjust size if necessary
    if(isPerson(person)) {
        sprintf(name, "%s %s", person->firstname, person->lastname);
        return name;
    } else {
        return "-";
    }
}

char *getSpouseName(Person *person) {
    static char spouseName[100]; // adjust size if necessary
    if(isPerson(person->p_spouse)) {
        sprintf(spouseName, "%s %s", person->p_spouse->firstname, person->p_spouse->lastname);
        return spouseName;
    } else {
        return "Aucun";
    }
}
void printChildren(int num_children, Person *person) {
    printf("Nombre d'enfants: %d\n", num_children);

    for (int j = 0; j < num_children; j++) {
        printf("Enfant %d: %s %s\n", j + 1, person->children[j]->firstname, person->children[j]->lastname);
    }
}

void printSiblings(Person *person, int *numSiblings) {
    Person **siblings = getSiblings(person, numSiblings);
    // Check numSiblings instead of siblings
    if (*numSiblings > 0 && siblings != NULL) {
        for (int i = 0; i < *numSiblings; i++) {
            printf("  - %s %s\n", siblings[i]->firstname, siblings[i]->lastname);
        }
        free(siblings);
    } else printf("  - Aucun\n");
}

void testAncestorsPersons(Population *population) {
    if (population->size > 0) {
        Person *person = &population->persons[1];
        int generations = 2;
        Person **ancestors = ancestorsPersons(*population, person);

        if (ancestors != NULL) {
            printf("Test ancestorsPersons:\n");
            for (int i = 1; i < pow(2, generations + 1) - 1; i++) {
                if (ancestors[i] != NULL) {
                    printf("Ancestor %d: %s %s\n", i, ancestors[i]->firstname, ancestors[i]->lastname);
                } else {
                    printf("Ancestor %d: NULL\n", i);
                }
            }
            free(ancestors);
        } else {
            printf("ancestorsPersons returned NULL\n");
        }
    } else {
        printf("Population is empty\n");
    }
}


void printPersonDetails(Person *person) {
    printf("ID: %d\n", person->id);
    printf("Nom: %s\n", person->lastname);
    printf("Prénom: %s\n", person->firstname);
    printf("Date de naissance: %02d/%02d/%04d\n", person->birthday, person->birthmonth, person->birthyear);
    printf("Region naissance: %s\n", person->region_naissance);
    printf("Père: %s\n", getFullName(person->p_father));
    printf("Mère: %s\n", getFullName(person->p_mother));
    printf("Conjoint: %s\n", getSpouseName(person));

    printChildren(person->num_children, person);

    printf("Frères et sœurs de %s %s:\n", person->firstname, person->lastname);
    int numSiblings = 0;
    printSiblings(person, &numSiblings);

    printf("\n");
}