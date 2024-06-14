//
// Created by Thomas & Quentin on 14/06/2024.
//

#include "person.h"

Person* initPerson(char* csvline) {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        perror("Failed to allocate memory for person");
        exit(EXIT_FAILURE);
    }
    sscanf(csvline, "%d,%d,%d,%19s,%19s,%d,%d,%d,%29s", &p->id, &p->father_id, &p->mother_id, p->lastname, p->firstname, &p->birthday, &p->birthmonth, &p->birthyear, p->birthzipcode);
    p->p_father = NULL;
    p->p_mother = NULL;
    p->p_spouse = NULL;
    p->children = NULL;
    p->num_children = 0;
    return p;
}