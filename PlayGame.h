#pragma once
#ifndef PLAY_GAME_H_
#define PLAY_GAME_H_

#include "CommanFunc.h"
#include "BaseObject.h"
#include "CarObject.h"
#include "ObstaclesObject.h"
#include "Functions.h"
#include "TextObject.h"
#include "Geomatric.h"
#include "TimeObject.h"
#include "ExplosionObject.h"



void runCowndown(TextObject& CountdownText, Uint32& timeCountdown, Uint32& val, std::stringstream& valTextcoundown, std::string& Textcoundown);
void runGamePlay(SDL_Renderer* gRenderer, BaseObject& gBackGround, CarObject& gRedCar, TTF_Font* gFont, std::vector<Obstacles>& gObstacles, TextObject& gText, Uint32& time, Uint32& val, std::stringstream&
	valText, std::string& TextScore, int& Score,int& currentObstacles, int &timeAppearObstacles,int&  timeMaxAppearObstacles);
void setExplosion(int posX, int posY, ExplosionObject& gExp, BaseObject& background_, CarObject& car_, TextObject& text_, std::vector<Obstacles>gObstacles, SDL_Renderer* screen);
void closeWhenFinish(BaseObject& gBackGround, CarObject& gRedCar,
	ExplosionObject& gExp, std::vector<Obstacles>& gObstacles,TextObject& gText,
	TTF_Font* gFont, Mix_Music* gMusic, Mix_Chunk* gCountdown, Mix_Chunk* gEffectCrash);

#endif 
