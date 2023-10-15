#include "particle.h"
#include <math.h>

void Particle::setPosition(const float x, const float y)
{
  position.x = x;
  position.y = y;
}

void Particle::setRadius(const float r)
{
  radius = r;
}

Vector2 Particle::getPosition() const
{
  return position;
}

float Particle::getRadius() const
{
  return radius;
}

void Particle::setVelocity(const float x, const float y)
{
  velocity.x = x;
  velocity.y = y;
}

void Particle::integrate(float duration)
{
  position += velocity * duration;
}

Vector2 Particle::getVelocity() const
{
  return velocity;
}