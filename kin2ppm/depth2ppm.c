#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: kinfile ppmfile\n");
    return 1;
  }

  char *kinfilename = argv[1];
  char *ppmfilename = argv[2];

  FILE *kinfile = fopen(kinfilename, "r");
  FILE *ppmfile = fopen(ppmfilename, "w");

  int i;
  fprintf(ppmfile, "P6 640 480 255\n");
  for (i=0; i<640*480; i++) {
    int r, g, b, d;
    fscanf(kinfile, "%d %d %d %d", &r, &g, &b, &d);
		
    const float min = 512;
    const float range = 96;
    const int gamma_range = 96;
    float gamma;
    if (d<min) {
      gamma = -1;
    } else if (d>=min+range) {
      gamma = -1;
    } else {
      gamma = (d-min)*gamma_range/range;
    }
    int pval = gamma;
    int X = pval*256.0/gamma_range;
    int dr, dg, db;
    if (pval < 0) {
      dr = 0;
      dg = 0;
      db = 0;
    } else if (pval%4 == -1) {
      dr = 255;
      dg = 255;
      db = 255;
    } else {
      dr = 255-X;
      dg = 0;
      db = X;
    }
    
    fprintf(ppmfile, "%c%c%c", (char)dr, (char)dg, (char)db);
  }

  fclose(kinfile);
  fclose(ppmfile);

  return 0;
}

