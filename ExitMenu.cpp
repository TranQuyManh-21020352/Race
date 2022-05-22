#include "ExitMenu.h"


void ShowExitMenu::setBackGround(SDL_Renderer* screen) {
	if (!menuExit.loadImage("image//background_standard.png", screen));
	{
		success = false;
	}
}

void ShowExitMenu::setString(int& totalPoint, std::vector<int>hightscore_) {
	std::string score = std::to_string(totalPoint);
	if (hightscore_.size() == 1 || totalPoint > hightscore_[1]) {
		buttonExit[E_YOUR_POINT] = "Hight Score: " + score;
		isHightScore = true;
	}
	else {
		buttonExit[E_YOUR_POINT] = "Your Point: " + score;
		isHightScore = false;
	}
	buttonExit[E_PLAY_AGAIN] = "PLAY AGAIN";
	buttonExit[E_RETURN_MENU] = "MENU";
	buttonExit[E_EXIT] = "EXIT";
}

void ShowExitMenu::setText(SDL_Renderer* screen, _TTF_Font* font) {

	textButtonExit[E_YOUR_POINT].setColor(TextObject::RED_TEXT);
	textButtonExit[E_YOUR_POINT].setText(buttonExit[0]);
	textButtonExit[E_YOUR_POINT].loadFromRenderedText(font, screen);
	for (int k = 1; k < menuExitItemNum; k++)
	{
		textButtonExit[k].setColor(TextObject::WHITE_TEXT);
		textButtonExit[k].setText(buttonExit[k]);
		textButtonExit[k].loadFromRenderedText(font, screen);
	}
}

void ShowExitMenu::setRect() {
	posButtonExit[E_YOUR_POINT] = { (SCREEN_WIDTH - textButtonExit[E_YOUR_POINT].getWidthText()) / 2,SCREEN_HEIGHT / 4, textButtonExit[E_YOUR_POINT].getWidthText(), textButtonExit[E_YOUR_POINT].getHeightText() };
	posButtonExit[E_PLAY_AGAIN] = { (SCREEN_WIDTH - textButtonExit[E_PLAY_AGAIN].getWidthText()) / 2,SCREEN_HEIGHT / 2 , textButtonExit[E_PLAY_AGAIN].getWidthText(), textButtonExit[E_PLAY_AGAIN].getHeightText() };
	posButtonExit[E_RETURN_MENU] = { (SCREEN_WIDTH - textButtonExit[E_RETURN_MENU].getWidthText()) / 2,SCREEN_HEIGHT / 2 + 120, textButtonExit[E_RETURN_MENU].getWidthText(), textButtonExit[E_RETURN_MENU].getHeightText() };
	posButtonExit[E_EXIT] = { (SCREEN_WIDTH - textButtonExit[E_EXIT].getWidthText()) / 2,SCREEN_HEIGHT / 2 + 240, textButtonExit[E_EXIT].getWidthText(), textButtonExit[E_EXIT].getHeightText() };

}
void ShowExitMenu::setSound() {
	gPress = Mix_LoadWAV("sound//press1.wav");
	gfinish = Mix_LoadWAV("sound//sound_finish.wav");
	hightScoreEffect = Mix_LoadWAV("sound//When_get_hight_score.wav");
}

void ShowExitMenu::close() {
	Mix_FreeChunk(hightScoreEffect);
	Mix_FreeChunk(gfinish);
	menuExit.free();
	for (int k = 0; k < menuExitItemNum; k++) {
		textButtonExit[k].free();
	}
}

int ShowExitMenu::showMenuExit(SDL_Renderer* screen, TTF_Font* font, int& totalPoint, std::vector<int>hightscore_)
{
	setBackGround(screen);
	setString(totalPoint, hightscore_);
	setText(screen, font);
	setRect();
	setSound();
	// design border for button
	SDL_Rect fillExitMenu = { 85, SCREEN_HEIGHT / 2 - 10, 320, 70 };
	SDL_Rect outlineExitMenu = { fillExitMenu.x + 1, fillExitMenu.y + 1, fillExitMenu.w - 2, fillExitMenu.h - 2 };
	// position of mouse
	int xmouse = 0;
	int ymouse = 0;

	if (isHightScore) {
		// if get hightest score is play this sound
		Mix_PlayChannel(-1, hightScoreEffect, 0);
	}
	else {
		Mix_PlayChannel(-1, gfinish, 0);
	}

	SDL_Event menuEvent;
	while (true) {
		//render for window HightScore
		RunBackground(menuExit, screen,false);
		for (int k = 0; k < 3; k++) {
			RenderRectangle(screen, FillColor, fillExitMenu);
			someRenderOutLine(screen, OutlineColor, outlineExitMenu);
			fillExitMenu.y += 120;
			if (fillExitMenu.y > posButtonExit[E_EXIT].y) {
				fillExitMenu.y = SCREEN_HEIGHT / 2 - 10;
			}
			outlineExitMenu.y = fillExitMenu.y + 1;
		}

		for (int k = 0; k < menuExitItemNum; k++)
		{
			textButtonExit[k].loadFromRenderedText(font, screen);
			textButtonExit[k].renderText(posButtonExit[k].x, posButtonExit[k].y, screen);
		}
		// output to the screen
		SDL_RenderPresent(screen);
		SDL_Delay(16);
		// check event from mouse and keyboard
		while (SDL_PollEvent(&menuEvent))
		{
			switch (menuEvent.type) {
			case SDL_QUIT:
				return 1;
				break;
			case SDL_MOUSEMOTION:
				// get position of mouse
				xmouse = menuEvent.button.x;
				ymouse = menuEvent.button.y;
				//  If pos of mouse is inside of button, change color of buttton, else comeback old color
				for (int k = 0; k < menuExitItemNum; k++)
				{
					if (k == 0)
					{
						continue;
					}
					if (checkFocusButton(xmouse, ymouse, posButtonExit[k]))
					{
						textButtonExit[k].setColor(TextObject::YELOW_TEXT);
					}
					else {
						textButtonExit[k].setColor(TextObject::WHITE_TEXT);
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				xmouse = menuEvent.button.x;
				ymouse = menuEvent.button.y;
				for (int k = 0; k < menuExitItemNum; k++)
				{
					if (k == 0)
					{
						continue;
					}
					if (checkFocusButton(xmouse, ymouse, posButtonExit[k]))
					{
						//if putdown is play effect sound
						Mix_HaltChannel(-1);
						Mix_PlayChannel(-1, gPress, 0);
						if (k == 1)
						{
							SDL_Delay(500);
						}
						else {
							SDL_Delay(500);
						}
						close();
						return k;
					}

				}
				break;
			default:
				break;
			}

		}

	}
	return E_EXIT;// default

}

