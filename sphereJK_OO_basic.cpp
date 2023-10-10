#include <GL/glut.h>
#include "app.h"

class SphereDemo : public Application
{
  int radius = 10;
  int x = 0;
  int y = 0;
  int xStep = 2;
  int yStep = 2;

public:
  virtual void display();
  virtual void update();
};

void SphereDemo::display()
{
  Application::display();

  glTranslatef(x, y, 0.0f);
  glColor3ub(255, 0, 0);
  glutSolidSphere(radius, 30, 30);
  glutSwapBuffers();
}

void SphereDemo::update()
{
  x += xStep;
  y += yStep;
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
