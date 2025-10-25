#ifndef READ_H
#define READ_H
#include <stdio.h>

char *read_line(FILE *file);
char *scanfline ();
char **read_line_split_into_two_when_first_appear_separator(FILE *file, char separator);

#endif //READ_H