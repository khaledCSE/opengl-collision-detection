class Application
{
protected:
  int height;
  int width;
  float timeInterval;

public:
  virtual void initGraphics();
  virtual void display();
  virtual void resize(int width, int height);
  virtual void update();
  virtual float getTimeInterval();
  virtual void setTimeInterval(float timeInt);
};
