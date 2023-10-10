#ifndef PARTICLE_H
#define PARTICLE_H
#include "coreMath.h"

class particle
{
protected:
  Vector2 position;
  Vector2 velocity;
  float radius;

public:
  void setPosition(const float x, const float y);
  void setRadius(const float r);
  Vector2 getPosition() const;
  float getRadius() const;
  void integrate(float duration);
  void setVelocity(const float x, const float y);
  Vector2 getVelocity() const;
};
