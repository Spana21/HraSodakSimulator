#include "Rocket.h"
Rocket::Rocket(Texture* texture, float x)
{
	this->IniRocket(texture, x);

}

Rocket::~Rocket()
{
}

void Rocket::IniRocket(Texture* texture, float x)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(x, -150.f);
	this->sprite.setScale(0.2f, 0.2f);
}


void Rocket::Update(float x)
{
	Move(x);

}


void Rocket::Move(float x)
{
	this->sprite.move(0.f, x);
}

void Rocket::Draw(RenderTarget& target)
{
	target.draw(this->sprite);

}