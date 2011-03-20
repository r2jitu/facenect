#ifndef _SHAPE_H_
#define _SHAPE_H_

typedef struct __POINT3 {
  int id;
  float x, y;
} POINT3;

typedef union __LINE3 {
  struct {
    POINT3 *p1, *p2;
  };
  POINT3 (*p)[2];
} LINE3;

#endif /* _SHAPE_H_ */
