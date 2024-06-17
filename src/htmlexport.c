//
// Created by Thomas & Quentin on 14/06/2024.
//
#include "../include/person.h"
#include "../include/population.h"
#define MAX_NAME_LETTER 25
#define MAX_HTML_LETTER 50

//Changer donner de la struct en html
char *titleHTML(Person * p) {
    char *name = malloc(30 * sizeof(char));
    sprintf(name,"%s", p->lastname);
    return name;
}

void exportTableau_HTML(Population *p, const char *filename){
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }
    char *name = titleHTML(&p->persons[1]);
    //ecriture de l'html
    fprintf(file,"<!DOCTYPE html>\n");
    fprintf(file,"<html lang=\"fr\">\n");
    fprintf(file,"<head>\n");
    fprintf(file,"    <meta charset=\"UTF-8\">\n");
    fprintf(file,"    <title>Arbre Généalogique</title>\n");
    fprintf(file,"</head>\n");
    fprintf(file,"<body>\n");
    fprintf(file,"<header>\n");
    fprintf(file,"<div class=\"header-left\">\n");
    fprintf(file,"  <h1>Nom de l'Entreprise</h1>\n");
    fprintf(file," <div class=\"header-right\">\n");
    fprintf(file,"        <h1>Nom de la Famille</h1>\n");
    fprintf(file,"    </div>\n");
    fprintf(file,"</header>\n");
    fprintf(file,"<main>\n");
    fprintf(file,"    <section id=\"tree\">\n");
    fprintf(file,"        <div class=\"generation\">\n");
    fprintf(file,"            <div class=\"member\">\n");
    fprintf(file,"                <img src=\"img.jpg\" alt=\"Personne 1\">\n");
    fprintf(file,"                <p>Personne 1</p>\n");
    fprintf(file,"                <div class=\"connection\"></div>\n");
    fprintf(file,"                <div class=\"connection\"></div>\n");
    fprintf(file,"            </div>\n");
    fprintf(file,"        </div>\n");
    fprintf(file,"        <div class=\"generation\">\n");
    fprintf(file,"            <div class=\"member\">\n");
    fprintf(file,"                <img src=\"img.jpg\" alt=\"Père\">\n");
    fprintf(file,"                <p>Père</p>\n");
    fprintf(file,"                <div class=\"connection\"></div>\n");
    fprintf(file,"            </div>\n");
    fprintf(file,"            <div class=\"member\">\n");
    fprintf(file,"                <img src=\"img.jpg\" alt=\"Mère\">\n");
    fprintf(file,"                <p>Mère</p>\n");
    fprintf(file,"                <div class=\"connection\"></div>\n");
    fprintf(file,"            </div>\n");
    fprintf(file,"            </div>\n");
    fprintf(file,"        <div class=\"generation\">\n");
    fprintf(file,"            <div class=\"member\">\n");
    fprintf(file,"                <img src=\"img.jpg\" alt=\"Grand-Père Paternel\">\n");
    fprintf(file,"                <p>Grand-Père Paternel</p>\n");
    fprintf(file,"            </div>\n");
    fprintf(file,"            <div class=\"member\">\n");
    fprintf(file,"                <img src=\"img.jpg\" alt=\"Grand-Mère Paternelle\">\n");
    fprintf(file,"                <p>Grand-Mère Paternelle</p>\n");
    fprintf(file,"            </div>\n");
    fprintf(file,"            <div class=\"member\">\n");
    fprintf(file,"                <img src=\"img.jpg\" alt=\"Grand-Père Maternel\">\n");
    fprintf(file,"                <p>Grand-Père Maternel</p>\n");
    fprintf(file,"            </div>\n");
    fprintf(file,"            <div class=\"member\">\n");
    fprintf(file,"                <img src=\"img.jpg\" alt=\"Grand-Mère Maternelle\">\n");
    fprintf(file,"                <p>Grand-Mère Maternelle</p>\n");
    fprintf(file,"            </div>\n");
    fprintf(file,"            </div>\n");
    fprintf(file,"    </section>\n");
    fprintf(file,"</main>\n");
    fprintf(file,"</body>\n");
    fprintf(file,"</html>\n");
    fclose(file);
    free(name);
}
