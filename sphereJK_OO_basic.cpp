#include <GL/glut.h>
#include "app.h"

class SphereDemo : public Application
{
  int radius = 10;

public:
  virtual void display();
  virtual void update();
};

void SphereDemo::display()
{
  Application::display();
  glColor3ub(255, 0, 0);
  glutSolidSphere(radius, 30, 30);
  glutSwapBuffers();
}

void SphereDemo::update()
{
  if (radius <= Application::height && radius <= Application::width)
    radius++;
  else
    radius = 0;
  Application::update();
}

Application *getApplication()
{
  return new SphereDemo();
};
