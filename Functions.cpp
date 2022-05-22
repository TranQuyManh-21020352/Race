#include "Functions.h"

int randomObstacles()
{
	return rand() % MaxLane;
}
// setRect for runbackground
void setRect() {
	pic1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - speed * i };
	pic2 = { 0, SCREEN_HEIGHT - speed * i, SCREEN_WIDTH, speed * i };
	pic3 = { 0, speed * i, SCREEN_WIDTH, SCREEN_HEIGHT - speed * i };
	pic4 = { 0, 0, SCREEN_WIDTH, speed * i };
}

void RunBackground(BaseObject& background, SDL_Renderer* screen,bool explosion)
{
	setRect();
	if (SCREEN_HEIGHT - i * speed < 0)
	{
		i = 0;
	}
	background.renderBackground(screen, &pic1, &pic3);
	background.renderBackground(screen, &pic2, &pic4);
	i++;
	// when have collision is stop runbackground
	if (explosion) {
		i--;
	}
}

void setObstacles(std::vector<Obstacles>& Obstacle, SDL_Renderer* screen, int& currentObstacles,int& timeAppearObstacles, int& timeMaxAppear)
{
	if (timeAppearObstacles < timeMaxAppear)
	{
		timeAppearObstacles++;
	}
	if (currentObstacles < MaxObstacles) {
		if (timeAppearObstacles == timeMaxAppear)
		{
			// random pos obstacles appear( 1 in 4 lane) 
			int index = randomObstacles();
			Obstacles current;
			if (index == 0)
			{
				current.setPosition(110, POSITIONY);
			}
			else if (index == 1)
			{
				current.setPosition(110 + 75, POSITIONY);
			}
			else if (index == 2)
			{
				current.setPosition(110 + 75 * 2, POSITIONY);
			}
			else if (index == 3)
			{
				current.setPosition(110 + 75 * 3, POSITIONY);
			}
			Obstacle.push_back(current);
			for (int obs = 0; obs < Obstacle.size(); obs++)
			{
					Obstacle[obs].loadImageObstacles("image//obstacles.png", screen);
			}
			timeAppearObstacles = 0;
			currentObstacles++;
		}
	}
}

void renderObs(std::vector<Obstacles>& Obstacle,SDL_Renderer* screen)
{
	for (int obs = 0; obs < Obstacle.size(); obs++)
	{
		if (Obstacle[obs].GetPosYObstacles() > SCREEN_HEIGHT + 60)
		{
			int random = rand() % 2;// random color obstacles
			if (random == 0) {
				Obstacle[obs].loadImageObstacles("image//obstacles.png", screen);
			}
			else {
				Obstacle[obs].loadImageObstacles("image//yelowCar_reverse.png", screen);
			}
			int index = randomObstacles();// reposition for obstacles when out of screen
			if (index == 0)
			{
				Obstacle[obs].setPosition(110, POSITIONY);
			}
			else if (index == 1)
			{
				Obstacle[obs].setPosition(110 + 75, POSITIONY);
			}
			else if (index == 2)
			{
				Obstacle[obs].setPosition(110 + 75 * 2, POSITIONY);
			}
			else if (index == 3)
			{
				Obstacle[obs].setPosition(110 + 75 * 3, POSITIONY);
			}
		}
		Obstacle[obs].moveObstacles();
		Obstacle[obs].renderObstacles(screen);
	}
	
}
// function increase velocity of obstacles
void setVelObstacles(std::vector<Obstacles>&obstacle, int velObs) {
	for (int obs = 0; obs < obstacle.size(); obs++)
	{
		obstacle[obs].setVelocity(velObs);
	}
}
// function check colllision between two 2 car by pixels
bool checkCollision(std::vector<SDL_Rect>&A, std::vector<SDL_Rect>&B)
{
	int Top_A, Top_B;
	int Bottom_A, Bottom_B;
	int Left_A, Left_B;
	int Right_A, Right_B;
	for (int Apix = 0; Apix < A.size(); Apix++)
	{
		Top_A = A[Apix].y;
		Bottom_A = A[Apix].y + A[Apix].h;
		Left_A = A[Apix].x;
		Right_A = A[Apix].x + A[Apix].w;
		for (int Bpix = 0; Bpix < B.size(); Bpix++)
		{
			Top_B = B[Bpix].y;
			Bottom_B = B[Bpix].y + B[Bpix].h;
			Left_B = B[Bpix].x;
			Right_B = B[Bpix].x + B[Bpix].w;
			if (((Top_A > Bottom_B) || (Bottom_A < Top_B) || (Right_A < Left_B) || (Left_A > Right_B)) == false)
			{
				std::cout << "car: " << Apix << " obs: " << Bpix << std::endl;
				return true;
			}
		}
	}
	return false;
}


void SetCountdown(SDL_Renderer* screen, TTF_Font* font, Mix_Chunk* Coundown_, BaseObject& background, CarObject& car,TextObject& text, TextObject& textcoundown_)
{
		background.renderBackground(screen, &pic1, &pic3);
		background.renderBackground(screen, &pic2, &pic4);
		car.CarRender(screen);
		RenderRectangle(screen, FillColor, FillRect);
		RenderOutLine(screen, OutlineColor, OutlineRect);
		text.renderText((SCREEN_WIDTH - text.getWidthText()) / 2, 1, screen);
		if (!textcoundown_.loadFromRenderedText(font,screen))
		{
			success = false;
		}
		textcoundown_.renderText((SCREEN_WIDTH - textcoundown_.getWidthText()) / 2, SCREEN_HEIGHT / 4, screen);
		SDL_Delay(500);
		SDL_RenderPresent(screen);
		
}
// function check pos is inside of button?
bool checkFocusButton(const int& x, const int& y, SDL_Rect& check) {
	if (x >= check.x && x <= check.x + check.w && y >= check.y && y <= check.y + check.h)
	{
		return true;
	}
	return false;
}
// function sort hightscore
void sort(std::vector<int>& hightscore_)
{
	for (int k = 0; k < hightscore_.size(); k++)
	{
		for (int j = k + 1; j < hightscore_.size(); j++)
		{
			if (hightscore_[j] > hightscore_[k])
			{
				int temp = hightscore_[k];
				hightscore_[k] = hightscore_[j];
				hightscore_[j] = temp;
			}
		}
	}
}