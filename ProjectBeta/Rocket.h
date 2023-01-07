#pragma once
#include "Kulky.h"

class Rocket
{
private:
	Texture* texture;
	Sprite sprite;

public:
	Rocket(Texture* texture, float x);
	virtual ~Rocket();

	inline const Vector2f& getPosition()const {
		return this->sprite.getPosition();
	}

	inline FloatRect getGlobalBounds()const {
		return this->sprite.getGlobalBounds();
	}

	void IniRocket(Texture* texture, float x);
	void Move(float x);
	void Draw(RenderTarget& target);
	void Update(float x);
};

