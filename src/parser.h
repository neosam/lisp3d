#ifndef PARSER_H
#define PARSER_H

Object *parse(char *filename);
Object *parseFile(FILE *file, Object *parent);
char *lookupList(char **list, char *key);

#endif
