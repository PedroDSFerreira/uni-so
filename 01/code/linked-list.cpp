#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linked-list.h"

namespace base {

Node *destroy(Node *list) { return NULL; }

Node *append(Node *list, uint32_t nmec, char *name) {
  Node *node = (Node *)malloc(sizeof(Node));
  assert(nmec > 0);
  assert(name != NULL);
  if (node == NULL) {
    exit(1);
  }

  node->reg.nmec = nmec;
  node->reg.name = name;
  node->next = NULL;

  if (list == NULL) {
    return node;
  } else {
    Node *current = list;
    while (current->next != NULL) {
    }
    current->next = node;
  }
  return node;
}

void print(Node *list) {
  while (list != NULL) {
    // TODO: name is not being printed
    printf("%d %s\n", list->reg.nmec, list->reg.name);
    list = list->next;
  }
}

int exists(Node *list, uint32_t nmec) { return 0; }

Node *remove(Node *list, uint32_t nmec) { return NULL; }

const char *search(Node *list, uint32_t nmec) { return NULL; }

Node *sort_by_name(Node *list) { return NULL; }

Node *sort_by_number(Node *list) { return NULL; }
} // namespace base
