#include <vector>
#include <iostream>
#include <GL/glut.h>
#include "app.h"
#include "particle.h"

using namespace std;

class SphereDemo : public Application
{
  Particle particle1;
  Particle particle2;
  Particle particle;

  Particle particles[2];

public:
  SphereDemo();
  virtual void display();
  virtual void update();
};

SphereDemo::SphereDemo()
{

  int number_of_particles = 2;

  for (int i = 0; i < number_of_particles; i++)
  {
    particles[i].setPosition(i * 50, 0);
    particles[i].setVelocity(-100, 101);
    particles[i].setRadius(10);
  }

  // particle1.setPosition(0, 0);
  // particle1.setVelocity(-100, 101);
  // particle1.setRadius(10);

  // particle2.setPosition(50, 0);
  // particle2.setVelocity(-100, 101);
  // particle2.setRadius(10);
  // * Setting time interval while setting every other property
  Application::setTimeInterval(5);
}

void SphereDemo::display()
{
  Application::display();

  glLoadIdentity();
  for (int i = 0; i < sizeof(particles); i++)
  {
    // * Go 50 units up the Y-axis
    // * Change the color on G values only

    Vector2 position = particles[i].getPosition();
    if (i == 0)
    {
      glPushMatrix();
    }
    glTranslatef(position.x, position.y, 0.0f);
    glColor3ub(255, i * 50, 0);
    glutSolidSphere(10, 30, 30);
    glPopMatrix();
  }

  // Vector2 position1 = particle1.getPosition();
  // Vector2 position2 = particle2.getPosition();

  // // * Go 50 units up the Y-axis
  // glLoadIdentity();
  // glPushMatrix();
  // glTranslatef(position1.x, position1.y, 0.0f);
  // glColor3ub(255, 0, 0);
  // glutSolidSphere(10, 30, 30);
  // glPopMatrix();

  // // * Go 50 units towards X-axis
  // glTranslatef(position2.x, position2.y, 0.0f);
  // glColor3ub(0, 255, 0);
  // glutSolidSphere(10, 30, 30);
  // glPopMatrix();

  glutSwapBuffers();
}

void SphereDemo::update(void)
{
  float duration = timeInterval / 100;

  for (int i = 0; i < sizeof(particles); i++)
  {
    float radius = particles[i].getRadius();

    particles[i].integrate(duration);

    Vector2 position = particles[i].getPosition();
    Vector2 velocity = particles[i].getVelocity();

    // * Reverse the direction when you reach left or right edge
    if (position.x > Application::width - radius || position.x < -Application::width + radius)
      particles[i].setVelocity(-velocity.x, velocity.y);
    if (position.y > Application::height - radius || position.y < -Application::height + radius)
      particles[i].setVelocity(velocity.x, -velocity.y);

    particles[i].setPosition(position.x, position.y);
  }

  // float radius = particle1.getRadius();

  // particle1.integrate(duration);
  // particle2.integrate(duration);

  // Vector2 position1 = particle1.getPosition();
  // Vector2 velocity1 = particle1.getVelocity();

  // Vector2 position2 = particle2.getPosition();
  // Vector2 velocity2 = particle2.getVelocity();

  // * Reverse the direction when you reach left or right edge
  // if (position1.x > Application::width - radius || position1.x < -Application::width + radius)
  //   particle1.setVelocity(-velocity1.x, velocity1.y);
  // if (position1.y > Application::height - radius || position1.y < -Application::height + radius)
  //   particle1.setVelocity(velocity1.x, -velocity1.y);

  // * For second particle
  // if (position2.x > Application::width - radius || position2.x < -Application::width + radius)
  //   particle2.setVelocity(-velocity2.x, velocity2.y);
  // if (position2.y > Application::height - radius || position2.y < -Application::height + radius)
  //   particle2.setVelocity(velocity2.x, -velocity2.y);

  // particle1.setPosition(position1.x, position1.y);
  // particle2.setPosition(position2.x, position2.y);
  Application::update();
}

Application *getApplication()
{
  return new SphereDemo();
};
