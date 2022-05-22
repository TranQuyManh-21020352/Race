#pragma once
#ifndef HOW_TO_PLAY_H_
#define HOW_TO_PLAY_H_
#include "CommanFunc.h"
#include "TextObject.h"
#include "BaseObject.h"
#include "Functions.h"
#include "TimeObject.h"
#include "Menu.h"
#include "Geomatric.h"

enum HOWTOPLAY {
	H_HOW_TO_PLAY = 0,
	H_TURN_UP = 1,
	H_TURN_DOWN = 2,
	H_TURN_LEFT = 3,
	H_TURN_RIGHT = 4,
	H_RETURN_MENU = 5,
};

const int numberArrow = 5;
const int numHelp = 6;
static TTF_Font* HelpFont = NULL;
static Mix_Chunk* pressReturnMenu = NULL;
static BaseObject HowToPlaybg;
static BaseObject Arrow[numberArrow];
static TextObject helpText[numHelp];
static std::string buttonHelp[numHelp];
static SDL_Rect helpRect[numHelp];
static SDL_Event helpEvent;
static SDL_Rect fillButton;
static SDL_Rect outlineButton;
static SDL_Rect fill_HowToPlay ;
static SDL_Rect outline_HowToPlay;
static SDL_Rect fill_ReturnMenu ;
static SDL_Rect outline_ReturnMenu ;
const SDL_Color helpFill = { 218,165,32,255 };
const SDL_Color helpOutline = { 184,134,11, 255 };
namespace ShowHowToPlay {
	void setBackGround(SDL_Renderer* screen);
	void setArrow(SDL_Renderer* screen);
	void setFont();
	void setString();
	void setText(SDL_Renderer* screen, _TTF_Font* font);
	void setRect();
	void setSound();
	void setBorder();
	void close();
	int showHowToPlay(SDL_Renderer* screen, TTF_Font* font);
}

#endif 
