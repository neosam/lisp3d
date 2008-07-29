#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "object.h"

char **elemList;

Object *parse(char *filename);
Object *parseFile(FILE *file, Object *parent);
char *lookupList(char **list, char *key);

void elemSetd(char *src, double *dst);
void elemSets(char *src, char **dst);

#endif
