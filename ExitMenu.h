#pragma once
#ifndef EXIT_MENU_H_
#define EXIT_MENU_H_

#include "CommanFunc.h"
#include "TextObject.h"
#include "BaseObject.h"
#include "Functions.h"
#include "TimeObject.h"
#include "Menu.h"
#include "Geomatric.h"

enum MENUEXIT {
	E_YOUR_POINT = 0,
	E_PLAY_AGAIN = 1,
	E_RETURN_MENU = 2,
	E_EXIT = 3,
};

const int menuExitItemNum = 4;
static Mix_Chunk* hightScoreEffect = NULL;
static Mix_Chunk* gfinish = NULL;
static BaseObject menuExit;
static std::string buttonExit[menuExitItemNum];
static TextObject textButtonExit[menuExitItemNum];
static SDL_Rect posButtonExit[menuExitItemNum];
static bool isHightScore = false;

namespace ShowExitMenu {
	void setBackGround(SDL_Renderer* screen);
	void setString(int& totalPoint, std::vector<int>hightscore_);
	void setText(SDL_Renderer* screen, _TTF_Font* font);
	void setRect();
	void setSound();
	void close();
	int showMenuExit(SDL_Renderer* screen, TTF_Font* font, int& totalPoint, std::vector<int>hightscore_);
}
#endif 
