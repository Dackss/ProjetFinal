//
// Created by Thomas & Quentin on 14/06/2024.
//

#include "population.h"

void insert(Population * p, int key, Person *data) {
    if (p->size >= p->capacity) {
        fprintf(stderr, "Erreur : capacité maximale atteinte\n");
        return;
    }

    // Vérifier les doublons
    for (int i = 0; i < p->size; ++i) {
        if (p->persons[i].id == key) {
            fprintf(stderr, "Erreur : Personne avec l'ID %d existe déjà\n", key);
            return;
        }
    }

    // Ajouter la nouvelle personne avec l'ID spécifié
    data->id = key;
    p->persons[p->size++] = *data;
}

void linkPopulation(Population* p) {
    for (int i = 0; i < p->size; i++) {
        //p->persons[i].children = malloc(sizeof(Person*));
        Person *current = &p->persons[i];
        if(&p->persons[current->father_id] != NULL) {
            (&p->persons[current->id])->p_father = (struct person *) &p->persons[current->father_id];
        }
        if(&p->persons[current->mother_id] != NULL) {
            (&p->persons[current->id])->p_mother = (struct person *) &p->persons[current->mother_id];
        }
    }
}