//
// Created by Thomas & Quentin on 14/06/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "htmlexport.h"
#include "population.h"

// Global variable to stock the population with a variable to check if the population is already linked
Population global_population;
int is_population_linked = 0;

// As indicated in the name, this function is used to link the population once
void link_population_once() {
    if (!is_population_linked) {
        global_population = readCSV("../resources/200.csv");
        linkPopulation(&global_population);
        is_population_linked = 1;
    }
}

/**
 * Main function
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return 0 if the program ran successfully, 1 otherwise
 *
 * The function starts by calling link_population_once() to link the population.
 * It then checks if the user has entered a command by verifying the number of arguments.
 * If no command is entered, it prints usage instructions and returns 1.
 *
 * The function then use if statements and compares the entered command with available commands using strcmp. (return 0 if the strings are equal)
 * For each command, it checks if the correct number of arguments is provided.
 * If the correct number of arguments is provided, it executes the corresponding function.
 * If the command is unknown or arguments are missing, it prints an error message and returns 1.
 */
int main(int argc, char *argv[]) {
    // Ensure the population data is loaded
    link_population_once();

    // Check if the user has entered a command
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

    // Handle the 'show_person_info' command
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

        // Handle the 'get_children' command
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

        // Handle the 'get_ancestors' command
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

        // Handle the 'get_siblings' command
    } else if (strcmp(command, "get_siblings") == 0) {
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

        // Handle unknown commands
    } else {
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