#pragma once
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

using namespace sf;

class Kulky
{
private:
	Texture* texture;
	Sprite sprite;

	Vector2f maxRychlost;
public:
	Kulky(Texture* texture, float positionX, float positionY, bool left);
	virtual ~Kulky();

	//Accessore
	inline FloatRect getGlobalBounds()const {
		return this->sprite.getGlobalBounds();
	}
	inline const Vector2f& getPosition()const {
		return this->sprite.getPosition();
	}

	//Funkce 
	void Movement();
	void Update();
	void Draw(RenderTarget& target);
};

