#pragma once
#ifndef TIME_OBJECT_H_
#define TIEM_OBJECT_H_
#include "CommanFunc.h"

class LTimer {
public:
	LTimer();
	void start();
	void stop();
	void pause();
	void unpause();

	// Gets the timer's time
	Uint32 getTicks();
	bool isStarted();
	bool isPaused();
	// checks the status of the timer
private:

	Uint32 mStartTicks;
	Uint32 mPausedTicks;

	bool mPaused;
	bool mStarted;

};
#endif 
