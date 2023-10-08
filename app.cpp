#include <GL/glut.h>
#include "app.h"

void Application::initGraphics()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Application::display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Application::resize(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-100.0f, 100.f, -100.f, 100.f, -100.f, 100.f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}