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
    fprintf(ppmfile, "%c%c%c", (char)r, (char)g, (char)b);
  }

  fclose(kinfile);
  fclose(ppmfile);

  return 0;
}

