#include "HowToPlay.h"


void ShowHowToPlay::setBackGround(SDL_Renderer* screen) {

	if (!HowToPlaybg.loadImage("image//background_standard.png", screen));
	{
		std::cout << "can't load image background" << std::endl;
		success = false;
	}
}

void ShowHowToPlay::setArrow(SDL_Renderer* screen) {

	Arrow[0].loadImage("image//Arrow.png", screen);
	Arrow[1].loadImage("image//Arrow_Up.png", screen);
	Arrow[2].loadImage("image//Arrow_Down.png", screen);
	Arrow[3].loadImage("image//Arrow_Left.png", screen);
	Arrow[4].loadImage("image//Arrow_Right.png", screen);

}

void ShowHowToPlay::setFont() {
	HelpFont = TTF_OpenFont("font//VNMUSTI.ttf", 65);
}

void ShowHowToPlay::setString() {
	buttonHelp[H_HOW_TO_PLAY] = "HOW TO PLAY";
	buttonHelp[H_TURN_UP] = "TURN UP";
	buttonHelp[H_TURN_DOWN] = "TURN DOWN";
	buttonHelp[H_TURN_LEFT] = "TURN LEFT";
	buttonHelp[H_TURN_RIGHT] = "TURN RIGHT";
	buttonHelp[H_RETURN_MENU] = "MENU";
}

void ShowHowToPlay::setText(SDL_Renderer* screen, _TTF_Font* font) {

	for (int k = 0; k < numHelp; k++)
	{
		if (k == 0) {
			helpText[k].setColor(TextObject::GREEN_TEXT);
			helpText[k].setText(buttonHelp[k]);
			helpText[k].loadFromRenderedText(HelpFont, screen);
			continue;
		}
		helpText[k].setColor(TextObject::WHITE_TEXT);
		helpText[k].setText(buttonHelp[k]);
		helpText[k].loadFromRenderedText(font, screen);
	}
}

void ShowHowToPlay::setRect() {

	helpRect[H_HOW_TO_PLAY] = { (SCREEN_WIDTH - helpText[H_HOW_TO_PLAY].getWidthText()) / 2, 50,helpText[H_HOW_TO_PLAY].getWidthText(),helpText[H_HOW_TO_PLAY].getHeightText() };
	helpRect[H_TURN_UP] = { 100, 300,helpText[H_TURN_UP].getWidthText(),helpText[H_TURN_UP].getHeightText() };
	helpRect[H_TURN_DOWN] = { 100, 400 ,helpText[H_TURN_DOWN].getWidthText(),helpText[H_TURN_DOWN].getHeightText() };
	helpRect[H_TURN_LEFT] = { 100, 500,helpText[H_TURN_LEFT].getWidthText(),helpText[H_TURN_LEFT].getHeightText() };
	helpRect[H_TURN_RIGHT] = { 100,  600,helpText[H_TURN_RIGHT].getWidthText(),helpText[H_TURN_RIGHT].getHeightText() };
	helpRect[H_RETURN_MENU] = { (SCREEN_WIDTH - helpText[H_RETURN_MENU].getWidthText()) / 2, 700,helpText[H_RETURN_MENU].getWidthText(),helpText[H_RETURN_MENU].getHeightText() };
}

void ShowHowToPlay::setSound() {
	pressReturnMenu = Mix_LoadWAV("sound//press1.wav");
	if (pressReturnMenu == NULL)
	{
		std::cout << "can't load sound press1.wav" << std::endl;
		success = false;
	}
}

void ShowHowToPlay::setBorder() {

	fillButton = { 95,helpRect[H_TURN_UP].y - 5, 238, 65 };
	outlineButton = { fillButton.x + 1,fillButton.y + 1, fillButton.w - 2, fillButton.h - 2 };
	fill_HowToPlay = { helpRect[H_HOW_TO_PLAY].x - 5,helpRect[H_HOW_TO_PLAY].y - 10,helpRect[H_HOW_TO_PLAY].w + 12,helpRect[H_HOW_TO_PLAY].h };
	outline_HowToPlay = { fill_HowToPlay.x + 1, fill_HowToPlay.y + 1, fill_HowToPlay.w - 2, fill_HowToPlay.h - 2 };
	fill_ReturnMenu = { helpRect[H_RETURN_MENU].x - 28,helpRect[H_RETURN_MENU].y - 10,helpRect[H_RETURN_MENU].w + 60,helpRect[H_RETURN_MENU].h + 10 };
	outline_ReturnMenu = { fill_ReturnMenu.x + 1, fill_ReturnMenu.y + 1, fill_ReturnMenu.w - 2, fill_ReturnMenu.h - 2 };

}

void ShowHowToPlay::close() {
	TTF_CloseFont(HelpFont);
	Mix_FreeChunk(pressReturnMenu);
	HowToPlaybg.free();
	for (int k = 0; k < numberArrow; k++) {
	   Arrow[k].free();
	}
}

int ShowHowToPlay::showHowToPlay(SDL_Renderer* screen, TTF_Font* font)
{
	
	setFont();
	setSound();
	setBackGround(screen);
	setArrow(screen);
	setString();
	setText(screen, font);
	setRect();
	setBorder();

	int xmouse, ymouse;// pos x,y of mouse
	while (true)
	{
		RunBackground(HowToPlaybg, screen,false);
		Arrow[0].renderCar(147, 100, screen);
		int posyArrow = helpRect[H_TURN_UP].y - 10;
		for (int k = 1; k < numberArrow; k++) {
			//render board for button
			RenderRectangle(screen, helpFill, fill_HowToPlay);
			someRenderOutLine(screen, helpOutline, outline_HowToPlay);
			RenderRectangle(screen, helpFill, fill_ReturnMenu);
			someRenderOutLine(screen, helpOutline, outline_ReturnMenu);
			RenderRectangle(screen, helpFill, fillButton);
			someRenderOutLine(screen, helpOutline,outlineButton);
			fillButton.y += 100;
			if (fillButton.y > helpRect[H_TURN_RIGHT].y) {
				fillButton.y = helpRect[H_TURN_UP].y - 10;
			}
			outlineButton = { fillButton.x + 1,fillButton.y + 1, fillButton.w - 2, fillButton.h - 2 };
			Arrow[k].renderCar(333, posyArrow, screen);
			posyArrow += 100;
		}
		for (int k = 0; k < numHelp; k++)
		{
			if (k != 0) {
				helpText[k].loadFromRenderedText(font, screen);
			}
			helpText[k].renderText(helpRect[k].x, helpRect[k].y, screen);
		}
		SDL_RenderPresent(screen);
		SDL_Delay(16);
		// get event and handling
		while (SDL_PollEvent(&helpEvent))
		{
			switch (helpEvent.type)
			{
			case SDL_QUIT:
				return M_EXIT;
				break;
			case SDL_MOUSEMOTION:
				xmouse = helpEvent.button.x;
				ymouse = helpEvent.button.y;
				// change color if inside button
				for (int k = 0; k < numHelp; k++) {
					if (checkFocusButton(xmouse, ymouse, helpRect[k]))
					{
						if (k != H_RETURN_MENU && k != H_HOW_TO_PLAY) {
							helpText[k].setColor(TextObject::GREEN_TEXT);
						}
						else {
							helpText[k].setColor(TextObject::RED_TEXT);
						}
					}
					else {
						helpText[k].setColor(TextObject::WHITE_TEXT);
					}
				}

				break;
			case SDL_MOUSEBUTTONDOWN:
				xmouse = helpEvent.button.x;
				ymouse = helpEvent.button.y;
				if (checkFocusButton(xmouse, ymouse, helpRect[H_RETURN_MENU]))
				{
					Mix_PlayChannel(-1, pressReturnMenu, 0);
					SDL_Delay(200);
					for (int k = 0; k < numHelp; k++)
					{
						helpText[k].free();
					}
					close();  // release memory
					return M_MENU;
				}
				break;
			}
		}
	}
}
