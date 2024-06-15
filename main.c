#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

// Déclarer la population comme variable globale
Population global_population;
int is_population_linked = 0;

void link_population_once() {
    if (!is_population_linked) {
        global_population = readCSV("../resources/200.csv");
        linkPopulation(&global_population);
        is_population_linked = 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "print_person_details") == 0 && argc == 3) {
            int person_id = atoi(argv[2]);
            link_population_once();
            for (int i = 0; i < global_population.size; i++) {
                if (global_population.persons[i].id == person_id) {
                    printPersonDetails(&global_population.persons[i]);
                    break;
                }
            }
            return 0;
        } else if (strcmp(argv[1], "print_children") == 0 && argc == 3) {
            int person_id = atoi(argv[2]);
            link_population_once();
            for (int i = 0; i < global_population.size; i++) {
                if (global_population.persons[i].id == person_id) {
                    printChildren(global_population.persons[i].num_children, &global_population.persons[i]);
                    break;
                }
            }
            return 0;
        } else if (strcmp(argv[1], "print_siblings") == 0 && argc == 3) {
            int person_id = atoi(argv[2]);
            link_population_once();
            for (int i = 0; i < global_population.size; i++) {
                if (global_population.persons[i].id == person_id) {
                    int num_siblings = 0;
                    printSiblings(&global_population.persons[i], &num_siblings);
                    break;
                }
            }
            return 0;
        } else if (strcmp(argv[1], "link_population") == 0) {
            link_population_once();
            return 0;
        }
    }

    link_population_once();
    startMenu();
    return 0;
}
