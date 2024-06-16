#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "population.h"

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
    link_population_once();
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [<args>]\n", argv[0]);
        fprintf(stderr, "Commands:\n");
        fprintf(stderr, "  show_person_info <id>\n");
        fprintf(stderr, "  get_children <id>\n");
        fprintf(stderr, "  get_siblings <id>\n");
        fprintf(stderr, "  get_ancestors <id>\n");
        fprintf(stderr, "  export_html <filename>\n");
        return 1;
    }

    const char *command = argv[1];

    if (strcmp(command, "show_person_info") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s show_person_info <id>\n", argv[0]);
            return 1;
        }
        int id = atoi(argv[2]);
        if (id < 0 || id >= global_population.size) {
            fprintf(stderr, "Invalid ID: %d\n", id);
            return 1;
        }
        printPersonDetails(&global_population.persons[id]);
    } else if (strcmp(command, "get_children") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s get_children <id>\n", argv[0]);
            return 1;
        }
        int id = atoi(argv[2]);
        if (id < 0 || id >= global_population.size) {
            fprintf(stderr, "Invalid ID: %d\n", id);
            return 1;
        }
        printChildren(global_population.persons[id].num_children, &global_population.persons[id]);
    } else if (strcmp(command, "get_ancestors") == 0) {
       if (argc < 3) {
           fprintf(stderr, "Usage: %s get_ancestors <id>\n", argv[0]);
           return 1;
       }
       int id = atoi(argv[2]);
       if (id < 0 || id >= global_population.size) {
           fprintf(stderr, "Invalid ID: %d\n", id);
           return 1;
       }
       printAncestors(global_population, &global_population.persons[id]);
   }
    else if (strcmp(command, "get_siblings") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s get_siblings <id>\n", argv[0]);
            return 1;
        }
        int id = atoi(argv[2]);
        if (id < 0 || id >= global_population.size) {
            fprintf(stderr, "Invalid ID: %d\n", id);
            return 1;
        }
        int numSiblings;
        printSiblings(&global_population.persons[id], &numSiblings);
    }else {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }

    return 0;
}
/*else if (strcmp(command, "export_html") == 0) {
       if (argc < 3) {
           fprintf(stderr, "Usage: %s export_html <filename>\n", argv[0]);
           return 1;
       }
       const char *filename = argv[2];
       exportTableau_HTML(&global_population, filename);
   } */