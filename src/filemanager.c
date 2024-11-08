//
// Created by Thomas & Quentin on 14/06/2024.
//

#include "../include/filemanager.h"

//Initialize the population by introducing new person from the lines read
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
    for (int i = 0; i < population.size; i++) {
        population.persons[i].p_father = NULL;
        population.persons[i].p_mother = NULL;
        population.persons[i].p_spouse = NULL;
        population.persons[i].children = malloc(MAX_CHILDREN * sizeof(Person *));
        population.persons[i].num_children = 0;
        population.persons[i].max_children = MAX_CHILDREN;
    }
    fclose(file);
    return population;
}