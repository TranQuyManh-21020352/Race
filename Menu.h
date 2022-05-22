#pragma once
#ifndef MENU_H_
#define MENU_H_

#include "CommanFunc.h"
#include "TextObject.h"
#include "BaseObject.h"
#include "Functions.h"
#include "TimeObject.h"
#include "Geomatric.h"

enum MENU {
	M_RACE = 0,
	M_PLAY_GAME = 1,
	M_HOW_TO_PLAY = 2,
	M_HIGHT_SCORE = 3,
	M_EXIT = 4,
	M_MENU = 5,
};

const int menuItemNum = 5;
static Mix_Chunk* gPress = NULL;// sound effect press
static Mix_Music* gMenuMusic = NULL; // music menu
static TTF_Font* Race = NULL;
static BaseObject menu;
static BaseObject car[3];
static TextObject textButton[menuItemNum];
static std::string button[menuItemNum];
static SDL_Rect posbutton[menuItemNum];
static Uint32 timeMenu;
static LTimer frameTime;

namespace ShowMenu {	
	void setBackGround(SDL_Renderer* screen);
	void setCar(SDL_Renderer* screen);
	void setFont();
	void setString();
	void setText(SDL_Renderer* screen,_TTF_Font* font);
	void setRect();
	void setSound();
	void close();
	int showMenuStart(SDL_Renderer* screen, TTF_Font* font);
 }
#endif 
