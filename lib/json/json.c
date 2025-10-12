#include "json.h"
#include "../error/error.h"

void addJsonElement(Json* json, JsonElement* element) {
  if (json->first == NULL) {
    json->first = element;
    json->last = element;
  } else {
    json->last->next = element;
    json->last = element;
  }
  json->length++;
}

typedef struct JsonToCharArray JsonToCharArray {
  char* current;
  JsonToCharArray* next;
};

void toCharArray(Json* json) {
  JsonToCharArray* jsonToCharArray = malloc(sizeof(JsonToCharArray));
  // 1) Transformation du json en JsonToCharArray
  int length = 0;

  // 2) Transformation en tableau de caractères
  char* result = malloc(sizeof(char) * (length + 2));
}

Json* create_Json(JsonContainer *node) {
  if (node == NULL) {
    JsonInvalideElement("Le node ne peut pas être NULL");
  }

  Json* json = malloc(sizeof(Json));
  json->node = node;
  json->addJsonElement = addJsonElement;
  json->toCharArray = toCharArray;
  return json;
}