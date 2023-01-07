#include "Kulky.h"

Kulky::Kulky(Texture* texture, float positionX, float positionY, bool left)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	
	//pokud je otoceni doleva strili doleva
	if (left == true) {
		this->sprite.setPosition(positionX - 10, positionY + 44);
		this->maxRychlost = Vector2f(-15.f, 0.f);
	}

	//strelba doprava
	else {
		this->sprite.setPosition(positionX + 100, positionY + 44);
		this->maxRychlost = Vector2f(15.f, 0.f);
	}
	this->sprite.setScale(0.35f, 0.35f);
}

Kulky::~Kulky()
{
}

void Kulky::Movement()
{
	this->sprite.move(this->maxRychlost.x,this->maxRychlost.y);
}

void Kulky::Update()
{
	this->Movement();
}

void Kulky::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
}
