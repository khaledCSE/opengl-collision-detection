#include <GL/glut.h>
#include "app.h"

class SphereDemo : public Application
{
public:
  virtual void display();
};

void SphereDemo::display()
{
  Application::display();
  glColor3ub(255, 0, 0);
  glutSolidSphere(10, 30, 30);
  glutSwapBuffers();
}

Application *getApplication()
{
  return new SphereDemo();
};