#include <errno.h>
#include "error.h"

void JsonInvalideElement(char *message) {
  perror("ERROR: Json invalide element: %s\n", message);
  exit(1);
}