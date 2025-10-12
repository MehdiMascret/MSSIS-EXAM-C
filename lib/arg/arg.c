#include "arg.h"
#include "../error/error.h"
#include <stdlib.h>
#include <string.h>

ArgList* createArgList(Arg *arg, char *option) {
  ArgList *argList = malloc(sizeof(ArgList));
  argList->option = option;
  argList->first = NULL;
  argList->last = NULL;
  argList->lengthValues = 0;

  if (arg->first == NULL) {
    arg->first = argList;
    arg->last = argList;
  } else {
    arg->last->next = argList;
    arg->last = argList;
  }

  return argList;
}

void addValueInCurrentOption(ArgList *currentOption, char *value) {
  currentOption->lengthValues++;
  
  ArgListValue *argListValue = malloc(sizeof(ArgListValue));

  argListValue->value = value;
  argListValue->next = NULL;

  if (currentOption->first == NULL) {
    currentOption->first = argListValue;
    currentOption->last = argListValue;
  } else {
    currentOption->last->next = argListValue;
    currentOption->last = argListValue;
  }
}

Arg* create_Arg(int argc, char **argv) {
  Arg *arg = malloc(sizeof(Arg));

  // Le première argument doit être une option
  if (argv[1][0] != '-') {
    ArgInvalideOption("L'option doit commencer par un -");
  }

  ArgList *currentOption = NULL;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-')
      currentOption = createArgList(arg, argv[i]);
    else 
      addValueInCurrentOption(currentOption, argv[i]);
  }

  return arg;
}
