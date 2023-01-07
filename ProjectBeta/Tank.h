#pragma once
#include "Kulky.h"

class Tank
{
private:
	Texture* texture;
	Sprite sprite;

public:
	Tank(Texture* texture);
	virtual ~Tank();

	inline const Vector2f& getPosition()const {
		return this->sprite.getPosition();
	}
	
	inline FloatRect getGlobalBounds()const {
		return this->sprite.getGlobalBounds();
	}
	
	void IniTank(Texture* texture);
	void Move(float x);
	void Draw(RenderTarget& target);
	void Update(float x);
};

