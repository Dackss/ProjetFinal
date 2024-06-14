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

// Fonction pour ajouter un enfant au parent
void addChild(Person *parent, Person *child) {
    if (parent->num_children < parent->max_children) {
        parent->children[parent->num_children++] = child;
    } else {
        // Gérer le cas où le nombre d'enfants dépasse la capacité initiale
        // Pour simplifier, nous ne faisons rien ici, mais dans un cas réel,
        // il pourrait être nécessaire d'agrandir le tableau ou de gérer autrement.
    }
}

// Fonction récursive pour créer les liens parentaux et incrémenter num_children
void createTree(Person *person, Population *population) {
    if (person->father_id != 0 && person->p_father == NULL) {
        // Trouver et assigner le père
        for (int j = 0; j < population->size; j++) {
            if (population->persons[j].id == person->father_id) {
                person->p_father = &population->persons[j];
                addChild(person->p_father, person);
                createTree(person->p_father, population);
                break;
            }
        }
    }

    if (person->mother_id != 0 && person->p_mother == NULL) {
        // Trouver et assigner la mère
        for (int j = 0; j < population->size; j++) {
            if (population->persons[j].id == person->mother_id) {
                person->p_mother = &population->persons[j];
                addChild(person->p_mother, person);
                createTree(person->p_mother, population);
                break;
            }
        }
    }
}

// Fonction pour lier toute la population
void linkPopulation(Population *population) {
    for (int i = 0; i < population->size; i++) {
        createTree(&population->persons[i], population);
    }
}