#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "CommanFunc.h"
#include "BaseObject.h"
#include "CarObject.h"
#include "ObstaclesObject.h"
#include "TextObject.h"
#include "Geomatric.h"



void setRect();
int randomObstacles();
void RunBackground(BaseObject& background, SDL_Renderer* screen, bool explosion);
void setObstacles(std::vector<Obstacles>&Obstacle, SDL_Renderer* screen, int& currentObstacles, int& timeAppearObstacles, int&timeMaxAppear);
void renderObs(std::vector<Obstacles>& Obstacle,SDL_Renderer* screen);
void setVelObstacles(std::vector<Obstacles>&obstacle, int velObs);
bool checkCollision(std::vector<SDL_Rect>&A, std::vector<SDL_Rect>&B);
void SetCountdown(SDL_Renderer* screen,TTF_Font* font, Mix_Chunk* Coundown_, BaseObject& background,CarObject& car, TextObject& text, TextObject& textcoundown_);
bool checkFocusButton(const int& x, const int& y, SDL_Rect& check);
void sort(std::vector<int>& hightscore_);

#endif 
