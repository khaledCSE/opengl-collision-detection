#include <GL/glut.h>
#include "app.h"
#include "particle.h"

class SphereDemo : public Application
{
  Particle particle;

public:
  SphereDemo();
  virtual void display();
  virtual void update();
};

SphereDemo::SphereDemo()
{
  particle.setPosition(0, 0);
  particle.setVelocity(-100, 101);
  particle.setRadius(10);
  // * Setting time interval while setting every other property
  Application::setTimeInterval(5);
}

void SphereDemo::display()
{
  Application::display();

  Vector2 position = particle.getPosition();

  // * Go 50 units up the Y-axis
  glLoadIdentity();
  glPushMatrix();
  glTranslatef(position.x, position.y, 0.0f);
  glColor3ub(255, 0, 0);
  glutSolidSphere(10, 30, 30);
  glPopMatrix();

  // * Go 50 units towards X-axis
  // glTranslatef(50.0f, 0.0f, 0.0f);
  // glColor3ub(0, 255, 0);
  // glutSolidSphere(10, 30, 30);
  // glPopMatrix();

  glutSwapBuffers();
}

void SphereDemo::update(void)
{
  float radius = particle.getRadius();
  float duration = timeInterval / 100;

  particle.integrate(duration);

  Vector2 position = particle.getPosition();
  Vector2 velocity = particle.getVelocity();

  // * Reverse the direction when you reach left or right edge
  if (position.x > Application::width - radius || position.x < -Application::width + radius)
    particle.setVelocity(-velocity.x, velocity.y);
  if (position.y > Application::height - radius || position.y < -Application::height + radius)
    particle.setVelocity(velocity.x, -velocity.y);

  particle.setPosition(position.x, position.y);
  Application::update();
}

Application *getApplication()
{
  return new SphereDemo();
};
