#include "TextObject.h"

TextObject::TextObject()
{
	textColor = { 255, 255, 255, 255 };
	TWidth = 0;
	THeight = 0;
	Text = "";
	Ttexture = NULL;
}

TextObject::~TextObject() 
{
	free();
}

void TextObject :: free()
{
	if (Ttexture != NULL)
	{
		SDL_DestroyTexture(Ttexture);
		Ttexture = NULL;
		TWidth = 0;
		THeight = 0;
	}
}

bool TextObject::loadFromRenderedText(TTF_Font* font, SDL_Renderer* screen)
{
	free();
	SDL_Surface* loadSurFace = TTF_RenderText_Blended(font, Text.c_str(), textColor);
	if (loadSurFace == NULL)
	{
		std::cout << "unable to load font :" << Text.c_str() << TTF_GetError() << std::endl;
	}
	else
	{
		Ttexture = SDL_CreateTextureFromSurface(screen, loadSurFace);
		if (Ttexture != NULL) {
			TWidth = loadSurFace->w;
			THeight = loadSurFace->h;
		}
		else {
			std::cout << "Can not create texture: " << Text.c_str() << SDL_GetError() << std::endl;
		}
		
	}	
	SDL_FreeSurface(loadSurFace);
	return Ttexture != NULL;
}

void TextObject::renderText(int x, int y, SDL_Renderer* screen, SDL_Rect* clip , double angle , SDL_Point* center , SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, TWidth, THeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, Ttexture, clip, &renderQuad, angle, center, flip);
}

void TextObject::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	textColor.r = red;
	textColor.g = green;
	textColor.b = blue;
}
void TextObject::setColor(int type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255, 0, 0,255 };
		textColor = color;
	}
	else if(type == WHITE_TEXT) {
		SDL_Color color = { 255, 255, 255, 255 };
		textColor = color;
	}
	else if (type == YELOW_TEXT)
	{
		SDL_Color color = { 255, 255, 0, 255 };
		textColor = color;
	}
	else if (type == GREEN_TEXT) {
		SDL_Color color = { 124, 252, 0, 255 };
		textColor = color;
	}
	else if (type = PURPLE_TEXT) {
		SDL_Color color = { 186,85,211, 255 };
		textColor = color;
	}
	else
	{
		SDL_Color color = { 0, 0, 0, 255 };
		textColor = color;
	}
}

void TextObject::setText(std::string &text_) {
	Text = text_;
}