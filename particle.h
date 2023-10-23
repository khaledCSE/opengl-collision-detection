#ifndef PARTICLE_H
#define PARTICLE_H
#endif
#include "coreMath.h"

struct RGB
{
  float r;
  float g;
  float b;
};

using namespace std;
class Particle
{
protected:
  Vector2 position;
  Vector2 velocity;
  float radius;

public:
  RGB color;
  void setPosition(const float x, const float y);
  void setRadius(const float r);
  Vector2 getPosition() const;
  float getRadius() const;
  void integrate(float duration);
  void setVelocity(const float x, const float y);
  Vector2 getVelocity() const;

  RGB getColor();
  void setColor(RGB rgb);
};
