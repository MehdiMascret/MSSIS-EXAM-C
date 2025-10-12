#include <errno.h>
#include "error.h"

void ArgInvalideOption(char *message) {
  perror("ERROR: Argument invalide option: %s\n", message);
  exit(1);
}