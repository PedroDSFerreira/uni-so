#ifndef __SO_IPC_ULL_
#define __SO_IPC_ULL_

// uint32_t
#include <stdint.h>

namespace base {
// Student information:
struct Student {
  uint32_t nmec;
  char *name;
};

// The linked-list support data structure:
struct Node {
  Student reg;
  struct Node *next;
};

Node *destroy(Node *list);
Node *append(Node *list, uint32_t nmec, char *name);
void print(Node *list);
int exists(Node *list, uint32_t nmec);
Node *remove(Node *list, uint32_t nmec);
const char *search(Node *list, uint32_t nmec);
Node *sort_by_name(Node *list);
Node *sort_by_number(Node *list);
void joinNodes(Node *current, Node *target);
} // namespace base

#endif /* __SO_IPC_ULL_ */
