#include <stdio.h>
#include <string.h>
#include "person.h"
#include "population.h"

// Function prototypes
void update_html(const char *template_filename, const char *output_filename, Person *p, Population *population);

void export_html(Population *population) {
    for (int i = 0; i < population->size; i++) {
        if (population->persons[i].id != 0) {
            char filename[50];
            sprintf(filename, "../result/person_%d.html", population->persons[i].id);
            update_html("../export/genealogie.html", filename, &population->persons[i], population);
        }
    }
}

void update_html(const char *template_filename, const char *output_filename, Person *p, Population *population) {
    FILE *template_file = fopen(template_filename, "r");
    if (!template_file) {
        printf("Erreur");
        fclose(template_file);
        return;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        printf("Erreur");
        fclose(template_file);
        return;
    }

    fprintf(output_file, "<!DOCTYPE html>\n");
    fprintf(output_file, "<html lang=\"fr\">\n");
    fprintf(output_file, "<head>\n");
    fprintf(output_file, "    <meta charset=\"UTF-8\">\n");
    fprintf(output_file, "    <link rel=\"stylesheet\" href=\"genealogie.css\">\n");
    fprintf(output_file, "    <title>Arbre Généalogique</title>\n");
    fprintf(output_file, "</head>\n");
    fprintf(output_file, "<body>\n");
    fprintf(output_file, "<header>\n");
    fprintf(output_file, "    <div class=\"header-left\">\n");
    fprintf(output_file, "        <h1>Nom de l'Entreprise</h1>\n");
    fprintf(output_file, "    </div>\n");
    fprintf(output_file, "    <div class=\"header-right\">\n");
    fprintf(output_file, "        <h1>Nom de la Famille</h1>\n");
    fprintf(output_file, "    </div>\n");
    fprintf(output_file, "</header>\n");
    fprintf(output_file, "<main>\n");
    fprintf(output_file, "    <div class=\"tree\">\n");
    fprintf(output_file, "        <ul>\n");
    fprintf(output_file, "            <li>\n");
    fprintf(output_file, "                <a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a>\n", p->firstname, p->lastname, p->firstname, p->lastname);
    fprintf(output_file, "                <ul>\n");

    if (p->p_father) {
        fprintf(output_file, "                    <li>\n");
        fprintf(output_file, "                        <a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a>\n", p->p_father->firstname, p->p_father->lastname, p->p_father->firstname, p->p_father->lastname);
        fprintf(output_file, "                        <ul>\n");
        if (p->p_father->p_father) {
            fprintf(output_file, "                            <li><a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a></li>\n", p->p_father->p_father->firstname, p->p_father->p_father->lastname, p->p_father->p_father->firstname, p->p_father->p_father->lastname);
        } else {
            fprintf(output_file, "                            <li><a href=\"#\"><img src=\"img.jpg\" alt=\"Inconnu\">Inconnu</a></li>\n");
        }
        if (p->p_father->p_mother) {
            fprintf(output_file, "                            <li><a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a></li>\n", p->p_father->p_mother->firstname, p->p_father->p_mother->lastname, p->p_father->p_mother->firstname, p->p_father->p_mother->lastname);
        } else {
            fprintf(output_file, "                            <li><a href=\"#\"><img src=\"img.jpg\" alt=\"Inconnu\">Inconnu</a></li>\n");
        }
        fprintf(output_file, "                        </ul>\n");
        fprintf(output_file, "                    </li>\n");
    }

    if (p->p_mother) {
        fprintf(output_file, "                    <li>\n");
        fprintf(output_file, "                        <a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a>\n", p->p_mother->firstname, p->p_mother->lastname, p->p_mother->firstname, p->p_mother->lastname);
        fprintf(output_file, "                        <ul>\n");
        if (p->p_mother->p_father) {
            fprintf(output_file, "                            <li><a href=\"#\"><img src=\"IMG.jpg\" alt=\"%s %s\">%s %s</a></li>\n", p->p_mother->p_father->firstname, p->p_mother->p_father->lastname, p->p_mother->p_father->firstname, p->p_mother->p_father->lastname);
        } else {
            fprintf(output_file, "                            <li><a href=\"#\"><img src=\"img.jpg\" alt=\"Inconnu\">Inconnu</a></li>\n");
        }
        if (p->p_mother->p_mother) {
            fprintf(output_file, "                            <li><a href=\"#\"><img src=\"img.jpg\" alt=\"%s %s\">%s %s</a></li>\n", p->p_mother->p_mother->firstname, p->p_mother->p_mother->lastname, p->p_mother->p_mother->firstname, p->p_mother->p_mother->lastname);
        } else {
            fprintf(output_file, "                            <li><a href=\"#\"><img src=\"img.jpg\" alt=\"Inconnu\">Inconnu</a></li>\n");
        }
        fprintf(output_file, "                        </ul>\n");
        fprintf(output_file, "                    </li>\n");
    }

    fprintf(output_file, "                </ul>\n");
    fprintf(output_file, "            </li>\n");
    fprintf(output_file, "        </ul>\n");
    fprintf(output_file, "    </div>\n");
    fprintf(output_file, "</main>\n");
    fprintf(output_file, "</body>\n");
    fprintf(output_file, "</html>\n");

    fclose(template_file);
    fclose(output_file);
}
