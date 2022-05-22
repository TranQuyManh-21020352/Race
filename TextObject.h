#ifndef TEXTOBJECT_H_
#define TEXTOBJECT_H_

#pragma once
#include "CommanFunc.h"

class TextObject {
	public:
		TextObject();
		~TextObject();
		enum TextColor
		{
			RED_TEXT = 0,
			WHITE_TEXT = 1,
			YELOW_TEXT = 2,
			GREEN_TEXT = 3,
			PURPLE_TEXT = 4,
		};
		void free();
		
		void setColor(int type);
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void setText(std::string &text_);
		bool loadFromRenderedText(TTF_Font* font, SDL_Renderer* screen);
		void renderText( int x, int y, SDL_Renderer* screen,SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		int getWidthText() { return TWidth; }
		int getHeightText() { return THeight; }
		SDL_Color getColor() { return textColor; }
		std::string getText() { return Text; }
	private:
		SDL_Color textColor;
		std::string Text;
		SDL_Texture* Ttexture;
		int TWidth;
		int THeight;

};



#endif 


