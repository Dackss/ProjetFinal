//
// Created by Thomas & Quentin on 14/06/2024.
//

#include "../include/person.h"

Person* initPerson(char* csvline) {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        perror("Failed to allocate memory for person");
        exit(EXIT_FAILURE);
    }

    char *token;
    token = strtok(csvline, ",");
    if (token != NULL) p->id = atoi(token);

    token = strtok(NULL, ",");
    if (token != NULL) p->father_id = atoi(token);

    token = strtok(NULL, ",");
    if (token != NULL) p->mother_id = atoi(token);

    token = strtok(NULL, ",");
    if (token != NULL) strncpy(p->lastname, token, sizeof(p->lastname) - 1);

    token = strtok(NULL, ",");
    if (token != NULL) strncpy(p->firstname, token, sizeof(p->firstname) - 1);

    token = strtok(NULL, "/");
    if (token != NULL) p->birthday = atoi(token);

    token = strtok(NULL, "/");
    if (token != NULL) p->birthmonth = atoi(token);

    token = strtok(NULL, ",");
    if (token != NULL) p->birthyear = atoi(token);

    token = strtok(NULL, ",");
    if (token != NULL) strncpy(p->region_naissance, token, sizeof(p->region_naissance) - 1);

    return p;
}