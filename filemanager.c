//
// Created by dacks on 14/06/2024.
//

#include "filemanager.h"

Population readCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    Population population = {NULL, 0, CAPACITY};
    population.persons = malloc(sizeof(Person) * CAPACITY);
    char line[256];
    int key;
    while (fgets(line, sizeof(line), file)) {
        Person *new_person = initPerson(line);
        key = new_person->id;
        insert(&population, key, new_person);
        free(new_person);
    }

    fclose(file);
    return population;
}