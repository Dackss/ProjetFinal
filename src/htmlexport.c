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
        printf("Error");
        fclose(template_file);
        return;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        printf("Error");
        fclose(template_file);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), template_file)) {
        if (strstr(line, "<!-- Génération 1 -->")) {
            fprintf(output_file, "            <div class='generation'>\n");
            fprintf(output_file, "                <div class='member'>\n");
            fprintf(output_file, "                    <img src='img.jpg' alt='%s %s'>\n", p->firstname, p->lastname);
            fprintf(output_file, "                    <p>%s %s</p>\n", p->firstname, p->lastname);
            fprintf(output_file, "                    <div class='connection'></div>\n");
            fprintf(output_file, "                </div>\n");
            fprintf(output_file, "            </div>\n");

        } else if (strstr(line, "<!-- Génération 2 -->")) {
            fprintf(output_file, "<div class='generation'>\n");
            if (p->p_father) {
                fprintf(output_file, "    <div class='member'>\n");
                fprintf(output_file, "        <img src='img.jpg' alt='%s %s'>\n", p->p_father->firstname, p->p_father->lastname);
                fprintf(output_file, "        <p>%s %s</p>\n", p->p_father->firstname, p->p_father->lastname);
                fprintf(output_file, "        <div class='connection'></div>\n");
                fprintf(output_file, "    </div>\n");
            }
            if (p->p_mother) {
                fprintf(output_file, "    <div class='member'>\n");
                fprintf(output_file, "        <img src='img.jpg' alt='%s %s'>\n", p->p_mother->firstname, p->p_mother->lastname);
                fprintf(output_file, "        <p>%s %s</p>\n", p->p_mother->firstname, p->p_mother->lastname);
                fprintf(output_file, "        <div class='connection'></div>\n");
                fprintf(output_file, "    </div>\n");
            }
            fprintf(output_file, "</div>\n");

        } else if (strstr(line, "<!-- Génération 3 -->")) {
            fprintf(output_file, "<div class='generation'>\n");
            if (p->p_father && p->p_father->p_father) {
                fprintf(output_file, "    <div class='member generation'>\n");
                fprintf(output_file, "        <img src='img.jpg' alt='%s %s'>\n", p->p_father->p_father->firstname, p->p_father->p_father->lastname);
                fprintf(output_file, "        <p>%s %s</p>\n", p->p_father->p_father->firstname, p->p_father->p_father->lastname);
                fprintf(output_file, "    </div>\n");
            }
            if (p->p_father && p->p_father->p_mother) {
                fprintf(output_file, "    <div class='member generation'>\n");
                fprintf(output_file, "        <img src='img.jpg' alt='%s %s'>\n", p->p_father->p_mother->firstname, p->p_father->p_mother->lastname);
                fprintf(output_file, "        <p>%s %s</p>\n", p->p_father->p_mother->firstname, p->p_father->p_mother->lastname);
                fprintf(output_file, "    </div>\n");
            }
            if (p->p_mother && p->p_mother->p_father) {
                fprintf(output_file, "    <div class='member generation'>\n");
                fprintf(output_file, "        <img src='img.jpg' alt='%s %s'>\n", p->p_mother->p_father->firstname, p->p_mother->p_father->lastname);
                fprintf(output_file, "        <p>%s %s</p>\n", p->p_mother->p_father->firstname, p->p_mother->p_father->lastname);
                fprintf(output_file, "    </div>\n");
            }
            if (p->p_mother && p->p_mother->p_mother) {
                fprintf(output_file, "    <div class='member'>\n");
                fprintf(output_file, "        <img src='img.jpg' alt='%s %s'>\n", p->p_mother->p_mother->firstname, p->p_mother->p_mother->lastname);
                fprintf(output_file, "        <p>%s %s</p>\n", p->p_mother->p_mother->firstname, p->p_mother->p_mother->lastname);
                fprintf(output_file, "    </div>\n");
            }
            fprintf(output_file, "</div>\n");

        } else {
            fprintf(output_file, "%s", line);
        }
    }

    fclose(template_file);
    fclose(output_file);
}
