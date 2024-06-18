//
// Created by Thomas & Quentin on 14/06/2024.
//

#include "../include/population.h"

void insert(Population * p, int key, Person *data) {
    if (p->size >= p->capacity) {
        fprintf(stderr, "Erreur : capacité maximale atteinte\n");
        return;
    }

    // Check for duplicates
    for (int i = 0; i < p->size; ++i) {
        if (p->persons[i].id == key) {
            fprintf(stderr, "Erreur : Personne avec l'ID %d existe déjà\n", key);
            return;
        }
    }

// Add the new person with the specified ID
    data->id = key;
    p->persons[p->size++] = *data;
}

// Function to add a child to the parent
void addChild(Person *parent, Person *child) {
    if (parent->num_children < parent->max_children) {
        parent->children[parent->num_children++] = child;
    } else {
        // Manage the case where the number of children exceeds the initial capacity
        // For simplicity, we don't do anything here, but in a real case,
        // it might be necessary to enlarge the table or handle it in other ways.
    }
}

// Recursive function to create parental links and increment num_children
    void createTree(Person *person, Population *population) {
    Person *unknown = &population->persons[0]; // Unknown person with ID 0

    if (person->father_id != 0 && person->p_father == NULL) {
        // Find and assign the father
        for (int j = 0; j < population->size; j++) {
            if (population->persons[j].id == person->father_id) {
                person->p_father = &population->persons[j];
                addChild(person->p_father, person);
                createTree(person->p_father, population);
                break;
            }
        }
        if (person->p_father == NULL) {
            person->p_father = unknown;
        }
    }

    if (person->mother_id != 0 && person->p_mother == NULL) {
        // Find and assign the mother
        for (int j = 0; j < population->size; j++) {
            if (population->persons[j].id == person->mother_id) {
                person->p_mother = &population->persons[j];
                addChild(person->p_mother, person);
                createTree(person->p_mother, population);
                break;
            }
        }
        if (person->p_mother == NULL) {
            person->p_mother = unknown;
        }
    }

    if (person->p_mother != NULL && person->p_father != NULL) {
        // Assign spouses
        person->p_father->p_spouse = person->p_mother;
        person->p_mother->p_spouse = person->p_father;
    }
}

// Function to link the entire population
void linkPopulation(Population *population) {
    for (int i = 0; i < population->size; i++) {
        createTree(&population->persons[i], population);
    }

    // Initialize spouses not found to "unknown" person
    Person *unknown = &population->persons[0];
    for (int i = 0; i < population->size; i++) {
        Person *person = &population->persons[i];
        if (person->p_father == NULL) {
            person->p_father = unknown;
        }
        if (person->p_mother == NULL) {
            person->p_mother = unknown;
        }
        if (person->p_spouse == NULL) {
            person->p_spouse = unknown;
        }
    }
}
