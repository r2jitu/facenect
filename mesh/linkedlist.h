#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

typedef struct LLNODE {
  void *v;
  struct LLNODE *n, *p;
} LLNODE;

typedef struct LINKEDLIST {
  LLNODE *h, *t;
} LINKEDLIST;

LINKEDLIST *llcreate();
LLNODE *llcreatenode(void *val);

void llinsertbefore(LINKEDLIST *list, LLNODE *ref, LLNODE *node);
void llinsertafter(LINKEDLIST *list, LLNODE *ref, LLNODE *node);

LLNODE *lladdbefore(LINKEDLIST *list, LLNODE *ref, void *val);
LLNODE *lladdafter(LINKEDLIST *list, LLNODE *ref, void *val);

LLNODE *lladdfirst(LINKEDLIST *list, void *val);
LLNODE *lladdlast(LINKEDLIST *list, void *val);

void llremove(LINKEDLIST *list, LLNODE *node);
void *lldelete(LINKEDLIST *list, LLNODE *node);
void lldestroy(LINKEDLIST *list);


#endif /* _LINKEDLIST_H_ */
