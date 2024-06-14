//
// Created by Thomas & Quentin on 14/06/2024.
//

#include "user_interface.h"
#include "person.h"

void printPersonDetails(Person *person) {
    printf("ID: %d\n", person->id);
    printf("Nom: %s\n", person->lastname);
    printf("Prénom: %s\n", person->firstname);
    printf("Date de naissance: %02d/%02d/%04d\n", person->birthday, person->birthmonth, person->birthyear);
    printf("Code postal: %s\n", person->region_naissance);

    printf("Père: %s %s\n", person->p_father ? person->p_father->firstname : "-", person->p_father ? person->p_father->lastname : "-");
    printf("Mère: %s %s\n", person->p_mother ? person->p_mother->firstname : "-", person->p_mother ? person->p_mother->lastname : "-");

    printf("Nombre d'enfants: %d\n", person->num_children);
    for (int j = 0; j < person->num_children; j++) {
        printf("Enfant %d: %s %s\n", j + 1, person->children[j]->firstname, person->children[j]->lastname);
    }
    printf("\n");
}

void start() {
    Population population = readCSV("../resources/40.csv");
    linkPopulation(&population);

    for (int i = 0; i < population.size; i++) {
        printPersonDetails(&population.persons[i]);
    }

    free(population.persons);
}