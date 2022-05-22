#include "BaseObject.h"


BaseObject :: BaseObject()
{
	bObject = NULL;
	bWidth = 0;
	bHeight = 0;
}

BaseObject :: ~BaseObject()
{
	free();
}

bool BaseObject::loadImage(std::string path,SDL_Renderer* screen)
{
	//free();
	SDL_Surface* loadSurFace = IMG_Load(path.c_str());
	SDL_Texture* loadTexTure = NULL;

	if (loadSurFace == NULL)
	{
		std::cout << "unable to load image: " << path.c_str()<<IMG_GetError() << std::endl;
	}
	else {
		SDL_SetColorKey(loadSurFace, SDL_TRUE, SDL_MapRGB(loadSurFace->format, 167, 175, 180));
		loadTexTure = SDL_CreateTextureFromSurface(screen, loadSurFace);
		if (loadTexTure == NULL)
		{
			std::cout << "unable to create texture: " << path.c_str() << SDL_GetError() << std::endl;
		}
		else {
			bWidth = loadSurFace->w;
			bHeight = loadSurFace->h;
			
		}
	}
	bObject = loadTexTure;
	SDL_FreeSurface(loadSurFace);
	return bObject != NULL;
}

void BaseObject::free()
{
	if (bObject != NULL)
	{
		bWidth = 0;
		bHeight = 0;
		SDL_DestroyTexture(bObject);
		bObject = NULL;
	}
}

void BaseObject::renderBackground(SDL_Renderer* des, SDL_Rect* Clip , SDL_Rect* Render )
{
	SDL_RenderCopy(des, bObject, Clip, Render);
}
void BaseObject::renderCar(int x, int y,SDL_Renderer* des, SDL_Rect* clip,SDL_Rect* Render, double angle, SDL_RendererFlip flip)
{
	
	SDL_Rect Renderquad = { x, y, bWidth, bHeight };
	if (clip != NULL)
	{
		Renderquad.w = clip->w;
		Renderquad.h = clip->h;
	}
	//SDL_RenderCopy(des, bObject, clip, &Renderquad);
	SDL_RenderCopyEx(des, bObject, clip, &Renderquad, angle, NULL, flip);
}
