#include "CommanFunc.h"
#include "BaseObject.h"
#include "CarObject.h"
#include "ObstaclesObject.h"
#include "Functions.h"
#include "TextObject.h"
#include "Geomatric.h"
#include "Menu.h"
#include "TimeObject.h"
#include "HightScore.h"
#include "HowToPlay.h"
#include "ExitMenu.h"
#include "ExplosionObject.h"
#include "PlayGame.h"

BaseObject gBackGround;
TextObject gText;
TextObject CountdownText;
SDL_Color Color = { 255, 0, 255 };
static int timeAppearObstacles ;
static int timeMaxAppearObstacles ;
static int currentObstacles = 0;

bool Init();
bool loadmedia(CarObject& gRedCar, ExplosionObject& gExp);
void close();

int main(int argc, char* args[])
{
	srand(time(0));

	if (!Init())
	{
		std::cout << "Failed to intialize!" << std::endl;
	}
	else
	{
		bool Game = false;
		int menu = M_MENU;
		bool gameOver = false;
		CountdownFont = TTF_OpenFont("font//VNMUSTI.ttf", 80);
		MenuFont = TTF_OpenFont("font//VNMUSTI.ttf", 60);
		HowToPlayFont = TTF_OpenFont("font//VNMUSTI.ttf", 50);
		std::vector<int>HightScore;
		while (!Game) {
			while (menu == M_MENU) {
				// operate with menu
				int start = ShowMenu::showMenuStart(gRenderer, MenuFont); // if press four button
				if (start == M_EXIT)//press button Exit
				{
					Game = true;
					menu = M_EXIT;
				}
				else if (start == M_HIGHT_SCORE) {
					int hightscore = ShowHightScore::showHightScore(gRenderer, MenuFont, HightScore);// press button HightScore
					if (hightscore == M_EXIT) {
						Game = true;
						menu = M_EXIT;
					}
				}
				else if (start == M_HOW_TO_PLAY)
				{
					int Help = ShowHowToPlay::showHowToPlay(gRenderer,HowToPlayFont);// press button HowToPlay
					if (Help == M_EXIT)
					{
						Game = true;
						menu = M_EXIT;
					}
				}
				else if (start == M_PLAY_GAME)
				{
					menu = M_PLAY_GAME;	
				}
			}
			if(menu == M_PLAY_GAME)
			{
			// initialize objects
			CarObject gRedCar;// object you control
			std::vector<Obstacles>gObstacles;// threats
			ExplosionObject gExp;// explosion object
			currentObstacles = 0;
			timeAppearObstacles = 30;
			timeMaxAppearObstacles = 30;
			TextScore = "Score: 0";
			int increase = 1;
			if (!loadmedia(gRedCar, gExp))
			{
				std::cout << "Failed to load image" << std::endl;
			}
			else
			{
				CountdownFont = TTF_OpenFont("font//VNMUSTI.ttf", 80);
				bool quit = false;
				std::stringstream valText;
				std::stringstream valTextcoundown;
				Mix_PlayChannel(-1, gCountdown, 0);
				Uint32 time;
				// set countdown from 3 to 1
				Uint32 timeCountdown = 4;
				Uint32 val = 4 + (SDL_GetTicks()) / 1000;
				while (timeCountdown > 0)
				{
					runCowndown(CountdownText,timeCountdown, val, valTextcoundown, Textcoundown);
					if (timeCountdown == 0)
					{
						break;
					}
					SetCountdown(gRenderer, CountdownFont, gCountdown, gBackGround, gRedCar, gText, CountdownText);
				}
				SDL_Delay(500);
				// set countdown word "GO"
				Textcoundown = "GO!";
				CountdownText.setText(Textcoundown);
				SetCountdown(gRenderer, CountdownFont, gCountdown, gBackGround, gRedCar, gText, CountdownText);
				SDL_Delay(1000);// set delay for game is more real
				Mix_PlayMusic(gMusic, -1);//play music When playgame
				while (!quit)
				{
					while (SDL_PollEvent(&gEvent) != 0)
					{
						if (gEvent.type == SDL_QUIT)
						{
							Mix_HaltMusic();  // stop music when exit
							quit = true;
							Game = true;
						}
						gRedCar.handleInputAction(gEvent, gRenderer);   // get event from your keyboard
					}
					runGamePlay(gRenderer, gBackGround, gRedCar, gFont, gObstacles, gText, time, val, valText, TextScore, Score,currentObstacles,timeAppearObstacles,timeMaxAppearObstacles);
					for (int cls = 0; cls < gObstacles.size(); cls++)
					{
						if (checkCollision(gRedCar.getCarPixels(), gObstacles[cls].getObsPixels()))
						{
							Mix_HaltMusic();// stop music play game
							Mix_PlayChannel(-1, gEffectCrash, 0); // play effect crash when have collision
							setExplosion(gRedCar.GetPosXCar(), gRedCar.GetPosYCar(), gExp, gBackGround, gRedCar, gText, gObstacles, gRenderer);
							gRedCar.free();
							quit = true;
							gameOver = true;
							HightScore.push_back(Score);
							sort(HightScore);
							break;
						}
					}
					// make sure that fps is about 60
					int frameticks = frameTime.getTicks();
					if (frameticks < 1000 / FRAME_PER_SECOND)
					{
						SDL_Delay(1000 / FRAME_PER_SECOND - frameticks);
					}
					// increase level for game
					if (Score >= 10 * increase){
						setVelObstacles(gObstacles, 1);
						increase++;
					}
					// release memory
					if (quit){
						closeWhenFinish(gBackGround, gRedCar, gExp, gObstacles, gText, gFont, gMusic, gCountdown, gEffectCrash);
					}
					
				}

			}
				
		}
		if (gameOver) {
			// show menu exit 
			int  finish = ShowExitMenu::showMenuExit(gRenderer, MenuFont, Score,HightScore);
			if (finish == E_PLAY_AGAIN) // if press button Play again
			{
				menu = M_PLAY_GAME;
				gameOver = false;
				Score = 0;
			}

			else if (finish == E_RETURN_MENU) { // if press button menu
				menu = M_MENU;
				Score = 0;
				gameOver = false;
			}
			else if (finish == E_EXIT) // if press Exit or symbol "X" is right of Window
			{
				Game = true;
				Score = 0;
				menu = M_EXIT;
				gameOver = false;
			}
		}
		}
	}
	close();
	return 0;
}

bool Init()
{
	success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
		}
		gWindow = SDL_CreateWindow("Race", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Could not create window" << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				std::cout << "Could not create renderer:" << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, COLOR_R, COLOR_G, COLOR_B, COLOR_A);
				SDL_RenderClear(gRenderer);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
					success = false;
				}
				else {
					if (TTF_Init() == -1)
					{
						std::cout << "TTF could not initilize! SDL_ttf Error: " << TTF_GetError() << std::endl;
						success = false;
					}
					else {
						if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
						{
							std::cout << "SDL_mixer could not initialize! SDL_image Error: " << Mix_GetError() << std::endl;
							success = false;
						}
					}
				}

			}
		}

	}
	return success;
}

bool loadmedia(CarObject& gRedCar, ExplosionObject& gExp)
{
	success = true;
	if (!gExp.loadImageExp("image//explosion.png", gRenderer)) {
		success = false;
	}
	gExp.setClip();
	gFont = TTF_OpenFont("font//ARCADE.ttf", 40);
	if (gFont == NULL)
	{
		std::cout << "Failed to load lazy font! SDL_ttf Error:" << TTF_GetError() << std::endl;
		success = false;
	}
	else {
		// set scoretext and set coundown text
		gText.setColor(TextObject::WHITE_TEXT);
		gText.setText(TextScore);
		CountdownText.setColor(TextObject::RED_TEXT);
		CountdownText.setText(Textcoundown);
		if (!gText.loadFromRenderedText(gFont, gRenderer))
		{
			success = false;
		}
	}
	// set music for game
	gMusic = Mix_LoadMUS("sound//Music_play_game.mp3");
	if (gMusic == NULL)
	{
		std::cout << "Failed to load music ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		success = false;
	}
	gEffectCrash = Mix_LoadWAV("sound//Crash.wav");
	if (gEffectCrash == NULL)
	{
		std::cout << "Failed to load music ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		success = false;
	}
	gCountdown = Mix_LoadWAV("sound//Countdown.wav");
	if (gCountdown == NULL)
	{
		std::cout << "Failed to load music ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		success = false;
	}
	//set background for game
	if (!gBackGround.loadImage("image//background_standard.png", gRenderer))
	{
		success = false;
	}
	if (!gRedCar.loadImageCar("image//car.png", gRenderer))
	{
		success = false;
		std::cout << "not load redcar" << std::endl;
	}
	return success;
}



void close()
{
	gBackGround.free();
	// destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//destroy renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	// destroy font
	gText.free();
	CountdownText.free();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
