#include <cmath>
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
  int generate_random_int_between(int min, int max);
};

SphereDemo::SphereDemo()
{

  int number_of_particles = 2;

  for (int i = 0; i < number_of_particles; i++)
  {
    // TODO:
    // * Mind the radius: here is 10
    particles[i].setPosition(i * 89, 0);
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

    // * Collision Detection
    // d=√((x2 – x1)² + (y2 – y1)²)
    // d <= r1 + r2

    if (i < sizeof(particles) - 1)
    {
      Vector2 position2 = particles[i + 1].getPosition();
      Vector2 velocity2 = particles[i + 1].getVelocity();

      float d = sqrt(pow((position2.x - position.x), 2) + pow((position2.y - position.y), 2));

      if (d <= float(radius + radius))
      {
        particles[i].setVelocity(-velocity.x, -velocity.y);
        particles[i + 1].setVelocity(-velocity2.x, -velocity2.y);
      }
      particles[i + 1].setPosition(position2.x, position2.y);
    }

    particles[i].setPosition(position.x, position.y);
  }

  Application::update();
}

Application *getApplication()
{
  return new SphereDemo();
};
