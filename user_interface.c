//
// Created by dacks on 14/06/2024.
//

#include "user_interface.h"

void start() {
    Population population = readCSV("../resources/40.csv");

    for (int i = 0; i < population.size; i++) {
        printf("ID: %d\n", population.persons[i].id);
        printf("Nom: %s\n", population.persons[i].lastname);
        printf("Prénom: %s\n", population.persons[i].firstname);
        printf("Date de naissance: %02d/%02d/%04d\n", population.persons[i].birthday, population.persons[i].birthmonth, population.persons[i].birthyear);
        printf("Code postal: %s\n", population.persons[i].region_naissance);
        printf("\n");
    }

    free(population.persons);
}