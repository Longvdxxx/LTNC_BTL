#include <SDL.h>
#include <deque>

class Snake
{
public:
  void mSnake();
  ~Snake();
  //void exec();
  int exec();
  bool tick();
  void draw();
  int gameStartScreen();
  int delgameStartScreen();
  int startScreen();
  static const auto Head = 0;
  static const auto Body = 1;
  static const auto Fruit = 5;
  const static auto Width = 1280;
  const static auto Height = 720;
  static const auto SpecialFruit = 6;

private:
  SDL_Window *window;
  SDL_Renderer *renderer;

  SDL_Window *window1;
  SDL_Renderer *renderer1;

   SDL_Window *windows;
  SDL_Renderer *renderers;

  SDL_Texture *sprites;
  SDL_Texture *point;
  SDL_Texture *number;
  SDL_Texture *lifes;
  SDL_Texture *effects;
  SDL_Texture *equit;
  SDL_Texture *over;
  SDL_Texture *start;

  std::deque<std::pair<int, int> > segmentsList;
  unsigned ticks = 0;
  int dx = 1;
  int dy = 0;
  int fruitX;
  int fruitY;
  int specialfruitX=-1;
  int specialfruitY=-1;
  void generateFruit();
  void generateSpecialFruit();
  int count = 0;
  void specialFruitEffect();
  int speed = 200;
  void pointDisplay();
  int points=0;
  void numberDisplay();
  int life = 0;
  void lifeDislay();
  void lifeNumberDisplay();
  void effectDisplay();
  //void effectQuit();
  int gameoverScreen();
  bool check=false;

};
