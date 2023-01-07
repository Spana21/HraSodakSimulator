#pragma once
#include "Kulky.h"


class Start
{
private:
	Text jmeno;
	Text uvod;
	Text start;
	Text enter;
	
	//wasd
	Texture* texture; 
	Sprite sprite;

	//Space
	Texture* texture2;
	Sprite sprite2;

public:
	Start(Font* font, Texture* texture, Texture* texture2);
	~Start();
	void Text();
	void Navod(Texture* texture, Texture* texture2);
	void Draw(RenderTarget& target);
};

