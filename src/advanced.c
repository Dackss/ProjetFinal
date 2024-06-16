//
// Created by Thomas & Quentin on 14/06/2024.
//

#include "../include/advanced.h"

Person** getSiblings(Person* person, int* count) {
    Person** siblings = malloc(CAPACITY * sizeof(Person *));
    *count = 0;

    // Check siblings from father side
    if (person->p_father != NULL && person->p_father->id != 0) {
        for (int i = 0; i < person->p_father->num_children; i++) {
            Person* child = person->p_father->children[i];
            if (child != person) {
                siblings[*count] = child;
                (*count)++;
            }
        }
    }

    // Check siblings from mother side
    if (person->p_mother != NULL && person->p_mother->id != 0) {
        for (int i = 0; i < person->p_mother->num_children; i++) {
            Person* child = person->p_mother->children[i];
            if (child != person) {
                // We ensure the sibling was not already added from father's side
                int siblingAlreadyAdded = 0;
                for(int j = 0; j < *count; j++) {
                    if(siblings[j] == child){
                        siblingAlreadyAdded = 1;
                        break;
                    }
                }

                if(!siblingAlreadyAdded) {
                    siblings[*count] = child;
                    (*count)++;
                }
            }
        }
    }

    return siblings;
}

Person** ancestorsPersons(Population population, Person *person) {
    // Calculate the size of the array based on the number of generations
    int array_size = pow(2, GENERATIONS + 1) - 1;

    // Allocate memory for the array
    Person **ancestors = malloc(array_size * sizeof(Person*));

    // Check if the memory was allocated successfully
    if (ancestors == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Set the first index to the person
    ancestors[0] = person;

    // Loop through the array and set the parents
    for (int i = 0; i < array_size / 2; i++) {
        if (ancestors[i] != NULL) {
            ancestors[2 * i + 1] = ancestors[i]->p_father;
            ancestors[2 * i + 2] = ancestors[i]->p_mother;
        }
        else {
            ancestors[2 * i + 1] = NULL;  // Unknown person
            ancestors[2 * i + 2] = NULL;  // Unknown person
        }
    }

    return ancestors;
}