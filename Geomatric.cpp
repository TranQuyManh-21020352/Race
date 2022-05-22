#include "Geomatric.h"

void RenderOutLine(SDL_Renderer* screen, const SDL_Color& outlineColor,const SDL_Rect& outlineRect)
{
	SDL_Rect Outline = { outlineRect.x, outlineRect.y, outlineRect.w, outlineRect.h };
	SDL_SetRenderDrawColor(screen, outlineColor.r, outlineColor.g, outlineColor.b, 255);
	SDL_RenderDrawRect(screen, &outlineRect);
}
void RenderRectangle(SDL_Renderer* screen, const SDL_Color& fillColor, const SDL_Rect& fillRect_)
{
	SDL_Rect fillRect = { fillRect_.x, fillRect_.y ,fillRect_.w ,fillRect_.h };
	SDL_SetRenderDrawColor(screen, fillColor.r, fillColor.g, fillColor.b, 255);
	SDL_RenderFillRect(screen, &fillRect);
}
void someRenderOutLine(SDL_Renderer* screen, const SDL_Color& outlineColor, const SDL_Rect& outlineRect)
{
	SDL_Rect Outline[5];
	Outline[0] = {outlineRect.x, outlineRect.y, outlineRect.w, outlineRect.h};
	for (int k = 1; k < 5; k++)
	{
		Outline[k] = {Outline[k - 1].x + 1, Outline[k - 1].y + 1, Outline[k - 1].w - 2, Outline[k - 1].h - 2 };
	}
	SDL_SetRenderDrawColor(screen, outlineColor.r, outlineColor.g, outlineColor.b, 255);
	for (int k = 0; k < 5; k++) {
		SDL_RenderDrawRect(screen, &Outline[k]);
	}
	
}
