#include "PlayGame.h"

void setExplosion(int posX, int posY, ExplosionObject& gExp, BaseObject& background_, CarObject& car_, TextObject& text_, std::vector<Obstacles>gObstacles, SDL_Renderer* screen) {
	// set posX,posy for frame of explosion
	posX -= gExp.getFrameWidth() * 0.5 - WIDTHCAR / 2;
	posY -= gExp.getFrameHeight() * 0.5 - HEIGHTCAR / 2;
	for (int k = 0; k < MAX_FRAME; k++) {
		RunBackground(background_, screen, true);
		for (int obs = 0; obs < gObstacles.size(); obs++) {
			gObstacles[obs].renderObstacles(screen);
		}
		car_.CarRender(screen);
		RenderRectangle(screen, FillColor, FillRect);
		RenderOutLine(screen, OutlineColor, OutlineRect);
		text_.renderText((SCREEN_WIDTH - text_.getWidthText()) / 2, 1, screen);
		SDL_Rect rect = gExp.getFrameClip(k);
		gExp.renderCar(posX, posY, screen, &rect);
		SDL_RenderPresent(screen);
		SDL_Delay(70);
	}
	gExp.free();// delete frame off  the screen
	RunBackground(background_, screen, true);
	for (int obs = 0; obs < gObstacles.size(); obs++) {
		gObstacles[obs].renderObstacles(screen);
	}
	RenderRectangle(screen, FillColor, FillRect);
	RenderOutLine(screen, OutlineColor, OutlineRect);
	text_.renderText((SCREEN_WIDTH - text_.getWidthText()) / 2, 1, screen);
	SDL_RenderPresent(screen);
}
void runCowndown(TextObject& CountdownText, Uint32& timeCountdown, Uint32& val, std::stringstream& valTextcoundown, std::string& Textcoundown)
{
	timeCountdown = val - (SDL_GetTicks() + 600) / 1000;
	if (timeCountdown == 4)
	{
		timeCountdown = 3;
	}
	valTextcoundown.str("");
	valTextcoundown << timeCountdown;
	Textcoundown = valTextcoundown.str().c_str();
	CountdownText.setText(Textcoundown);

}

void runGamePlay(SDL_Renderer* gRenderer, BaseObject& gBackGround, CarObject& gRedCar, TTF_Font* gFont, std::vector<Obstacles>& gObstacles, TextObject& gText, Uint32& time, Uint32& val, std::stringstream&
	valText, std::string& TextScore, int& Score,int& currentObstacles, int& timeAppearObstacles, int& timeMaxAppearObstacles) {
	// set Score by for time run
	time = (SDL_GetTicks() - 1200) / 1000 - val;
	valText.str("");
	valText << "Score: " << time;
	TextScore = valText.str().c_str();
	Score = time;
	gText.setText(TextScore);
	RunBackground(gBackGround, gRenderer, false);
	gRedCar.move();
	setObstacles(gObstacles, gRenderer, currentObstacles, timeAppearObstacles, timeMaxAppearObstacles);
	gText.loadFromRenderedText(gFont, gRenderer);
	renderObs(gObstacles, gRenderer);
	gRedCar.CarRender(gRenderer);
	RenderRectangle(gRenderer, FillColor, FillRect);
	RenderOutLine(gRenderer, OutlineColor, OutlineRect);
	gText.renderText((SCREEN_WIDTH - gText.getWidthText()) / 2, 1, gRenderer);
	SDL_RenderPresent(gRenderer);
}

void closeWhenFinish(BaseObject& gBackGround, CarObject& gRedCar,
	ExplosionObject& gExp, std::vector<Obstacles>& gObstacles,TextObject& gText,
	TTF_Font* gFont, Mix_Music* gMusic, Mix_Chunk* gCountdown, Mix_Chunk* gEffectCrash) {
	// release memory when play 1 turn 
	SDL_Delay(1500);
	gRedCar.free();
	for (int k = 0; k < gObstacles.size(); k++) {
		gObstacles[k].free();
	}
	gExp.free();
	gText.free();
	TTF_CloseFont(gFont);
	Mix_FreeChunk(gEffectCrash);
	Mix_FreeChunk(gCountdown);
	Mix_FreeMusic(gMusic);
	gBackGround.free();
}