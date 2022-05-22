#include "HightScore.h"

void ShowHightScore::setBackGround(SDL_Renderer* screen)
{

	if (!hightScorebg.loadImage("image//background_standard.png", screen));
	{
		success = false;
	}
}

void ShowHightScore::setString(std::vector<int>& HightScore) {
	hightScoreStr[0] = "No1.  "; hightScoreStr[1] = "No2.  "; hightScoreStr[2] = "No3.  "; hightScoreStr[3] = "No4.  "; hightScoreStr[4] = "No5.  ";
	for (int k = 0; k < HightScore.size(); k++)
	{
		if (HightScore[k] != 0 && k < MAX_HIGHT_SCORE)
		{
			hightScoreStr[k] += std::to_string(HightScore[k]);
		}
	}

}

void ShowHightScore::close() {
    hightScorebg.free();
	for (int k = 0; k < MAX_HIGHT_SCORE; k++) {
		hightScoreText[k].free();
	}
	Title.free();
	Back.free();
}

void ShowHightScore::setText(SDL_Renderer* screen, _TTF_Font* font) {
	Title.setColor(128,0,128);
	Title.setText(titleStr);
	Title.loadFromRenderedText(font, screen);
	Back.setColor(TextObject::WHITE_TEXT);
	Back.setText(backStr);
	Back.loadFromRenderedText(font, screen);
	for (int k = 0; k < MAX_HIGHT_SCORE; k++)
	{
		hightScoreText[k].setColor(TextObject::WHITE_TEXT);
		hightScoreText[k].setText(hightScoreStr[k]);
		hightScoreText[k].loadFromRenderedText(font, screen);
	}
}
void ShowHightScore::setRect() {

	for (int k = 0; k < MAX_HIGHT_SCORE; k++)
	{
		hightScoreRect[k] = { 105,150 + 80 * k,hightScoreText[k].getWidthText(),hightScoreText[k].getHeightText() };
	}

}
void ShowHightScore::setSound()
{
	pressHightScore = Mix_LoadWAV("sound//press1.wav");
	if (pressHightScore == NULL)
	{
		std::cout << "can't load sound press1.wav" << std::endl;
		success = false;
	}
}

void ShowHightScore::setBorder() {

	titleRect = { (SCREEN_WIDTH - Title.getWidthText()) / 2, 50, Title.getWidthText(), Title.getHeightText() };
    backRect = { (SCREEN_WIDTH - Back.getWidthText()) / 2, 600, Back.getWidthText(), Back.getHeightText() };
	fillBack = { backRect.x - 5, backRect.y - 12, backRect.w + 10, backRect.h + 10 };
	outlineBack = { fillBack.x + 1, fillBack.y + 1, fillBack.w - 2, fillBack.h - 2 };
	fillBoard = { 95, 140, 300, 400 };
	outlineBoard = { fillBoard.x + 1, fillBoard.y + 1, fillBoard.w - 2, fillBoard.h - 2 };
}

int  ShowHightScore::showHightScore(SDL_Renderer* screen, TTF_Font* font, std::vector<int>& HightScore)
{
	setBackGround(screen);
	setString(HightScore);
	setText(screen, font);
	setRect();
	setSound();
	setBorder();
	int xmouse, ymouse;

	while (true)
	{
		// render
		RunBackground(hightScorebg, screen,false);
		RenderRectangle(screen, fillBoardColor, fillBack);
		someRenderOutLine(screen, outlineBoardColor, outlineBack);
		RenderRectangle(screen, fillBoardColor, fillBoard);
		someRenderOutLine(screen, outlineBoardColor, outlineBoard);
		for (int k = 0; k < MAX_HIGHT_SCORE; k++)
		{
			if (k == 0) {
				Title.renderText(titleRect.x, titleRect.y, screen);
				Back.loadFromRenderedText(font, screen);
				Back.renderText(backRect.x, backRect.y, screen);
			}
			hightScoreText[k].loadFromRenderedText(font, screen);
			hightScoreText[k].renderText(hightScoreRect[k].x, hightScoreRect[k].y, screen);
		}
		SDL_RenderPresent(screen);
		SDL_Delay(16);
		while (SDL_PollEvent(&hightScoreEvent))
		{
			switch (hightScoreEvent.type)
			{
			case SDL_QUIT:
				return M_EXIT;
				break;
			case SDL_MOUSEMOTION:
				xmouse = hightScoreEvent.button.x;
				ymouse = hightScoreEvent.button.y;
				for (int k = 0; k < MAX_HIGHT_SCORE; k++) {
					if (checkFocusButton(xmouse, ymouse, hightScoreRect[k]))
					{
						hightScoreText[k].setColor(TextObject::PURPLE_TEXT);
					}
					else {
						hightScoreText[k].setColor(TextObject::WHITE_TEXT);
					}
				}
				if (checkFocusButton(xmouse, ymouse, backRect)) {
					Back.setColor(TextObject::PURPLE_TEXT);
				}
				else {
					Back.setColor(TextObject::WHITE_TEXT);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				xmouse = hightScoreEvent.button.x;
				ymouse = hightScoreEvent.button.y;
				if (checkFocusButton(xmouse, ymouse, backRect))
				{
					Mix_PlayChannel(-1, pressHightScore, 0);
					SDL_Delay(200);
					for (int k = 0; k < MAX_HIGHT_SCORE; k++)
					{
						hightScoreText[k].free();
					}
					close();
					return M_MENU;
				}
				break;
			}
		}
	}
	return M_EXIT;
}