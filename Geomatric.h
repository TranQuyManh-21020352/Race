#pragma once
#ifndef GEOMATRIC_H_
#define GEOMATRIC_H_
#include "CommanFunc.h"

void RenderOutLine(SDL_Renderer* screen, const SDL_Color& outlineColor, const SDL_Rect& outlineRect);
void someRenderOutLine(SDL_Renderer* screen, const SDL_Color& outlineColor, const SDL_Rect& outlineRect);
void RenderRectangle(SDL_Renderer* screen,const SDL_Color& fillColor, const SDL_Rect& fillRect_);

#endif 
