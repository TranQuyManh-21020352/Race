
#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

static TTF_Font* gFont = NULL;
static TTF_Font* CountdownFont = NULL;
static TTF_Font* MenuFont = NULL;
static TTF_Font* HowToPlayFont = NULL;

static SDL_Event gEvent;

static Mix_Music* gMusic= NULL;
static Mix_Chunk* gEffectCrash = NULL;
static Mix_Chunk* gCountdown = NULL;

const int SCREEN_WIDTH = 490;
const int SCREEN_HEIGHT = 760;
const int COLOR_R = 255;
const int COLOR_G = 255;
const int COLOR_B = 255;
const int COLOR_A = 255;


const int BACKGROUND_WIDTH = 840;
const int BACKGROUND_HEIGHT = 650;

static SDL_Rect* CLIPBACKGROUND = NULL;

const int MaxLane = 4;
const int MaxObstacles = 5;
const int WIDTHCAR = 40;
const int HEIGHTCAR = 60;
const int POSITIONY = -60;
static int DISTANCE = 8;
static int speed = 5;
const int increaseVel = 1;
const int MaxPixels = 13;
static bool success;
static bool explosion = false;
static int i = 0;

static SDL_Rect pic1;
static SDL_Rect pic2;
static SDL_Rect pic3;
static SDL_Rect pic4;

const SDL_Rect OutlineRect = { 1, 1, SCREEN_WIDTH - 2, 28 };
const SDL_Rect FillRect = { 0, 0, SCREEN_WIDTH , 30 };
const SDL_Color OutlineColor = { 255, 255, 255, 255 };
const SDL_Color FillColor = { 36, 36, 36, 255 };

static std::string TextScore = "Score: 0";
static std::string Textcoundown = "";
static int Score = 0;

const  int FRAME_PER_SECOND = 60;

#endif 
