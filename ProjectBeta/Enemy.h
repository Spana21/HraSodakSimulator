#pragma once
#include "Kulky.h"

class Enemy
{
private:
	//Enemy
	Texture* texture;
	Sprite sprite;
	
	//Nuz
	Texture* TexturNuz;
	Sprite nuz;

	

public:
	Enemy(Texture* texture, Texture* nuz);
	virtual ~Enemy();

	inline const Vector2f& getPosition()const {
		return this->sprite.getPosition();
	}
	inline FloatRect getGlobalBounds()const {
		return this->sprite.getGlobalBounds();
	}

	void IniTerorista(Texture* texture);
	void IniNuz(Texture* nuz);
	void Move(float x);
	void Draw(RenderTarget& target);
	void Update(float x);
};

