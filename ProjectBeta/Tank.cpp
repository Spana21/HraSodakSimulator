#include "Tank.h"
Tank::Tank(Texture* texture)
{
	this->IniTank(texture);
	
}

Tank::~Tank()
{
	
}

void Tank::IniTank(Texture* texture)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(-300.f, 935.f);
	this->sprite.setScale(0.7f, 0.7f);
}


void Tank::Update(float x)
{
	Move(x);
	
}


void Tank::Move(float x)
{
	this->sprite.move(x, 0.f);
}

void Tank::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
	
}
