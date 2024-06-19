#include <stdio.h>
#include "person.h"
#include "population.h"
#include "htmlexport.h"
#include "advanced.h"

//Link C into html
char* linkHtml(Person *person, int who) {
    char *link = (char*) malloc(255 * sizeof(char));
    const char *imgSrc;

    // Déterminer l'image en fonction du paramètre who
    if (who == 1) {
        imgSrc = "../img-homme.jpg";
    } else if (who == 2) {
        imgSrc = "../img-femme.jpeg";
    } else {
        imgSrc = "../img-inconnu.jpg";
        person->gender = 0;
    }

    sprintf(link, "<a href=\"../info/info_person_%d.html\"><img src=\"%s\" alt=\"%s %s\">%s %s</a>\n",
            person->id, imgSrc, person->firstname, person->lastname, person->firstname, person->lastname);
    return link;
}

//Load images
char* imgName(Person *person) {
    char *img = (char*) malloc(150 * sizeof(char));
//Associate an image based on gender
    if (person->gender == 1) {
        sprintf(img, "../img-homme.jpg");
    } if (person->gender == 2) {
        sprintf(img, "../img-femme.jpeg");
    } else {
        sprintf(img, "../img-homme.jpg");
    }
    return img;
}

// get lastname
char* getFamilyName(Person *p) {
    return p->lastname;
}

//Free up memory space
void free_person(Person *p) {
    free(p->children);
}

//Export tamplates for html
void export_html(Population *population) {
    for (int i = 0; i < population->size; i++) {
        if (population->persons[i].id != 0) {
            char filename[50];
            sprintf(filename, "../result/trees/tree_person_%d.html", population->persons[i].id);
            update_html("../result/template_trees.html", filename, &population->persons[i]);
            sprintf(filename, "../result/info/info_person_%d.html", population->persons[i].id);
            create_info_html(filename, &population->persons[i]);
        }
    }
}

//Updating the html based on populations
    void update_html(const char *template_file, const char *output_filename, Person *p) {
    FILE *output_file = fopen(output_filename, "w");
    FILE *template = fopen(template_file, "r");
    if (!output_file) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", output_filename);
        return;
    }
    int numSiblings;
    Person **siblings = getSiblings(p, &numSiblings);

    char *personLink = linkHtml(p, 1); // 0 for the unknown person or the person themselves
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
                    "                        <div class=\"children\">\n"
                    "                           %s\n",  // Add the brothers and sisters below
                    personLink
            );
            for (int j = 0; j < numSiblings; j++) {
                Person *sibling = siblings[j];
                char *siblingLink = linkHtml(sibling, 1); // 0 for brothers and sisters
                fprintf(output_file, "                           %s\n", siblingLink);
                free(siblingLink);
            }
            fprintf(output_file,"                        </div>\n");
            fprintf(output_file, "                <ul>\n");
            free(personLink);
            if (p->p_father) {
                char *fatherLink = linkHtml(p->p_father, 1);
                p->p_father->gender = 1;

                char *grandpaLink;
                if (p->p_father->p_father) {
                    grandpaLink = linkHtml(p->p_father->p_father, 1);
                    p->p_father->p_father->gender = 1;
                } else {
                    grandpaLink = malloc(
                            strlen("<a href=\"#\"><img src=\"../img-homme.jpg\" alt=\"Inconnu\">Inconnu</a>") + 1);
                    strcpy(grandpaLink, "<a href=\"#\"><img src=\"../img-homme.jpg\" alt=\"Inconnu\">Inconnu</a>");
                }

                char *grandmaLink;
                if (p->p_father->p_mother) {
                    grandmaLink = linkHtml(p->p_father->p_mother, 2);
                    p->p_father->p_mother->gender = 2;
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
                char *motherLink = linkHtml(p->p_mother, 2);
                p->p_mother->gender = 2;

                char *grandpaLink;
                if(p->p_mother->p_father) {
                    grandpaLink = linkHtml(p->p_mother->p_father, 1);
                    p->p_mother->p_father->gender = 1;
                } else {
                    grandpaLink = malloc(strlen("<a href=\"#\"><img src=\"../img-homme.jpg\" alt=\"Inconnu\">Inconnu</a>") + 1);
                    strcpy(grandpaLink, "<a href=\"#\"><img src=\"../img-homme.jpg\" alt=\"Inconnu\">Inconnu</a>");
                }

                char *grandmaLink;
                if(p->p_mother->p_mother) {
                    grandmaLink = linkHtml(p->p_mother->p_mother, 2);
                    p->p_mother->p_mother->gender = 2;
                } else {
                    grandmaLink = malloc(strlen("<a href=\"#\"><img src=\"../img-femme.jpg\" alt=\"Inconnu\">Inconnu</a>") + 1);
                    strcpy(grandmaLink, "<a href=\"#\"><img src=\"../img-femme.jpg\" alt=\"Inconnu\">Inconnu</a>");
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
    free(siblings);
    fclose(output_file);
}

//Updating tamplate 2 with a person's specific information
    void create_info_html(const char *output_filename, Person *p) {
    FILE *output_file = fopen(output_filename, "w");

    if (!output_file) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", output_filename);
        return;
    }

    //html code to modify the tamplates
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
            "       <div id='family'> Famille %s </div>\n"
            "</div>\n"
            "<div id='global'>\n"
            "        <h1>Détail sur %s %s</h1>\n"
            "        <div id='person' style=\"background-image:url(%s)\"></div>\n"
            "        <div id='info'>\n"
            "        <ul>\n"
            "            <li>Prénom : %s</li>\n"
            "            <li>Nom : %s</li>\n"
            "            <li>Anniversaire : %02d/%02d/%04d</li>\n"
            "            <li>Lieu de naissance : %s</li>\n",
            p->lastname,
            p->firstname, p->lastname, imgName(p), p->firstname, p->lastname,
            p->birthday, p->birthmonth, p->birthyear, p->region_naissance
    );
    free(imgName(p));
    if (p->p_father){
        fprintf(output_file,
                "            <li>Le père : %s %s</li>\n",
                p->p_father->firstname, p->p_father->lastname
        );
    } else {
        fprintf(output_file,
                "            <li>Le père : Inconnu</li>\n"
        );
    }

    if (p->p_mother){
        fprintf(output_file,
                "            <li>La mère : %s %s</li>\n",
                p->p_mother->firstname, p->p_mother->lastname
        );
    } else {
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
            "         <img src=\"../tree2.png\" class=\"arbre\" alt=\"Arbre Généalogique\">\n"
            "         <div class=\"terre\"></div>"
            "    </body>\n"
            "</html>"
    );

    fclose(output_file);
}
