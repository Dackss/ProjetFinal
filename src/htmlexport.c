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
            update_html(filename, &population->persons[i]);
            sprintf(filename, "../result/info/info_person_%d.html", population->persons[i].id);
            create_info_html(filename, &population->persons[i]);
        }
    }
}

void update_html(const char *output_filename, Person *p)
{
    FILE *output_file = fopen(output_filename, "w");

    char *personLink = linkHtml(p->id, p->firstname, p->lastname);
    fprintf(output_file,
            "<!DOCTYPE html>\n"
            "<html lang=\"fr\">\n"
            "    <head>\n"
            "        <meta charset=\"UTF-8\">\n"
            "        <link rel=\"stylesheet\" href=\"../genealogie.css\">\n"
            "        <title>Arbre Généalogique</title>\n"
            "    </head>\n"
            "    <body>\n"
            "        <header>\n"
            "            <div class=\"header-left\">\n"
            "                <h1>Family Trees</h1>\n"
            "             </div>\n"
            "            <div class=\"header-right\">\n"
            "                <h1>Famille : %s</h1>\n"
            "            </div>\n"
            "        </header>\n"
            "        <main>\n"
            "            <div class=\"tree\">\n"
            "                <ul>\n"
            "                    <li>\n"
            "                        %s\n"  // Remplace par le lien de la personne
            "                        <ul>\n",
            getFamilyName(p), personLink
    );

    if (p->p_father) {
        char *fatherLink = linkHtml(p->p_father->id, p->p_father->firstname, p->p_father->lastname);
        char *grandpaLink = p->p_father->p_father ? linkHtml(p->p_father->p_father->id, p->p_father->p_father->firstname, p->p_father->p_father->lastname) : strdup("<a href=\"#\"><img src=\"../img.jpg\" alt=\"Inconnu\">Inconnu</a>");
        char *grandmaLink = p->p_father->p_mother ? linkHtml(p->p_father->p_mother->id, p->p_father->p_mother->firstname, p->p_father->p_mother->lastname) : strdup("<a href=\"#\"><img src=\"../img.jpg\" alt=\"Inconnu\">Inconnu</a>");

        fprintf(output_file,
                "<li>\n"
                "   %s\n"  // Father's link
                "   <ul>\n"
                "       <li>%s</li>\n"  // Grandfather's link
                "       <li>%s</li>\n"  // Grandmother's link
                "   </ul>\n"
                "</li>\n",
                fatherLink, grandpaLink, grandmaLink
        );

        free(fatherLink);
        free(grandpaLink);
        free(grandmaLink);
    }
    if (p->p_mother) {
        char *motherLink = linkHtml(p->p_mother->id, p->p_mother->firstname, p->p_mother->lastname);
        char *grandpaLink = p->p_mother->p_father ? linkHtml(p->p_mother->p_father->id, p->p_mother->p_father->firstname, p->p_mother->p_father->lastname) : strdup("<a href=\"#\"><img src=\"../img.jpg\" alt=\"Inconnu\">Inconnu</a>");
        char *grandmaLink = p->p_mother->p_mother ? linkHtml(p->p_mother->p_mother->id, p->p_mother->p_mother->firstname, p->p_mother->p_mother->lastname) : strdup("<a href=\"#\"><img src=\"../img.jpg\" alt=\"Inconnu\">Inconnu</a>");

        fprintf(output_file,
                "<li>\n"
                "   %s\n"  // Mother's link
                "   <ul>\n"
                "       <li>%s</li>\n"  // Grandfather's link
                "       <li>%s</li>\n"  // Grandmother's link
                "   </ul>\n"
                "</li>\n",
                motherLink, grandpaLink, grandmaLink
        );

        free(motherLink);
        free(grandpaLink);
        free(grandmaLink);
    }
    fprintf(output_file,
            "                        </ul>\n"
            "                    </li>\n"
            "                </ul>\n"
            "            </div>\n"
            "        </main>\n"
            "      <script src=\"../main.js\"></script>"
            "    </body>\n"
            "</html>\n"
    );
    fclose(output_file);
}

void create_info_html(const char *output_filename, Person *p) {
    FILE *output_file = fopen(output_filename, "w");

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
            "            <li>Nom : %s</li>\n",
            p->firstname, p->lastname, p->firstname, p->lastname
    );

    if (p->p_father)
    {
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

    if (p->p_mother)
    {
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

    fprintf(output_file,
            "        </ul>\n"
            "    </body>"
            "</html>"
    );

    fclose(output_file);
}