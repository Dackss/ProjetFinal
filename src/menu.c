#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "advanced.h"

int isPerson(Person *person) {
    return person && person->id != 0;
}

char *getFullName(Person *person) {
    static char name[100]; // ajuster la taille si nécessaire
    if (isPerson(person)) {
        sprintf(name, "%s %s", person->firstname, person->lastname);
        return name;
    } else {
        return "-";
    }
}

char *getSpouseName(Person *person) {
    static char spouseName[100]; // ajuster la taille si nécessaire
    if (isPerson(person->p_spouse)) {
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

void printAncestors(Population population, Person *person) {
    Person **ancestors = ancestorsPersons(population, person);
    if (ancestors != NULL) {
        for (int i = 0; i < pow(2, GENERATIONS + 1) - 1; i++) {
            if (ancestors[i] != NULL) {
                if (ancestors[i]->id == 0) {
                    printf("  - Inconnu\n");
                } else {
                    printf("  - %s %s\n", ancestors[i]->firstname, ancestors[i]->lastname);
                }
            }
        }
        free(ancestors);
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