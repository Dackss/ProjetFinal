#include <stdio.h>
#include "person.h"
#include "population.h"
#include "htmlexport.h"
#include "advanced.h"

char* linkHtml(int id, const char *firstname, const char *lastname) {
    char *link = (char*) malloc(255 * sizeof(char));
    sprintf(link, "<a href=\"../info/info_person_%d.html\"><img src=\"../img-homme.jpg\" alt=\"%s %s\">%s %s</a>\n", id, firstname, lastname, firstname, lastname);
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
    int numSiblings;
    Person **siblings = getSiblings(p, &numSiblings);

    char *personLink = linkHtml(p->id, p->firstname, p->lastname);
    char line[1000];
    while (fgets(line, sizeof(line), template)) {
        if (strstr(line, "<!-- Famille -->")) {
            fprintf(output_file, "        <title>Famille %s</title>", getFamilyName(p));
        }
        if (strstr(line, "<!-- Famille 2 -->")) {
            fprintf(output_file, "                <h1 class=\"family-name\">Famille : %s</h1>", getFamilyName(p));
        }
        if (strstr(line, "<!-- Generation  -->")) {
            fprintf(output_file,
                    "                <ul>\n"
                    "                    <li>\n"
                    "                        %s\n",  // Ajoute en dessous les frères et soeur
                    personLink
            );
            for (int j = 0; j < numSiblings; j++) {
                Person *sibling = siblings[j];
                char *siblingLink = linkHtml(sibling->id, sibling->firstname, sibling->lastname);
                fprintf(output_file, "                        %s\n", siblingLink);
                free(siblingLink);
            }
            fprintf(output_file, "                <ul>\n");
            free(personLink);
            if (p->p_father) {
                char *fatherLink = linkHtml(p->p_father->id, p->p_father->firstname, p->p_father->lastname);

                char *grandpaLink;
                if (p->p_father->p_father) {
                    grandpaLink = linkHtml(p->p_father->p_father->id, p->p_father->p_father->firstname,
                                           p->p_father->p_father->lastname);
                } else {
                    grandpaLink = malloc(
                            strlen("<a href=\"#\"><img src=\"../img-homme.jpg\" alt=\"Inconnu\">Inconnu</a>") + 1);
                    strcpy(grandpaLink, "<a href=\"#\"><img src=\"../img-homme.jpg\" alt=\"Inconnu\">Inconnu</a>");
                }

                char *grandmaLink;
                if (p->p_father->p_mother) {
                    grandmaLink = linkHtml(p->p_father->p_mother->id, p->p_father->p_mother->firstname,
                                           p->p_father->p_mother->lastname);
                } else {
                    grandmaLink = malloc(
                            strlen("<a href=\"#\"><img src=\"../img-femme.jpg\" alt=\"Inconnu\">Inconnu</a>") + 1);
                    strcpy(grandmaLink, "<a href=\"#\"><img src=\"../img-femme.jpg\" alt=\"Inconnu\">Inconnu</a>");
                }

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

                char *grandpaLink;
                if(p->p_mother->p_father) {
                    grandpaLink = linkHtml(p->p_mother->p_father->id, p->p_mother->p_father->firstname, p->p_mother->p_father->lastname);
                } else {
                    grandpaLink = malloc(strlen("<a href=\"#\"><img src=\"../img-homme.jpg\" alt=\"Inconnu\">Inconnu</a>") + 1);
                    strcpy(grandpaLink, "<a href=\"#\"><img src=\"../img-homme.jpg\" alt=\"Inconnu\">Inconnu</a>");
                }

                char *grandmaLink;
                if(p->p_mother->p_mother) {
                    grandmaLink = linkHtml(p->p_mother->p_mother->id, p->p_mother->p_mother->firstname, p->p_mother->p_mother->lastname);
                } else {
                    grandmaLink = malloc(strlen("<a href=\"#\"><img src=\"../img-homme.jpg\" alt=\"Inconnu\">Inconnu</a>") + 1);
                    strcpy(grandmaLink, "<a href=\"#\"><img src=\"../img-homme.jpg\" alt=\"Inconnu\">Inconnu</a>");
                }

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
            "<link rel='stylesheet' href='../info.css'\n>"
            "        <title>Information de la Personne</title>\n"
            "    </head>\n"
            "    <body>\n"
            "<div id='header'>\n"
            "       <div id='business'> Family Trees </div>\n"
            "       <div id='family'> famille : %s </div>\n"
            "</div>\n"
            "<img src=../tree2.png>\n"
            "<div id='global'>\n"
            "        <h1>Détail sur %s %s</h1>\n"
            "        <div id='person'></div>\n"
            "        <div id='info'>\n"
            "        <ul>\n"
            "            <li>Prénom : %s</li>\n"
            "            <li>Nom : %s</li>\n"
            "            <li>Anniversaire : %02d/%02d/%04d</li>\n"
            "            <li>Lieu de naissance : %s</li>\n",
            p->lastname,
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
            "            </div>\n"
            "           </div>\n"
            "    </body>\n"
            "</html>"
    );

    fclose(output_file);
}