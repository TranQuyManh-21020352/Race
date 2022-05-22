#include "CarObject.h"

CarObject :: CarObject()
{
	PosX = (SCREEN_WIDTH - WIDTHCAR) / 2;
	PosY = SCREEN_HEIGHT - HEIGHTCAR;
	Velx = 0;
	Vely = 0;
    Distance = 10;
	CarRect = { (SCREEN_WIDTH - WIDTHCAR)/2, SCREEN_HEIGHT - HEIGHTCAR, WIDTHCAR, HEIGHTCAR };
    CarCollision = false;
    CarPixels.resize(MaxPixels);
    // width and height of pixels on image
    CarPixels[0].w = 26;
    CarPixels[0].h = 1;
    CarPixels[1].w = 28;
    CarPixels[1].h = 1;
    CarPixels[2].w = 30;
    CarPixels[2].h = 1;
    CarPixels[3].w = 32;
    CarPixels[3].h = 1;
    CarPixels[4].w = 34;
    CarPixels[4].h = 1;
    CarPixels[5].w = 36;
    CarPixels[5].h = 1;
    CarPixels[6].w = 38;
    CarPixels[6].h = 1;
    CarPixels[7].w = 40;
    CarPixels[7].h = 48;
    CarPixels[8].w = 38;
    CarPixels[8].h = 1;
    CarPixels[9].w = 36;
    CarPixels[9].h = 1;
    CarPixels[10].w = 34;
    CarPixels[10].h = 1;
    CarPixels[11].w = 32;
    CarPixels[11].h = 1;
    CarPixels[12].w = 26;
    CarPixels[12].h = 1;
    shilfCarCollision();
}

CarObject :: ~CarObject()
{
	free();
}

void CarObject:: setPosX(int x_) {
    PosX = x_;
}

void CarObject:: setPosY(int y_) {
    PosY = y_;
}

bool CarObject::loadImageCar(std::string path, SDL_Renderer* screen)
{
	bool res = BaseObject::loadImage(path, screen);
	return res;
}

void CarObject::CarRender(SDL_Renderer* des)
{
    BaseObject::renderCar(PosX, PosY, des, NULL, NULL);
}

void CarObject::handleInputAction(SDL_Event e, SDL_Renderer* screen)
{
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_RIGHT:
                Velx += Distance;
                break;
            case SDLK_LEFT:
                Velx -= Distance;
                break;
            case SDLK_UP:
                Vely -= Distance;
                break;
            case SDLK_DOWN:
                Vely += Distance;
                break;
            }
        }
        else if (e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_RIGHT:
                Velx -= Distance;
                break;
            case SDLK_LEFT:
                Velx += Distance;
                break;
            case SDLK_UP:
                Vely += Distance;
                break;
            case SDLK_DOWN:
                Vely -= Distance;
                break;
            }
        }
}

void CarObject::setCheckCollision(bool collision_)
{
    CarCollision = collision_;
}

void CarObject::move()
{
    PosX += Velx;
    shilfCarCollision();
    if (PosX + WIDTHCAR > SCREEN_WIDTH - 85 || PosX < 85 )
    {
        if (PosX + WIDTHCAR > SCREEN_WIDTH - 85)
        {
            PosX = 365;
        }
        if (PosX < 85)
        {
            PosX = 85;
        }
        shilfCarCollision();
    }
    if (CarCollision)
    {
        PosX -= Velx;
        shilfCarCollision();
    }
    PosY += Vely;
    shilfCarCollision();
    if (PosY < 30 || PosY  > SCREEN_HEIGHT - HEIGHTCAR )
    {
        if (PosY < 30) {
            PosY = 30;
        }
        else {
            PosY = SCREEN_HEIGHT - HEIGHTCAR;
        }
        shilfCarCollision();
    }
    if (CarCollision)
    {
        PosY -= Vely;
        shilfCarCollision();
    }
}
// update pos of pixels when car move
void CarObject::shilfCarCollision()
{
    int value = 0;
    for (int pix = 0; pix < CarPixels.size(); pix++)
    {
        CarPixels[pix].x = PosX + (WIDTHCAR - CarPixels[pix].w) / 2;
        CarPixels[pix].y = PosY + value;
        value += CarPixels[pix].h;
    }
}
