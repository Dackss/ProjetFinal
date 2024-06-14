//
// Created by dacks on 14/06/2024.
//

#include "user_interface.h"
#include "person.h"

void start() {
    Population population = readCSV("../resources/40.csv");

    linkPopulation(&population);

    // Afficher les détails des personnes ajoutées et leurs liens
    for (int i = 0; i < population.size; i++) {
        Person *person = &population.persons[i];
        printf("ID: %d\n", person->id);
        printf("Nom: %s\n", person->lastname);
        printf("Prénom: %s\n", person->firstname);
        printf("Date de naissance: %02d/%02d/%04d\n", person->birthday, person->birthmonth, person->birthyear);
        printf("Code postal: %s\n", person->region_naissance);

        if (person->p_father != NULL) {
            printf("Père: %s %s\n", person->p_father->lastname, person->p_father->firstname);
        } else {
            printf("Père: Inconnu\n");
        }

        if (person->p_mother != NULL) {
            printf("Mère: %s %s\n", person->p_mother->lastname, person->p_mother->firstname);
        } else {
            printf("Mère: Inconnu\n");
        }

        printf("Nombre d'enfants: %d\n", person->num_children);
        for (int j = 0; j < person->num_children; j++) {
            printf("Enfant %d: %s %s\n", j + 1, person->children[j]->firstname, person->children[j]->lastname);
        }
        printf("\n");
    }
    free(population.persons);
}