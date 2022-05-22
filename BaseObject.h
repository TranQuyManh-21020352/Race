
#ifndef BASIC_OBJECT_H_
#define BASIC_OBJECT_H_

#include "CommanFunc.h"

class BaseObject {
public:
	BaseObject();

	~BaseObject();

	void free();

	bool loadImage(std :: string path, SDL_Renderer* screen);
	void renderBackground(SDL_Renderer* des, SDL_Rect* Clip = NULL, SDL_Rect* Render = NULL);
	void renderCar(int x, int y, SDL_Renderer* des, SDL_Rect* Clip = NULL, SDL_Rect* Render = NULL, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth() const { return bWidth; }
	int getHeight() const { return bHeight; }
	SDL_Texture* getObject () const{ return bObject; }
private:
	SDL_Texture* bObject;

	int bWidth;
	int bHeight;

};
#endif