#include <stdlib.h>

#include "linkedlist.h"

LINKEDLIST *llcreate() {
  LINKEDLIST *list = malloc(sizeof(LINKEDLIST));
  list->h = list->t = NULL;
  return list;
}

LLNODE *llcreatenode(void *val) {
  LLNODE *node = malloc(sizeof(LLNODE));
  node->v = val;
  node->p = NULL;
  node->n = NULL;
  return node;
}

void llinsertbefore(LINKEDLIST *list, LLNODE *ref, LLNODE *node) {
  node->p = ref->p;
  node->n = ref;
  if (list->h == ref) list->h = node;
  ref->p = node;
}

void llinsertafter(LINKEDLIST *list, LLNODE *ref, LLNODE *node) {
  node->p = ref;
  node->n = ref->n;
  if (list->t == ref) list->t = node;
  ref->n = node;
}

LLNODE *lladdbefore(LINKEDLIST *list, LLNODE *ref, void *val) {
  LLNODE *node = llcreatenode(val);
  llinsertbefore(list, ref, node);
  return node;
}

LLNODE *lladdafter(LINKEDLIST *list, LLNODE *ref, void *val) {
  LLNODE *node = llcreatenode(val);
  llinsertafter(list, ref, node);
  return node;
}

LLNODE *lladdfirst(LINKEDLIST *list, void *val) {
  LLNODE *node = llcreatenode(val);
  if (list->h != NULL) llinsertbefore(list, list->h, node);
  if (list->h == NULL) list->h = node;
  if (list->t == NULL) list->t = node;
  return node;
}

LLNODE *lladdlast(LINKEDLIST *list, void *val) {
  LLNODE *node = llcreatenode(val);
  if (list->t != NULL) llinsertafter(list, list->t, node);
  if (list->h == NULL) list->h = node;
  if (list->t == NULL) list->t = node;
  return node;
}

void llremove(LINKEDLIST *list, LLNODE *node) {
  if (list->h == node) list->h = node->n;
  if (list->t == node) list->t = node->p;
  if (node->p != NULL) node->p->n = node->n;
  if (node->n != NULL) node->n->p = node->p;
  node->p = NULL;
  node->n = NULL;
}

void *lldelete(LINKEDLIST *list, LLNODE *node) {
  void *val = node->v;
  llremove(list, node);
  free(node);
  return val;
}

void lldestroy(LINKEDLIST *list) {
  while (list->h) lldelete(list, list->h);
  free(list);
}

