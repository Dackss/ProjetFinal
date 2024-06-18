//
// Created by Thomas & Quentin on 14/06/2024.
//

#ifndef PROJETFINAL_HTMLEXPORT_H
#define PROJETFINAL_HTMLEXPORT_H

#include "population.h"


void export_html(Population *population);
void update_html(const char *template_file, const char *output_filename, Person *p);
void create_info_html(const char *output_filename, Person *p);

#endif
