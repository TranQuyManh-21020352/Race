#include "ExplosionObject.h"

ExplosionObject::ExplosionObject() {
	frameWidth = 0;
	frameHeight = 0;
	frame = 0;
}

ExplosionObject:: ~ExplosionObject() {
	free();
}

void ExplosionObject::setClip() {
	if (frameWidth > 0 && frameHeight > 0) {
		for (int fr = 0; fr < MAX_FRAME; fr++) {
			frameClip[fr] = { frameWidth * fr, 0, frameWidth, frameHeight };
		}
	}
}

bool ExplosionObject::loadImageExp(std::string path, SDL_Renderer* screen) {
	bool res = BaseObject::loadImage(path, screen);
	if (res) {
		frameWidth = BaseObject::getWidth() / MAX_FRAME;
		frameHeight = BaseObject::getHeight();
	}
	return res;
}