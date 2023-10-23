#include <cmath>
#include <vector>
#include <iostream>
#include <GL/glut.h>
#include "app.h"
#include "particle.h"

using namespace std;

class SphereDemo : public Application
{
  vector<Particle> particles;

public:
  SphereDemo();
  virtual void display();
  virtual void update();
  bool detect_out_of_the_box(Particle *particle);
  void resolve_box_collision(Particle *particle);
  void resolve_particle_collision(Particle *p1, Particle *p2);
  int generate_random_int_between(int min, int max);
};

SphereDemo::SphereDemo()
{

  int number_of_particles = 2;

  for (int i = 0; i < number_of_particles; i++)
  {
    Particle particle;

    // * Mind the radius: here is 10
    particle.setPosition(i * 89, 0);
    particle.setVelocity(-50, 51);
    particle.setRadius(10);
    particles.push_back(particle);
  }
  // * Setting time interval while setting every other property
  Application::setTimeInterval(5);
}

void SphereDemo::display()
{
  Application::display();

  glLoadIdentity();
  for (int i = 0; i < particles.size(); i++)
  {
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

  for (int i = 0; i < particles.size(); i++)
  {
    float radius = particles[i].getRadius();

    particles[i].integrate(duration);

    Vector2 position = particles[i].getPosition();
    Vector2 velocity = particles[i].getVelocity();

    if (detect_out_of_the_box(&particles[i]))
    {
      resolve_box_collision(&particles[i]);
    }
    else
    {
      if (i < particles.size() - 1)
      {
        resolve_particle_collision(&particles[i], &particles[i + 1]);
      }
    }
  }

  Application::update();
}

bool SphereDemo::detect_out_of_the_box(Particle *particle)
{
  float radius = particle->getRadius();
  Vector2 position = particle->getPosition();

  // Check if the particle is out of the box bounds
  if (position.x + radius > Application::width ||
      position.x - radius < -Application::width ||
      position.y + radius > Application::height ||
      position.y - radius < -Application::height)
  {
    return true; // Particle is out of the box
  }
  return false; // Particle is within the box
}

void SphereDemo::resolve_box_collision(Particle *particle)
{
  float radius = particle->getRadius();
  Vector2 position = particle->getPosition();
  Vector2 velocity = particle->getVelocity();

  // Check for collisions with the boundary
  if (position.x > Application::width - radius)
  {
    position.x = Application::width - radius;
    velocity.x = -velocity.x;
  }
  else if (position.x < -Application::width + radius)
  {
    position.x = -Application::width + radius;
    velocity.x = -velocity.x;
  }

  if (position.y > Application::height - radius)
  {
    position.y = Application::height - radius;
    velocity.y = -velocity.y;
  }
  else if (position.y < -Application::height + radius)
  {
    position.y = -Application::height + radius;
    velocity.y = -velocity.y;
  }

  // Update the position with corrections
  particle->setPosition(position.x, position.y);
  particle->setVelocity(velocity.x, velocity.y);
}

void SphereDemo::resolve_particle_collision(Particle *p1, Particle *p2)
{
  Vector2 position = p1->getPosition();
  Vector2 velocity = p1->getVelocity();

  Vector2 position2 = p2->getPosition();
  Vector2 velocity2 = p2->getVelocity();

  // * Collision Detection
  // d=√((x2 – x1)² + (y2 – y1)²)
  // d <= r1 + r2

  float d = sqrt(pow((position2.x - position.x), 2) + pow((position2.y - position.y), 2));

  if (d <= float(p1->getRadius() + p2->getRadius()))
  {
    p1->setVelocity(-velocity.x, -velocity.y);
    p2->setVelocity(-velocity2.x, -velocity2.y);
  }
  p1->setPosition(position.x, position.y);
  p2->setPosition(position2.x, position2.y);
}

Application *getApplication()
{
  return new SphereDemo();
};
