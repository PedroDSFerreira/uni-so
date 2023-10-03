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
  assert(nmec > 0);
  assert(name != NULL);

  Node *node = (Node *)malloc(sizeof(Node));
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

  if (list == NULL) {
    exit(1);
  }

  // Check head
  while (list->reg.nmec == nmec) {
    if (list->next != NULL) {
      joinNodes(NULL, list->next);
      list = list->next;
    } else {
      free(list);
      return NULL;
    }
  }

  // Check body
  Node *current = list;
  while (current->next != NULL) {
    Node *tmp = current->next;
    if (tmp->reg.nmec == nmec) {
      joinNodes(current, tmp->next);
      free(tmp);
    } else {
      current = current->next;
    }
  }

  return list;
}

const char *search(Node *list, uint32_t nmec) {
  assert(nmec > 0);

  while (list != NULL) {
    if (list->reg.nmec == nmec) {
      return list->reg.name;
    }
    list = list->next;
  }
  return NULL;
}

Node *sort_by_name(Node *list) {
  assert(list != NULL);
  return NULL;
}

Node *sort_by_number(Node *list) {
  assert(list != NULL);

  Node *sorted = list;
  Node *current = list;
  while (current->next != NULL) {
    Node *next = current->next;
    printf("sorted: %d\nnext: %d\n\n\n", sorted->reg.nmec, next->reg.nmec);
    // check head
    if (next->reg.nmec < sorted->reg.nmec) {
      // BUG:first element points to next,
      // when joining the next as head, creates a loop
      printf("here\n");

      joinNodes(next, sorted);
      sorted = next;
      print(sorted);
    } else {
      // check body
      Node *tmp = sorted;
      while (tmp->next != NULL) {
        if (next->reg.nmec < tmp->next->reg.nmec) {
          joinNodes(next, tmp->next);
          break;
        }
        tmp = tmp->next;
      }
    }
    current = next;
  }
  return sorted;
}

void joinNodes(Node *current, Node *target) {
  if (current == NULL) {
    current = target;
  } else {
    current->next = target;
  }
}
} // namespace base
