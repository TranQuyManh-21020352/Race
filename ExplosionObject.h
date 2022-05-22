#pragma once
#ifndef EXPLOSION_OBJECT_H_
#define EXPLOSION_OBJECT_H_
#include "CommanFunc.h"
#include "BaseObject.h"

const int MAX_FRAME = 8;

class ExplosionObject : public BaseObject {
public:
	ExplosionObject();
	~ExplosionObject();
	void setClip();
	void setFrame(const int& fr_) { frame = fr_; }
	bool loadImageExp(std::string path, SDL_Renderer* screen);
	int getFrameWidth() { return frameWidth; }
	int getFrameHeight() { return frameHeight; }
	SDL_Rect getFrameClip(int pos) { return frameClip[pos]; }
private:
	int frameWidth;
	int frameHeight;
	int frame;
	SDL_Rect frameClip[MAX_FRAME];
};


#endif 

