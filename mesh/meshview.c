#include <stdio.h>
#include <unistd.h> // for sleep

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* GLUT window */
int window;

void InitGL(int width, int height) {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // background color
  glClearDepth(1.0); // clear depth buffer
  glDepthFunc(GL_LESS); // only visible if depth is less
  glEnable(GL_DEPTH_TEST); // enable overlap checking
  glShadeModel(GL_SMOOTH); // smooth color shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); // reset projection matrix

  // set a good aspect ratio for window
  gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW);
}

void ReSizeGLScene(int width, int height) {
  if (height==0) height = 1; // prevent divide by zero

  glViewport(0, 0, width, height); // reset to take up full window

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); // reset projection matrix

  // set a good aspect ratio for window
  gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW);
}

void DrawGLScene() {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // clear screen and depth buffer

  // reset the view
  glLoadIdentity();

  glTranslatef(-1.5f, 0.0f, -6.0f);

  glBegin(GL_POLYGON);

  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);

  glEnd();

  glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y) {
  /* avoid thrashing this call */
  usleep(100);

  if (key==27) {
    glutDestroyWindow(window);
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  /*
  if (argc < 2) {
    printf("Usage: meshfile\n");
    return 1;
  }
  */

  glutInit(&argc, argv);

  /* 
   * GLUT_RGBA - RGBA color
   * GLUT_DOUBLE - Double buffer
   * GLUT_ALPHA - Alpha supported
   * GLUT_DEPTH - Automatic depth clipping
   */
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

  glutInitWindowSize(640, 480);

  glutInitWindowPosition(0, 0);

  window = glutCreateWindow("Jitu's Mesh View");

  glutDisplayFunc(&DrawGLScene);

  glutFullScreen();

  glutIdleFunc(&DrawGLScene);

  glutReshapeFunc(&ReSizeGLScene);

  glutKeyboardFunc(&keyPressed);

  InitGL(640, 480);

  glutMainLoop();

  return 1;
}

