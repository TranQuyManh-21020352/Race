#include "Menu.h"

void ShowMenu::setBackGround(SDL_Renderer* screen) {

	if (!menu.loadImage("image//background_standard.png", screen));
	{
		success = false;
	}
}

void ShowMenu::setCar(SDL_Renderer* screen) {

	car[0].loadImage("image//car.png", screen);
	car[1].loadImage("image//obstacles.png", screen);
	car[2].loadImage("image//YelowCar.png", screen);
}

void ShowMenu::setFont() {
	Race = TTF_OpenFont("font//MISTRAL.ttf", 100);
}

void ShowMenu:: setString() {
	button[M_RACE] = "RACE";
	button[M_PLAY_GAME] = "PLAY GAME";
	button[M_HOW_TO_PLAY] = "HOW TO PLAY";
	button[M_HIGHT_SCORE] = "HIGHT SCORE";
	button[M_EXIT] = "EXIT";
}

void ShowMenu::setText(SDL_Renderer* screen,TTF_Font* font) {
	textButton[M_RACE].setColor(TextObject::RED_TEXT);
	textButton[M_RACE].setText(button[M_RACE]);
	textButton[M_RACE].loadFromRenderedText(Race, screen);
	for (int k = 1; k < menuItemNum; k++)
	{
		textButton[k].setColor(TextObject::WHITE_TEXT);
		textButton[k].setText(button[k]);
		textButton[k].loadFromRenderedText(font, screen);
	}
}

void ShowMenu::setRect() {
	posbutton[M_RACE] = { (SCREEN_WIDTH - textButton[0].getWidthText()) / 2,SCREEN_HEIGHT / 6, textButton[0].getWidthText(), textButton[0].getHeightText() };
	posbutton[M_PLAY_GAME] = { (SCREEN_WIDTH - textButton[1].getWidthText()) / 2,SCREEN_HEIGHT / 3 , textButton[1].getWidthText(), textButton[1].getHeightText() };
	posbutton[M_HOW_TO_PLAY] = { (SCREEN_WIDTH - textButton[2].getWidthText()) / 2,SCREEN_HEIGHT / 3 + 100, textButton[2].getWidthText(), textButton[2].getHeightText() };
	posbutton[M_HIGHT_SCORE] = { (SCREEN_WIDTH - textButton[3].getWidthText()) / 2,SCREEN_HEIGHT / 3 + 200 , textButton[3].getWidthText(), textButton[3].getHeightText() };
	posbutton[M_EXIT] = { (SCREEN_WIDTH - textButton[4].getWidthText()) / 2,SCREEN_HEIGHT / 3 + 300, textButton[4].getWidthText(), textButton[4].getHeightText() };
}

void ShowMenu::setSound() {
	gPress = Mix_LoadWAV("sound//press1.wav");
	if (gPress == NULL)
	{
		std::cout << "Can't play press1.wav" << std::endl;
	}
	gMenuMusic = Mix_LoadMUS("sound//Follow.mp3");
	if (gMenuMusic == NULL)
	{
		std::cout << "Can't play Follow.mp3 " << std::endl;
	}
}

void ShowMenu::close() {
	Mix_FreeChunk(gPress);
	Mix_FreeMusic(gMenuMusic);
	TTF_CloseFont(Race);
	menu.free();
	for (int k = 0; k < 3; k++) {
		car[k].free();
	}
	for (int k = 0; k < menuItemNum; k++) {
		textButton[k].free();
	}
}
int ShowMenu::showMenuStart(SDL_Renderer* screen, TTF_Font* font)
{
	setFont();
	setBackGround(screen);
	setCar(screen);
	setString();	
	setText(screen, font);
	setRect();
	setSound();
	// design board 
	static SDL_Rect fillButton = { 85,posbutton[M_PLAY_GAME].y - 10, 320, 70 };
	static SDL_Rect outlineButton = { fillButton.x + 1,fillButton.y + 1, fillButton.w - 2, fillButton.h - 2 };
	// init event of win menu
	SDL_Event menuEvent;
	int xmouse = 0;
	int ymouse = 0;
	// setup sound effect
	
	Mix_PlayMusic(gMenuMusic, -1);
	
	frameTime.start();
	while (true) {
		timeMenu = SDL_GetTicks() - 500;   // set time
		// render 
		RunBackground(menu, screen,false);
		car[0].renderCar((SCREEN_WIDTH - car[1].getWidth()) / 2 - 80, SCREEN_HEIGHT - 60, screen);
		car[1].renderCar((SCREEN_WIDTH - car[1].getWidth()) / 2, SCREEN_HEIGHT - 60, screen, NULL, NULL, 0, SDL_FLIP_VERTICAL);
		car[2].renderCar((SCREEN_WIDTH - car[1].getWidth()) / 2 + 80, SCREEN_HEIGHT - 60, screen);

		for (int k = 0; k < menuItemNum; k++)
		{
			if (k != 0) {
				RenderRectangle(screen, FillColor, fillButton);
				someRenderOutLine(screen, OutlineColor, outlineButton);
				fillButton.y += 100;
				if (fillButton.y > SCREEN_HEIGHT / 3 + 300) {
					fillButton.y = posbutton[M_PLAY_GAME].y - 10;
				}
			}
			outlineButton = { fillButton.x + 1,fillButton.y + 1, fillButton.w - 2, fillButton.h - 2 };
			if (k != 0) {
				textButton[k].loadFromRenderedText(font, screen);
			}
			textButton[k].renderText(posbutton[k].x, posbutton[k].y, screen);
			
		}
		SDL_RenderPresent(screen);
		SDL_Delay(16);
		// get event
		while (SDL_PollEvent(&menuEvent))
		{
			switch (menuEvent.type) {
			case SDL_QUIT:
				return M_EXIT;
				break;
			case SDL_MOUSEMOTION:
				xmouse = menuEvent.button.x;
				ymouse = menuEvent.button.y;
				// change color if pos is inside button and else
				for (int k = 0; k < menuItemNum; k++)
				{
					if (k == 0)
					{
						continue;
					}
					if (checkFocusButton(xmouse, ymouse, posbutton[k]))
					{
						textButton[k].setColor(TextObject::YELOW_TEXT);
					}
					else {
						textButton[k].setColor(TextObject::WHITE_TEXT);
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				xmouse = menuEvent.button.x;
				ymouse = menuEvent.button.y;
				for (int k = 0; k < menuItemNum; k++)
				{
					if (k == M_RACE)
					{
						continue;
					}
					if (checkFocusButton(xmouse, ymouse, posbutton[k]))
					{
						// play sound if press
						Mix_PlayChannel(-1, gPress, 0);
						Mix_HaltMusic();
						if (k == M_EXIT)
						{
							SDL_Delay(500);
						}
						else {
							SDL_Delay(200);
						}
						close();// release memory
						return k;
					}
				}
				break;
			default:
				break;
			}
			
		}
		
	}
	return M_EXIT;
}

