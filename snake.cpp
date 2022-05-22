#include "snake.hpp"
#include "sdl_check.hpp"
#include<sstream>
#include <cstdlib>
#include <ctime>

void Snake::mSnake()
{
  auto res = SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CHECK(res == 0, "SDL_Init");
  SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_BORDERLESS, &window, &renderer);
  SDL_CHECK(window, "SDL_CreateWindowAndRenderer");
  SDL_CHECK(renderer, "SDL_CreateWindowAndRenderer");
  SDL_SetWindowPosition(window, 0, 0);


  auto surface = SDL_LoadBMP("sprites.bmp");
  SDL_CHECK(surface, "SDL_LoadBMP(\"sprites.bmp\")");
  sprites = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_CHECK(sprites, "SDL_CreateTextureFromSurface");
  SDL_FreeSurface(surface);

  auto surface1 = SDL_LoadBMP("point.bmp");
  SDL_CHECK(surface1, "SDL_LoadBMP(\"point.bmp\")");
  point = SDL_CreateTextureFromSurface(renderer, surface1);
  SDL_CHECK(point, "SDL_CreateTextureFromSurface1");
  SDL_FreeSurface(surface1);

  auto surface2 = SDL_LoadBMP("number.bmp");
  SDL_CHECK(surface2, "SDL_LoadBMP(\"number.bmp\")");
  number = SDL_CreateTextureFromSurface(renderer, surface2);
  SDL_CHECK(point, "SDL_CreateTextureFromSurface2");
  SDL_FreeSurface(surface2);

  auto surface3 = SDL_LoadBMP("life.bmp");
  SDL_CHECK(surface3, "SDL_LoadBMP(\"life.bmp\")");
  lifes = SDL_CreateTextureFromSurface(renderer, surface3);
  SDL_CHECK(lifes, "SDL_CreateTextureFromSurface3");
  SDL_FreeSurface(surface3);

  segmentsList.push_back(std::make_pair(5, 5));//khoi tao vi tri bo phan
  segmentsList.push_back(std::make_pair(5, 6));//khoi tao vi tri bo phan
  segmentsList.push_back(std::make_pair(4, 6));//khoi tao vi tri bo phan
  generateFruit();

}
int Snake::gameStartScreen()
{

    auto res = SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CHECK(res == 0, "SDL_Init");
  SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_BORDERLESS, &windows, &renderers);
  SDL_CHECK(windows, "SDL_CreateWindowAndRenderer");
  SDL_CHECK(renderers, "SDL_CreateWindowAndRenderer");
  SDL_SetWindowPosition(windows, 0, 0);

  auto surfaces = SDL_LoadBMP("SnakeStart.bmp");
  SDL_CHECK(surfaces, "SDL_LoadBMP(\"SnakeStart.bmp\")");
  start = SDL_CreateTextureFromSurface(renderers, surfaces);
  SDL_CHECK(start, "SDL_CreateTextureFromSurfaceover");
  SDL_FreeSurface(surfaces);

//    SDL_SetRenderDrawColor(renderers, 0x00, 0x9f, 0x00, 0xff);
//    SDL_RenderClear(renderers);


  SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = 1280;
        src.h = 720;
    SDL_Rect dest;
        dest.x=0;
        dest.y=0;
        dest.w = 1280;
        dest.h = 720;
        SDL_RenderCopyEx(renderers, start, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
        SDL_RenderPresent(renderers);
        return delgameStartScreen();

}
int Snake::delgameStartScreen()
{
    A: SDL_Event e;
    if (SDL_PollEvent(&e)&&e.type==SDL_KEYDOWN)
    {

    //SDL_Delay(2000);
    SDL_DestroyRenderer(renderers);
    SDL_DestroyWindow(windows);
    check=true;
    //SDL_Quit();
}
if (check==true) return exec();
else    goto A;
}

void Snake::generateFruit()
{
  srand(time(NULL));
  auto done = false;
  do
  {
    fruitX = rand() % (Width / 64);
    fruitY = rand() % (Height / 64);
    done = true;
    for (const auto &segment: segmentsList)
    {
      if (fruitX == segment.first && fruitY == segment.second)
      {
        done = false;
        break;
      }
    }
  } while (!done);
}

void Snake::generateSpecialFruit()
{
  auto done = false;
  do
  {
    specialfruitX = rand() % (Width / 64);
    specialfruitY = rand() % (Height / 64);
    done = true;
    for (const auto &segment: segmentsList)
    {
      if (specialfruitX == segment.first && specialfruitY == segment.second)
      {
        done = false;
        break;
      }
    }
  } while (!done);
}



void Snake::specialFruitEffect()
{
    int a=rand();
    int effect=a%5;
    switch (effect)
    {
    case 0:
    {
        points+=5;
        speed=speed+100;
        auto surfaceE = SDL_LoadBMP("effect0.bmp");
        SDL_CHECK(surfaceE, "SDL_LoadBMP(\"effect0.bmp\")");
        effects = SDL_CreateTextureFromSurface(renderer, surfaceE);
        SDL_CHECK(effects, "SDL_CreateTextureFromSurfaceE");
        SDL_FreeSurface(surfaceE);
        break;
    }
    case 1:
        {
            points+=5;
            speed = speed-100;
        auto surfaceE = SDL_LoadBMP("effect1.bmp");
        SDL_CHECK(surfaceE, "SDL_LoadBMP(\"effect1.bmp\")");
        effects = SDL_CreateTextureFromSurface(renderer, surfaceE);
        SDL_CHECK(effects, "SDL_CreateTextureFromSurfaceE");
        SDL_FreeSurface(surfaceE);
        break;
        }
    case 2:
        {
            points=points+10;
        auto surfaceE = SDL_LoadBMP("effect2.bmp");
        SDL_CHECK(surfaceE, "SDL_LoadBMP(\"effect2.bmp\")");
        effects = SDL_CreateTextureFromSurface(renderer, surfaceE);
        SDL_CHECK(effects, "SDL_CreateTextureFromSurfaceE");
        SDL_FreeSurface(surfaceE);
            break;
        }
    case 3:
        {
            points=points/2;
        auto surfaceE = SDL_LoadBMP("effect3.bmp");
        SDL_CHECK(surfaceE, "SDL_LoadBMP(\"effect3.bmp\")");
        effects = SDL_CreateTextureFromSurface(renderer, surfaceE);
        SDL_CHECK(effects, "SDL_CreateTextureFromSurfaceE");
        SDL_FreeSurface(surfaceE);
            break;

        }
    case 4:
        {
            life=life+1;
            points+=5;
        auto surfaceE = SDL_LoadBMP("effect4.bmp");
        SDL_CHECK(surfaceE, "SDL_LoadBMP(\"effect4.bmp\")");
        effects = SDL_CreateTextureFromSurface(renderer, surfaceE);
        SDL_CHECK(effects, "SDL_CreateTextureFromSurfaceE");
        SDL_FreeSurface(surfaceE);
            break;
        }
     default:
        {
            break;
        }
    }
}

Snake::~Snake()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}


//  int Snake::startScreen()
//  {
//      gameStartScreen();
//    delgameStartScreen();
//    if (check==true) return exec();
//    return gameStartScreen();
//  }

int Snake::exec()
{
//    gameStartScreen();
//   delgameStartScreen();

   mSnake();



  auto oldTick = SDL_GetTicks();
  for (auto done = false; !done;)
  {
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
      case SDL_KEYDOWN:
        {
          switch (e.key.keysym.sym)
          {
          case SDLK_UP:
            dx = 0;
            dy = -1;
            break;
          case SDLK_RIGHT:
            dx = 1;
            dy = 0;
            break;
          case SDLK_DOWN:
            dx = 0;
            dy = 1;
            break;
          case SDLK_LEFT:
            dx = -1;
            dy = 0;
            break;
          }
        }
        break;
      case SDL_QUIT:
        done = true;
        break;
      }
    }
    SDL_SetRenderDrawColor(renderer,0xFF, 0xA5, 0x00, 0xFF);
    //SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
    SDL_RenderClear(renderer);
    auto currentTick = SDL_GetTicks();
    for (auto t = oldTick; t < currentTick; ++t)
      if (!tick()) return gameoverScreen();
        //return 1;

    oldTick = currentTick;


    //SDL_DestroyRenderer(renderers);
    //SDL_DestroyWindow(windows);
    //SDL_Quit();

    draw();
    pointDisplay();
    numberDisplay();
    lifeDislay();
    lifeNumberDisplay();
    effectDisplay();
//    Uint32 startTime = 0;
//    startTime = SDL_GetTicks();
//    if(startTime>=3){
//    effectQuit();
//    }
    SDL_RenderPresent(renderer);
  }
  return 0;
}

bool Snake::tick()
{
  if (ticks++ % speed == 0)
  {
    auto p = segmentsList.front();
    p.first += dx;
    p.second += dy;
    if (p.first < 0 || p.first >= Width / 64 ||
        p.second < 0 || p.second >= Height / 64)
      return false;
    for (const auto &segment: segmentsList)
      if (p == segment)
      {
          if(life>0){
            life--;
          }
          else{
            return false;
          }
      }

    segmentsList.push_front(p);
     if(fruitX == specialfruitX || fruitY == specialfruitY)
     {
         generateSpecialFruit();
     }
    if (p.first != fruitX || p.second != fruitY){
      if(p.first != specialfruitX || p.second != specialfruitY){
      segmentsList.pop_back();
      }
      else{
      specialFruitEffect();
      specialfruitX=-1;
      specialfruitY=-1;

    }
    }

    else{
      generateFruit();
      specialfruitX=-1;
      specialfruitY=-1;
      count++;
      points++;
    }
  }
  if(count==5){
    generateSpecialFruit();
    count = 0;
  }
  return true;
}

void Snake::draw()
{
  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = 64;
  src.h = 64;
  SDL_Rect dest;
  dest.w = 64;
  dest.h = 64;
  int ds[][3] = {
    { -1, 0, 0 },//dau sang phai
    { 0, -1, 90 },//dau xuong duoi
    { 1, 0, 180 },//dau sang trai
    { 0, 1, -90 },//dau len tren
  };
  for (auto iter = std::begin(segmentsList); iter != std::end(segmentsList); ++iter)
  {
    float rotate = 0;
    const auto &segment = *iter;
    if (iter == std::begin(segmentsList))
    {
      if (iter->first + dx == fruitX && iter->second + dy == fruitY)//neu an fruit
        src.x = HeadOpenMouth * 64;
        else if(iter->first + dx == specialfruitX && iter->second + dy == specialfruitY)
        {
            src.x = HeadOpenMouth * 64;
        }
      else
        src.x = Head * 64;
      if (iter + 1 != std::end(segmentsList))//tranh con ran chi co dau va duoi
      {
        const auto &nextSegment = *(iter + 1);
        for (const auto &d: ds)
        {
          if (segment.first + d[0] == nextSegment.first && segment.second + d[1] == nextSegment.second)//huong quay cua dau
          {
            rotate = d[2];
            break;
          }
        }
      }
    }
    else if (iter + 1 == std::end(segmentsList))
    {
      src.x = Tail * 64;
      const auto &prevSegment = *(iter - 1);
      for (const auto &d: ds)
      {
        if (segment.first == prevSegment.first + d[0] && segment.second == prevSegment.second + d[1])
        {
          rotate = d[2];//huong quay cua duoi
          break;
        }
      }
    }
    else
    {
      const auto &nextSegment = *(iter + 1);
      const auto &prevSegment = *(iter - 1);
      if (nextSegment.first == prevSegment.first)
      {
        src.x = Straight * 64;
        rotate = 90;
      }
      else if (nextSegment.second == prevSegment.second)
      {
        src.x = Straight * 64;
        rotate = 0;
      }
      else
      {
        src.x = Turn * 64;
        bool up = false;
        if (segment.first == nextSegment.first && segment.second - 1 == nextSegment.second)
          up = true;
        if (segment.first == prevSegment.first && segment.second - 1 == prevSegment.second)
          up = true;
        bool right = false;
        if (segment.first + 1 == nextSegment.first && segment.second == nextSegment.second)
          right = true;
        if (segment.first + 1 == prevSegment.first && segment.second == prevSegment.second)
          right = true;
        bool down = false;
        if (segment.first == nextSegment.first && segment.second + 1 == nextSegment.second)
          down = true;
        if (segment.first == prevSegment.first && segment.second + 1 == prevSegment.second)
          down = true;
        bool left = false;
        if (segment.first - 1 == nextSegment.first && segment.second == nextSegment.second)
          left = true;
        if (segment.first - 1 == prevSegment.first && segment.second == prevSegment.second)
          left = true;
        if (up && right)
          rotate = 0;
        else if (right && down)
          rotate = 90;
        else if (down && left)
          rotate = 180;
        else if (left && up)
          rotate = 270;
      }
    }

    dest.x = 64 * segment.first;
    dest.y = 64 * segment.second;
    SDL_RenderCopyEx(renderer, sprites, &src, &dest, rotate, nullptr, SDL_FLIP_NONE);
  }
  src.x = Fruit * 64;
  dest.x = fruitX * 64;
  dest.y = fruitY * 64;
  SDL_RenderCopyEx(renderer, sprites, &src, &dest, 0, nullptr, SDL_FLIP_NONE);

  src.x = SpecialFruit * 64;
  dest.x = specialfruitX * 64;
  dest.y = specialfruitY * 64;
  SDL_RenderCopyEx(renderer, sprites, &src, &dest, 0, nullptr, SDL_FLIP_NONE);

}

void Snake::pointDisplay()
{
  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = 89;
  src.h = 36;
  SDL_Rect dest;
  dest.x = Width-110;
  dest.y = Height-36;
  dest.w = 89;
  dest.h = 36;
  SDL_RenderCopyEx(renderer, point, &src, &dest, 0, nullptr, SDL_FLIP_NONE);


}

void Snake::lifeDislay()
{
  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = 89;
  src.h = 36;
  SDL_Rect dest;
  dest.x = Width-200;
  dest.y = Height-36;
  dest.w = 89;
  dest.h = 36;
  SDL_RenderCopyEx(renderer, lifes, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
}

void Snake::lifeNumberDisplay()
{
    std::string s ;
    std::stringstream ss ;
    ss << life;
    ss >> s;
    for(int i = s.length()-1; i >= 0 ;--i) {
        int temp= s[i]-'0';
        SDL_Rect src;
                src.x = 20*temp+2;
                src.y = 6;
                src.w = 13;
                src.h = 32;
                SDL_Rect dest;
                dest.x = Width-13*(s.length()-i+1)-113;
                dest.y = Height-36;
                dest.w = 13;
                dest.h = 34;
                SDL_RenderCopyEx(renderer, number, &src, &dest, 0, nullptr, SDL_FLIP_NONE);

        }
     }


void Snake::numberDisplay()
{
    std::string s ;
    std::stringstream ss ;
    ss << points;
    ss >> s;
    for(int i = s.length()-1; i >= 0 ;--i) {
        int temp= s[i]-'0';
        SDL_Rect src;
                src.x = 20*temp+2;
                src.y = 6;
                src.w = 13;
                src.h = 32;
                SDL_Rect dest;
                dest.x = Width-13*(s.length()-i+1);
                dest.y = Height-36;
                dest.w = 13;
                dest.h = 34;
                SDL_RenderCopyEx(renderer, number, &src, &dest, 0, nullptr, SDL_FLIP_NONE);

        }
     }
     void Snake::effectDisplay()
     {
            SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = 246;
        src.h = 36;
            SDL_Rect dest;
        dest.x=517;
        dest.y=Height-36;
        dest.w = 246;
        dest.h = 36;
        SDL_RenderCopyEx(renderer, effects, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
     }
int Snake::gameoverScreen()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    auto res = SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CHECK(res == 0, "SDL_Init");
  SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_BORDERLESS, &window1, &renderer1);
  SDL_CHECK(window1, "SDL_CreateWindowAndRenderer");
  SDL_CHECK(renderer1, "SDL_CreateWindowAndRenderer");
  SDL_SetWindowPosition(window1, 0, 0);

    auto surface0 = SDL_LoadBMP("gameover.bmp");
  SDL_CHECK(surface0, "SDL_LoadBMP(\"gameover.bmp\")");
  over = SDL_CreateTextureFromSurface(renderer1, surface0);
  SDL_CHECK(over, "SDL_CreateTextureFromSurfaceover");
  SDL_FreeSurface(surface0);

    SDL_SetRenderDrawColor(renderer1, 0x00, 0x9f, 0x00, 0xff);
    SDL_RenderClear(renderer1);


  SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = 1280;
        src.h = 720;
    SDL_Rect dest;
        dest.x=0;
        dest.y=0;
        dest.w = 1280;
        dest.h = 720;
        SDL_RenderCopyEx(renderer1, over, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer1);
        SDL_Delay(2000);
        return 1;

}

//void Snake:: effectQuit()
//     {
//    auto surfaceEQ = SDL_LoadBMP("effectquit.bmp");
//    SDL_CHECK(surfaceEQ, "SDL_LoadBMP(\"effectquit.bmp\")");
//    equit = SDL_CreateTextureFromSurface(renderer, surfaceEQ);
//    SDL_CHECK(equit, "SDL_CreateTextureFromSurfaceEQ");
//    SDL_FreeSurface(surfaceEQ);
//            SDL_Rect src;
//        src.x = 0;
//        src.y = 0;
//        src.w = 246;
//        src.h = 36;
//            SDL_Rect dest;
//        dest.x=517;
//        dest.y=Height-36;
//        dest.w = 246;
//        dest.h = 36;
//        SDL_RenderCopyEx(renderer, equit, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
//     }

