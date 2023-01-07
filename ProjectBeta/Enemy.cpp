#include "Enemy.h"

Enemy::Enemy(Texture* texture, Texture* nuz)
{
	this->IniTerorista(texture);
	this->IniNuz(nuz);
}

Enemy::~Enemy()
{
}


void Enemy::Update(float x)
{
	Move(x);
	this->nuz.setPosition(this->sprite.getPosition().x - this->sprite.getGlobalBounds().width + 10.f, this->sprite.getPosition().y - 2.f);
}

void Enemy::IniTerorista(Texture* texture)
{
	this->texture = texture;
	
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(1900.f, 905.f);
	this->sprite.setScale(0.4f, 0.4f);
}

void Enemy::IniNuz(Texture* nuz)
{
	this->TexturNuz = nuz;
	this->nuz.setTexture(*this->TexturNuz);
	this->nuz.setScale(0.4f, 0.4f);
	this->nuz.setPosition(this->sprite.getPosition().x - this->sprite.getGlobalBounds().width + 10.f, this->sprite.getPosition().y - 2.f);

}

void Enemy::Move(float x)
{

	this->sprite.move(x, 0.f);

}

void Enemy::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
	target.draw(this->nuz);
}
