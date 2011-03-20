#include <stdio.h>
#include <stdlib.h>

#include "shape.h"
#include "linkedlist.h"

int numPts;
POINT3 *pts;
float *_ptdistsq;

void printLineLL(LINKEDLIST *list) {
  LLNODE *node = list->h;
  printf("[ ");
  while (node) {
    LINE3 *line = node->v;
    printf("{(%.1f,%.1f)->(%.1f,%.1f)}",
      line->p1->x, line->p1->y,
      line->p2->x, line->p2->y);
    node = node->n;

    if (node!=NULL) printf(", ");
  }
  printf(" ]\n");
}

void genPtDists() {
  int i, j;

  _ptdistsq = malloc(sizeof(float) * numPts * (numPts-1) / 2);

  int idx = 0;
  for (i=0; i<numPts-1; i++) {
    for (j=i+1; j<numPts; j++) {
      _ptdistsq[idx++] = distsqP2P(&pts[i], &pts[j]);
    }
  }
}

float ptdistsq(int id1, int id2) {
  if (id1 == id2) return 0;

  if (id1 > id2) {
    int t = id1;
    id1 = id2;
    id2 = t;
  }

  int n = numPts;
  //int idx = n*(n-1)/2 - (n-id1)*(n-1-id1)/2 + id2 - id1 - 1;
  int idx = n*id1 - (id1+3)*id1/2 + id2 - 1;
  //printf("(%d,%d) => %d\n", id1, id2, idx);
  return _ptdistsq[idx];
}

LLNODE *closestPointToPoint(POINT3 *pt, LINKEDLIST *list) {
  LLNODE *closest = NULL;
  float bestDist = 1.0f/0.0f; // infinity
  float curDist;
  LLNODE *curNode = list->h;
  
  while (curNode != NULL) {
    if ((curDist=ptdistsq(pt->id, ((POINT3*)curNode->v)->id)) < bestDist) {
      bestDist = curDist;
      closest = curNode;
    }
    curNode = curNode->n;
  }

  return closest;
}

LLNODE *closestPointToLine(LINE3 *line, LINKEDLIST *list) {
  LLNODE *closest = NULL;
  float bestDist = 1.0f/0.0f; // infinity
  float curDist;
  LLNODE *curNode = list->h;
  
  while (curNode != NULL) {
    curDist = ptdistsq(line->p1->id, ((POINT3*)curNode->v)->id)
            + ptdistsq(line->p2->id, ((POINT3*)curNode->v)->id);

    if (curDist < bestDist) {
      bestDist = curDist;
      closest = curNode;
    }
    curNode = curNode->n;
  }

  return closest;
}

int main(int argc, char *argv[]) {
  int i, j;
  LINKEDLIST *remainPts = llcreate();
  LINKEDLIST *lines = llcreate();
  LINKEDLIST *remainLines = llcreate();

  if (argc < 2) {
    printf("Usage: meshfile\n");
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  fscanf(file, "%d", &numPts);

  pts = malloc(sizeof(POINT3) * numPts);

  for (i=0; i<numPts; i++) {
    pts[i].id = i;
    fscanf(file, "%f %f", &pts[i].x, &pts[i].y);
    lladdlast(remainPts, &pts[i]);
  }
  
  fclose(file);

  genPtDists();
  /*
  for (i=0; i<numPts; i++) {
    for (j=0; j<numPts; j++) {
      printf("%3.3f\t", ptdistsq(i,j));
    }
    printf("\n");
  }
  */

  // Delete the first point

  LLNODE *firstPointNode = remainPts->h;
  POINT3 *firstPoint = firstPointNode->v;
  lldelete(remainPts, firstPointNode);

  LLNODE *secondPointNode = closestPointToPoint(firstPoint, remainPts);
  POINT3 *secondPoint = secondPointNode->v;
  LINE3 *firstLine = linecreate(firstPoint, secondPoint);
  lladdlast(remainLines, firstLine);
  llremove(remainPts, secondPointNode);

  LLNODE *thirdPointNode = closestPointToLine(firstLine, remainPts);
  POINT3 *thirdPoint = thirdPointNode->v;
  LINE3 *secondLine = linecreate(firstPoint, thirdPoint);
  LINE3 *thirdLine = linecreate(secondPoint, thirdPoint);
  lladdlast(remainLines, secondLine);
  lladdlast(remainLines, thirdLine);
  llremove(remainPts, thirdPointNode);

  while (remainPts->h) {
    LLNODE *closestPointNode = NULL;
    POINT3 *closestPoint = NULL;
    LLNODE *closestLineNode = NULL;
    LINE3 *closestLine = NULL;
    float best = 1.0f/0.0f; // infinity

    LLNODE *nodeL = remainLines->h;
    while (nodeL) {
      LINE3 *line = nodeL->v;

      LLNODE *nodeP = remainPts->h;
      while (nodeP) {
        POINT3 *pt = nodeP->v;

        float cur = distsqP2L(pt,line);
        if (cur < best) {
          best = cur;
          closestPointNode = nodeP;
          closestPoint = pt;
          closestLineNode = nodeL;
          closestLine = line;
        }

        nodeP = nodeP->n;
      }

      nodeL = nodeL->n;
    }

    lldelete(remainLines, closestLineNode);
    lldelete(remainPts, closestPointNode);
    lladdlast(remainLines, linecreate(closestLine->p1, closestPoint));
    lladdlast(remainLines, linecreate(closestLine->p2, closestPoint));
    lladdlast(lines, closestLine);
  }

  printLineLL(remainLines);
  printLineLL(lines);

  lldestroy(remainPts);
  lldestroy(lines);
  lldestroy(remainLines);
  free(_ptdistsq);
  free(pts);
  return 0;
}

