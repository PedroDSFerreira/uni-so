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
  char *nameCopy = strdup(name);
  node->reg.nmec = nmec;
  node->reg.name = nameCopy;
  node->next = NULL;

  if (list == NULL) {
    return node;
  } else {
    Node *current = list;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = node;
  }
  return list;
}

void print(Node *list) {
  while (list != NULL) {
    printf("%d | %s\n", list->reg.nmec, list->reg.name);
    list = list->next;
  }
}

int exists(Node *list, uint32_t nmec) { return 0; }

Node *remove(Node *list, uint32_t nmec) {
  assert(nmec > 0);
  assert(list != NULL);

  if (list == NULL) {
    exit(1);
  }

  // Check head
  if (list->reg.nmec == nmec) {
    if (list->next != NULL) {
      Node *tmp = list->next;
      free(list);
      list = tmp;
    } else {
      free(list);
      return NULL;
    }
  }
  // BUG: Removing tail - seg. fault
  Node *current = list;
  while (current->next != NULL) {
    Node *tmp = current->next;
    if (tmp->reg.nmec == nmec) {
      if (tmp->next != NULL) {
        joinNodes(current, tmp->next);
      } else {
        joinNodes(current, NULL);
      }
    } else {
      current = current->next;
    }
  }
  return list;
}

const char *search(Node *list, uint32_t nmec) { return NULL; }

Node *sort_by_name(Node *list) { return NULL; }

Node *sort_by_number(Node *list) { return NULL; }

void joinNodes(Node *current, Node *target) {
  assert(current != NULL);

  Node *tmp = current->next;
  current->next = target;
  free(tmp);
}
} // namespace base
