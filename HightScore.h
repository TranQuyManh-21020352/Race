#pragma once
#ifndef HIGHT_SCORE_H_
#define HIGHT_SCORE_H_
#include "CommanFunc.h"
#include "TextObject.h"
#include "BaseObject.h"
#include "Functions.h"
#include "TimeObject.h"
#include "Menu.h"
#include "Geomatric.h"

static Mix_Chunk* pressHightScore = NULL;

const int MAX_HIGHT_SCORE = 5;
const int MAX_BUTTON = 7;
static std::string titleStr = "HIGHT SCORE";
static  std::string  backStr = "MENU";
static BaseObject hightScorebg;
static std::string hightScoreStr[MAX_HIGHT_SCORE];
static TextObject hightScoreText[MAX_HIGHT_SCORE];
static TextObject Title;
static TextObject Back;
static SDL_Rect titleRect ;
static SDL_Rect backRect ;
static SDL_Rect hightScoreRect[MAX_HIGHT_SCORE];
static SDL_Rect fillBack ;
static SDL_Rect outlineBack ;
static SDL_Rect fillBoard ;
static SDL_Rect outlineBoard ;
static SDL_Event hightScoreEvent;
const SDL_Color outlineBoardColor = { 186,85,211, 0 };
const SDL_Color fillBoardColor = { 25,25,112, 255 };

namespace ShowHightScore {
	void setBackGround(SDL_Renderer* screen);
	void setString(std::vector<int>& HightScore);
	void setText(SDL_Renderer* screen, _TTF_Font* font);
	void setRect();
	void setSound();
	void setBorder();
	void close();
	int showHightScore(SDL_Renderer* screen, TTF_Font* font, std::vector<int>& HightScore);
}
#endif 
