#ifndef CAR_OBJECT_H_
#define CAR_OBJECT_H_

#include "CommanFunc.h"
#include "BaseObject.h"
class CarObject : public BaseObject{
	public:
	CarObject();
	~CarObject();
	void freeCar();
	bool loadImageCar(std :: string path, SDL_Renderer* screen);
	void setPosX(int x_);
	void setPosY(int y_);
	void CarRender(SDL_Renderer* des);
	void handleInputAction(SDL_Event e, SDL_Renderer* screen);
	void setCheckCollision(bool collision_);
	void move();
	int GetPosXCar() { return PosX; }
	int GetPosYCar() { return PosY; }
	int GetVelxCar() { return Velx; }
	int GetVelyCar() { return Vely; }
	SDL_Rect getCarRect() { return CarRect; }
	std::vector<SDL_Rect>& getCarPixels() { return CarPixels; }
private:
	int PosX;
	int PosY;
	int Velx;
	int Vely;
	int Distance;
	bool CarCollision;
	SDL_Rect CarRect;
	std::vector<SDL_Rect>CarPixels;
	void shilfCarCollision();
};


#endif