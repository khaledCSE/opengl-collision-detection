#include <GL/glut.h>
#include "app.h"

// * Possible directions in a 2D space
enum Direction
{
  TOP,
  BOTTOM,
  LEFT,
  RIGHT,
  TOP_RIGHT,
  TOP_LEFT,
  BOTTOM_RIGHT,
  BOTTOM_LEFT,
};

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
  virtual void changeDirection(Direction direction);
};

void SphereDemo::changeDirection(Direction direction)
{
  switch (direction)
  {
  case TOP:
    y -= yStep;
    break;
  case BOTTOM:
    y += yStep;
    break;
  case LEFT:
    x -= xStep;
    break;
  case RIGHT:
    x += xStep;
    break;
  case TOP_LEFT:
    y -= yStep;
    x -= xStep;
    break;
  case TOP_RIGHT:
    x += xStep;
    y -= yStep;
    break;
  case BOTTOM_LEFT:
    x -= xStep;
    y += yStep;
    break;
  case BOTTOM_RIGHT:
    x += xStep;
    y += yStep;
    break;
  default:
    break;
  }
}

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
  // x += xStep;
  // y += yStep;
  changeDirection(TOP_LEFT);

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
