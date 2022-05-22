#ifndef OBSTACLES_OBJECT_H_
#define OBSTACLES_OBJECT_H_



#include "CommanFunc.h"
#include "BaseObject.h"

class Obstacles : public BaseObject
{
	public:
		Obstacles();
		~Obstacles();
		void setPosition(int x_, int y_);
		void setVelocity(int vel_);
		bool loadImageObstacles(std :: string path, SDL_Renderer* screen);
		void renderObstacles(SDL_Renderer* des);
		void moveObstacles();
		void setObsCollision(bool obscols_);
		int GetPosXObstacles() { return PosXObstacles; }
		int GetPosYObstacles() { return PosYObstacles; }
		int GetVelObstacles() { return VelObstacles; }
		std::vector<SDL_Rect>& getObsPixels() { return ObsPixels; }
	private:
		int PosXObstacles;
		int PosYObstacles;
		int VelObstacles;
		bool ObsCollision;
		std::vector<SDL_Rect>ObsPixels;
		void shilfObsCollision();
};


#endif 



