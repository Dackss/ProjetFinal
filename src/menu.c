#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "advanced.h"

/**
 * @param person Person to check
 * @return 1 if the person is valid, 0 otherwise
 * A if statement is used to check if the person is not NULL and if the id of the person is different from 0
 */
int isPerson(Person *person) {
    return person && person->id != 0;
}


/**
 * @param person A pointer to a Person structure.
 * @return A pointer to a string containing the full name of the person, or "-" if the person is not valid.
 * This function takes a pointer to a Person structure, checks if the person is valid, and then constructs a full name by concatenating the first name and the last name.
 * If the person is not valid, it returns a string with a single character "-".
 */
char *getFullName(Person *person) {
    if (isPerson(person)) {
        // Calculate the required length for the full name
        size_t length = strlen(person->firstname) + strlen(person->lastname) + 2; // +1 for space, +1 for null terminator
        char *name = (char *)malloc(length * sizeof(char)); // Allocate memory dynamically

        if (name != NULL) {
            sprintf(name, "%s %s", person->firstname, person->lastname); // Concatenate first name and last name
            return name;
        } else {
            return NULL; // For memory allocation failure
        }
    } else {
        char *unknown = (char *)malloc(2 * sizeof(char)); // Allocate memory for "-"
        if (unknown != NULL) {
            strcpy(unknown, "-");
            return unknown;
        } else {
            // Handle memory allocation failure
            return NULL;
        }
    }
}

/**
 * @param person A pointer to a Person structure.
 * @return A pointer to a string containing the spouse's full name, or "Aucun" if the spouse is not valid.
 * This function takes a pointer to a Person structure, checks if the spouse is valid, and then constructs a full name by concatenating the spouse's first name and last name.
 * If the spouse is not valid, it returns a string with "Aucun".
 */
char *getSpouseName(Person *person) {
    if (isPerson(person->p_spouse)) {
        // Calculate the required length for the spouse's full name
        size_t length = strlen(person->p_spouse->firstname) + strlen(person->p_spouse->lastname) + 2; // +1 for space, +1 for null terminator
        char *spouseName = (char *)malloc(length * sizeof(char)); // Allocate memory dynamically

        if (spouseName != NULL) {
            sprintf(spouseName, "%s %s", person->p_spouse->firstname, person->p_spouse->lastname); // Concatenate first name and last name
            return spouseName;
        } else {
            return NULL; // For memory allocation failure
        }
    } else {
        char *noSpouse = (char *)malloc(6 * sizeof(char)); // Allocate memory for "Aucun"
        if (noSpouse != NULL) {
            strcpy(noSpouse, "Aucun");
            return noSpouse;
        } else {
            // Handle memory allocation failure
            return NULL;
        }
    }
}

/**
 * @param num_children The number of children.
 * @param person A pointer to a Person structure.
 * This function takes the number of children and a pointer to a Person structure, then prints the full name of each child.
 */
void printChildren(int num_children, Person *person) {
    // Print the number of children
    printf("Nombre d'enfants: %d\n", num_children);

    // Loop through each child and print their full name
    for (int j = 0; j < num_children; j++) {
        printf("Enfant %d: %s %s\n", j + 1, person->children[j]->firstname, person->children[j]->lastname);
    }
}

/**
 * @param person A pointer to a Person structure.
 * @param numSiblings A pointer to an integer to store the number of siblings.
 * This function takes a pointer to a Person structure and a pointer to an integer, retrieves the siblings of the person,
 * and prints their full names. If there are no siblings, it prints "Aucun".
 */
void printSiblings(Person *person, int *numSiblings) {
    // Create an array of pointers to the siblings
    Person **siblings = getSiblings(person, numSiblings);

    // Check if there are any siblings
    if (*numSiblings > 0 && siblings != NULL) {
        // Loop through each sibling and print their full name
        for (int i = 0; i < *numSiblings; i++) {
            printf("  - %s %s\n", siblings[i]->firstname, siblings[i]->lastname);
        }
    } else {
        // Print a message indicating there are no siblings
        printf("  - Aucun\n");
    }
    // Free the memory allocated for the siblings array
    free(siblings);
}

/**
 * @param population The population structure containing all persons.
 * @param person A pointer to a Person structure.
 * This function takes a pointer to a Person structure and a population, retrieves the ancestors of the person,
 * and prints their full names. If an ancestor's ID is 0, it prints "Inconnu".
 */
void printAncestors(Population population, Person *person) {
    // Create an array of pointers to the ancestors
    Person **ancestors = ancestorsPersons(population, person);

    // Check if the ancestors array is not NULL
    if (ancestors != NULL) {
        // Loop through each ancestor and print their full name
        for (int i = 0; i < pow(2, GENERATIONS + 1) - 1; i++) {
            if (ancestors[i] != NULL) {
                if (ancestors[i]->id == 0) {
                    // Print "Inconnu" for unknown ancestors
                    printf("  - Inconnu\n");
                } else {
                    // Print the full name of the ancestor
                    printf("  - %s %s\n", ancestors[i]->firstname, ancestors[i]->lastname);
                }
            }
        }
        // Free the memory allocated for the ancestors array
        free(ancestors);
    }
}

/**
 * @param person A pointer to a Person structure.
 * This function takes a pointer to a Person structure and prints the details of the person,
 * including ID, last name, first name, date of birth, region of birth, parents' names, spouse's name,
 * children's names, and siblings' names.
 */
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