#include <stdio.h>
#include "person.h"
#include "population.h"
#include "htmlexport.h"

char* linkHtml(int id, const char *firstname, const char *lastname) {
    char *link = (char*) malloc(255 * sizeof(char));
    sprintf(link, "<a href=\"../info/info_person_%d.html\"><img src=\"../img.jpg\" alt=\"%s %s\">%s %s</a>\n", id, firstname, lastname, firstname, lastname);
    return link;
}

char* getFamilyName(Person *p) {
    return p->lastname;
}

void export_html(Population *population) {
    for (int i = 0; i < population->size; i++) {
        if (population->persons[i].id != 0) {
            char filename[50];
            sprintf(filename, "../result/trees/tree_person_%d.html", population->persons[i].id);
            update_html("../result/template_trees.html",filename, &population->persons[i]);
            sprintf(filename, "../result/info/info_person_%d.html", population->persons[i].id);
            create_info_html(filename, &population->persons[i]);
        }
    }
}

void update_html(const char *template_file, const char *output_filename, Person *p) {
    FILE *output_file = fopen(output_filename, "w");
    FILE *template = fopen(template_file, "r");
    if (!(template || output_file)) {
        printf("Fichier pas ouvert");
        return;
    }

    char *personLink = linkHtml(p->id, p->firstname, p->lastname);
    char line[1000];
    while (fgets(line, sizeof(line), template)) {
        if (strstr(line, "<!-- Famille -->")) {
            fprintf(output_file, "        <title>Famille %s</title>", getFamilyName(p));
        }
        if (strstr(line, "<!-- Famille 2 -->")) {
            fprintf(output_file, "                <h1>Famille : %s</h1>", getFamilyName(p));
        }
        if (strstr(line, "<!-- Generation  -->")) {
            fprintf(output_file,
                    "                <ul>\n"
                    "                    <li>\n"
                    "                        %s\n"  // Remplace par le lien de la personne
                    "                        <ul>\n",
                    personLink
            );
            free(personLink);
            if (p->p_father) {
                char *fatherLink = linkHtml(p->p_father->id, p->p_father->firstname, p->p_father->lastname);
                char *grandpaLink = p->p_father->p_father ? linkHtml(p->p_father->p_father->id,
                                                                     p->p_father->p_father->firstname,
                                                                     p->p_father->p_father->lastname) : strdup(
                        "<a href=\"#\"><img src=\"../img.jpg\" alt=\"Inconnu\">Inconnu</a>");
                char *grandmaLink = p->p_father->p_mother ? linkHtml(p->p_father->p_mother->id,
                                                                     p->p_father->p_mother->firstname,
                                                                     p->p_father->p_mother->lastname) : strdup(
                        "<a href=\"#\"><img src=\"../img.jpg\" alt=\"Inconnu\">Inconnu</a>");

                fprintf(output_file,
                        "                            <li>\n"
                        "                               %s\n"  // Father's link
                        "                               <ul>\n"
                        "                                   <li>%s"
                        "                                                        </li>\n"  // Grandfather's link
                        "                                   <li>%s"
                        "                                                        </li>\n"  // Grandmother's link
                        "                               </ul>\n"
                        "                            </li>\n",
                        fatherLink, grandpaLink, grandmaLink
                );

                free(fatherLink);
                free(grandpaLink);
                free(grandmaLink);
            }
            if (p->p_mother) {
                char *motherLink = linkHtml(p->p_mother->id, p->p_mother->firstname, p->p_mother->lastname);
                char *grandpaLink = p->p_mother->p_father ? linkHtml(p->p_mother->p_father->id,
                                                                     p->p_mother->p_father->firstname,
                                                                     p->p_mother->p_father->lastname) : strdup(
                        "<a href=\"#\"><img src=\"../img.jpg\" alt=\"Inconnu\">Inconnu</a>");
                char *grandmaLink = p->p_mother->p_mother ? linkHtml(p->p_mother->p_mother->id,
                                                                     p->p_mother->p_mother->firstname,
                                                                     p->p_mother->p_mother->lastname) : strdup(
                        "<a href=\"#\"><img src=\"../img.jpg\" alt=\"Inconnu\">Inconnu</a>");

                fprintf(output_file,
                        "                            <li>\n"
                        "                               %s\n"  // Mother's link
                        "                               <ul>\n"
                        "                                   <li>%s"
                        "                                                        </li>\n"  // Grandfather's link
                        "                                   <li>%s"
                        "                                                        </li>\n"  // Grandmother's link
                        "                               </ul>\n"
                        "                            </li>\n",
                        motherLink, grandpaLink, grandmaLink
                );

                free(motherLink);
                free(grandpaLink);
                free(grandmaLink);
            }
        }
        fputs(line, output_file);
    }
    fclose(output_file);
}

void create_info_html(const char *output_filename, Person *p) {
    FILE *output_file = fopen(output_filename, "w");

    if (!output_file) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", output_filename);
        return;
    }

    fprintf(output_file,
            "<!DOCTYPE html>\n"
            "<html lang=\"fr\">\n"
            "    <head>\n"
            "        <meta charset=\"UTF-8\">\n"
            "        <title>Information de la Personne</title>\n"
            "    </head>\n"
            "    <body>\n"
            "        <h1>Informations sur %s %s</h1>\n"
            "        <ul>\n"
            "            <li>Prénom : %s</li>\n"
            "            <li>Nom : %s</li>\n"
            "            <li>Anniversaire : %02d/%02d/%04d</li>\n"
            "            <li>Lieu de naissance : %s</li>\n",
            p->firstname, p->lastname, p->firstname, p->lastname,
            p->birthday, p->birthmonth, p->birthyear, p->region_naissance
    );

    if (p->p_father){
        fprintf(output_file,
                "            <li>Le père : %s %s</li>\n",
                p->p_father->firstname, p->p_father->lastname
        );
    }
    else
    {
        fprintf(output_file,
                "            <li>Le père : Inconnu</li>\n"
        );
    }

    if (p->p_mother){
        fprintf(output_file,
                "            <li>La mère : %s %s</li>\n",
                p->p_mother->firstname, p->p_mother->lastname
        );
    }
    else
    {
        fprintf(output_file,
                "            <li>La mère : Inconnu</li>\n"
        );
    }
    if (p->children && p->num_children > 0) {
        for (int i = 0; i < p->num_children; ++i) {
            fprintf(output_file,
                    "                <li>L'enfant  : %s %s</li>\n",
                    p->children[i]->firstname, p->children[i]->lastname
            );
        }
    } else {
        fprintf(output_file,
                "            <li>Les enfants : Inconnus</li>\n"
        );
    }
    fprintf(output_file,
            "        </ul>\n"
            "    </body>"
            "</html>"
    );

    fclose(output_file);
}