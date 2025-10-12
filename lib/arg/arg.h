#ifndef ARG_H
#define ARG_H

typedef struct ArgListValue ArgListValue {
  char *value;
  ArgListValue *next;
};

typedef struct ArgList ArgList {
  char *option;
  int lengthValues;
  ArgListValue *first, *last;
};

typedef struct Arg Arg {
  int length;
  ArgList *first, *last;
  (char*) (toCharArray*(*arg));
};

Arg* create_Arg(int argc, char **argv);

#endif // ARG_H