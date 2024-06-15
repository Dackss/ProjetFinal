#include "advanced.h"

Person** getSiblings(Person* person, int* count) {
    Person** siblings = malloc(10 * sizeof(Person *));
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