#include <GL/glut.h>

/**
 * Draws a red sphere at the origin of the window.
 */
void display(void)
{
  /**
   * Clears the color buffer and the depth buffer.
   * The color buffer is used to store the color of each pixel in the window.
   * The depth buffer is used to store the distance of each pixel from the camera.
   */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /**
   * Sets the current drawing color to red.
   * The glColor3ub() function takes three arguments: the red, green, and blue components of the color.
   * Each component is a value between 0 and 255.
   */
  glColor3ub(0, 255, 0);

  /**
   * Draws a solid sphere at the origin.
   * The glutSolidSphere() function takes three arguments:
   * the radius of the sphere, the number of slices to use to discretize the sphere, and the number of stacks to use to discretize the sphere.
   */
  glutSolidSphere(10.0f, 30, 30);

  /**
   * Swaps the front and back buffers.
   * The front buffer is the buffer that is displayed on the screen.
   * The back buffer is the buffer that is being drawn to.
   * Swapping the buffers ensures that the user sees the most up-to-date drawing.
   */
  glutSwapBuffers();
};

/**
 * The initGraphics() function is typically called by the GLUT library when it is time to initialize the OpenGL graphics system.
 */
void initGraphics(void)
{
  // RGBA
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
};

/**
 * Reshapes the OpenGL viewport and projection matrix.
 *
 * @param w The new width of the window in pixels.
 * @param h The new height of the window in pixels.
 */
void reshape(int w, int h)
{
  // Sets the viewport to the size of the window.
  glViewport(0, 0, w, h);

  // Switches to projection mode. The projection matrix is used to transform the scene from 3D space to 2D space.
  glMatrixMode(GL_PROJECTION);

  // Loads the identity matrix into the projection matrix.
  // The identity matrix is a matrix that does not transform the scene at all.
  glLoadIdentity();

  // Sets up an orthographic projection.
  // An orthographic projection is a projection that preserves the parallel lines of the scene.
  // The glOrtho() function takes six arguments: the left, right, bottom, top, near, and far clipping planes.
  // The clipping planes define the region of the scene that is visible.
  glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

  // Switches to modelview mode.
  // The modelview matrix is used to transform the scene before it is projected onto the screen.
  glMatrixMode(GL_MODELVIEW);

  // Loads the identity matrix into the modelview matrix.
  glLoadIdentity();
};

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Sphere");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  initGraphics();

  // A very important function in OpenGL programming, as it allows the program to respond to user input and other events.
  glutMainLoop();

  return 0;
};