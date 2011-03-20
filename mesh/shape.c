#include <stdio.h>
#include <stdlib.h>

#include "shape.h"
#include "linkedlist.h"

LINE3 *linecreate(POINT3 *p1, POINT3 *p2) {
  LINE3 *line = malloc(sizeof(LINE3));
  line->p1 = p1;
  line->p2 = p2;
  return line;
}

float distsqP2P(POINT3 *p1, POINT3 *p2) {
  float dx = p1->x-p2->x;
  float dy = p1->y-p2->y;
  float d = dx*dx + dy*dy;
  //printf("(%f,%f) to (%f,%f) is %f\n", p1->x, p1->y, p2->x, p2->y, d);
  return d;
}

float distsqP2L(POINT3 *p, LINE3 *l) {
  return distsqP2P(p,l->p1) + distsqP2P(p,l->p2);
}

