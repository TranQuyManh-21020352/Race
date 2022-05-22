#include "ObstaclesObject.h"

Obstacles::Obstacles()
{
	PosXObstacles = 0;
	PosYObstacles = -60;
	VelObstacles = 6;
    ObsCollision = false;
	ObsPixels.resize(MaxPixels);
    ObsPixels[0].w = 26;
    ObsPixels[0].h = 1;
    ObsPixels[1].w = 32;
    ObsPixels[1].h = 1;
    ObsPixels[2].w = 34;
    ObsPixels[2].h = 1;
    ObsPixels[3].w = 36;
    ObsPixels[3].h = 1;
    ObsPixels[4].w = 38;
    ObsPixels[4].h = 1;
    ObsPixels[5].w = 40;
    ObsPixels[5].h = 48;
    ObsPixels[6].w = 38;
    ObsPixels[6].h = 1;
    ObsPixels[7].w = 36;
    ObsPixels[7].h = 1;
    ObsPixels[8].w = 34;
    ObsPixels[8].h = 1;
    ObsPixels[9].w = 32;
    ObsPixels[9].h = 1;
    ObsPixels[10].w = 30;
    ObsPixels[10].h = 1;
    ObsPixels[11].w = 28;
    ObsPixels[11].h = 1;
    ObsPixels[12].w = 26;
    ObsPixels[12].h = 1;
    shilfObsCollision();
}

Obstacles :: ~Obstacles()
{
	free();
}

void Obstacles::setPosition(int x_, int y_)
{
	PosXObstacles = x_;
	PosYObstacles = y_;
}
void Obstacles::setVelocity(int vel_)
{
	VelObstacles += vel_;
}
bool Obstacles::loadImageObstacles(std::string path,SDL_Renderer* screen)
{
	bool res = BaseObject::loadImage(path, screen);
	return res;
}

void Obstacles::renderObstacles(SDL_Renderer* des)
{
	BaseObject::renderCar(PosXObstacles, PosYObstacles, des, NULL, NULL);
}

void Obstacles::moveObstacles()
{
    if (ObsCollision)
    {
        VelObstacles = 0;
    }
    PosYObstacles += VelObstacles;
    shilfObsCollision();
}

void Obstacles::shilfObsCollision()
{
    int value = 0;
    for (int pix = 0; pix < ObsPixels.size(); pix++)
    {
        ObsPixels[pix].x = PosXObstacles + (WIDTHCAR - ObsPixels[pix].w) / 2;
        ObsPixels[pix].y = PosYObstacles + value;
        value += ObsPixels[pix].h;
    }
}

void Obstacles:: setObsCollision(bool obscols_)
{
    ObsCollision = obscols_;
}