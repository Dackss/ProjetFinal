#include <stdio.h>
#include "person.h"
#include "population.h"
#include "htmlexport.h"



void export_html(Population *population) {
    for (int i = 0; i < population->size; i++) {
        if (population->persons[i].id != 0) {
            char filename[50];
            sprintf(filename, "../result/person_%d.html", population->persons[i].id);
            update_html(filename, &population->persons[i]);
        }
    }
}


void update_html(const char *output_filename, Person *p) {
    FILE *output_file = fopen(output_filename, "w");

    fprintf(output_file, "<!DOCTYPE html>\n<html lang=\"fr\">\n<head>\n<meta charset=\"UTF-8\">\n<link rel=\"stylesheet\" href=\"genealogie.css\">\n<title>Arbre Généalogique</title>\n</head>\n<body>\n<header>\n<div class=\"header-left\">\n<h1>Nom de l'Entreprise</h1>\n</div>\n<div class=\"header-right\">\n<h1>Nom de la Famille</h1>\n</div>\n</header>\n<main>\n<div class=\"tree\">\n<ul>\n<li>\n<a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a>\n<ul>\n", p->firstname, p->lastname, p->firstname, p->lastname);

    if (p->p_father) {
        fprintf(output_file, "<li>\n<a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a>\n<ul>\n", p->p_father->firstname, p->p_father->lastname, p->p_father->firstname, p->p_father->lastname);
        fprintf(output_file, "<li><a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a></li>\n", p->p_father->p_father ? p->p_father->p_father->firstname : "Inconnu", p->p_father->p_father ? p->p_father->p_father->lastname : "Inconnu", p->p_father->p_father ? p->p_father->p_father->firstname : "Inconnu", p->p_father->p_father ? p->p_father->p_father->lastname : "Inconnu");
        fprintf(output_file, "<li><a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a></li>\n", p->p_father->p_mother ? p->p_father->p_mother->firstname : "Inconnu", p->p_father->p_mother ? p->p_father->p_mother->lastname : "Inconnu", p->p_father->p_mother ? p->p_father->p_mother->firstname : "Inconnu", p->p_father->p_mother ? p->p_father->p_mother->lastname : "Inconnu");
        fprintf(output_file, "</ul>\n</li>\n");
    }

    if (p->p_mother) {
        fprintf(output_file, "<li>\n<a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a>\n<ul>\n", p->p_mother->firstname, p->p_mother->lastname, p->p_mother->firstname, p->p_mother->lastname);
        fprintf(output_file, "<li><a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a></li>\n", p->p_mother->p_father ? p->p_mother->p_father->firstname : "Inconnu", p->p_mother->p_father ? p->p_mother->p_father->lastname : "Inconnu", p->p_mother->p_father ? p->p_mother->p_father->firstname : "Inconnu", p->p_mother->p_father ? p->p_mother->p_father->lastname : "Inconnu");
        fprintf(output_file, "<li><a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a></li>\n", p->p_mother->p_mother ? p->p_mother->p_mother->firstname : "Inconnu", p->p_mother->p_mother ? p->p_mother->p_mother->lastname : "Inconnu", p->p_mother->p_mother ? p->p_mother->p_mother->firstname : "Inconnu", p->p_mother->p_mother ? p->p_mother->p_mother->lastname : "Inconnu");
        fprintf(output_file, "</ul>\n</li>\n");
    }

    fprintf(output_file, "</ul>\n</li>\n</ul>\n</div>\n</main>\n</body>\n</html>\n");

    fclose(output_file);
}
