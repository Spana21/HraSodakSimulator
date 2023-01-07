#include "Start.h"

Start::Start(Font* font, Texture* texture, Texture* texture2)
{
	//ini Font
	this->jmeno.setFont(*font);
	this->uvod.setFont(*font);
	this->start.setFont(*font);
	this->enter.setFont(*font);
	
	//Klavesnice
	this->Navod(texture,texture2);
	
	//Text
	this->Text();
}

Start::~Start()
{
}

void Start::Text()
{
	this->jmeno.setCharacterSize(80);
	this->jmeno.setString("SODak simulator");
	this->jmeno.setPosition(1920.f / 2.f - jmeno.getGlobalBounds().width / 2.f, 20.f);

	this->uvod.setCharacterSize(30);
	this->uvod.setString("Behem tve sluzby na Univerzite Obrany, teroristicka \nskupina, ktera si rika ,,Zdemolovat Brno'', prave \nzautocila na Brno. Jejich cilem je take znicit tvoji \nmilovanou univerzitu. Ty, ktery sis prave uzival chut \nlahodneho lunch meatu, musis zabranit zniceni univerzity.\nTvym ukolem je zabit co nejvice teroristu, vyhnout se \ntankum a raketam, a dostat se do urovne 10.");
	this->uvod.setPosition(jmeno.getPosition().x, 250.f);

	this->start.setCharacterSize(30);
	this->start.setString("Zahajeni obrany:");
	this->start.setPosition(jmeno.getPosition().x, uvod.getPosition().y + uvod.getGlobalBounds().height + 50);

	this->enter.setCharacterSize(35);
	this->enter.setString("enter");
	this->enter.setFillColor(Color::Red);
	this->enter.setPosition(jmeno.getPosition().x + start.getGlobalBounds().width + 9.f, start.getPosition().y -3.f);

}

void Start::Navod(Texture* texture, Texture* texture2)
{
	//Wasd
	this->texture = texture;
	sprite.setTexture(*this->texture);
	sprite.setPosition(650.f, 600.f);
	sprite.setScale(0.3f, 0.3f);

	//Space
	this->texture2 = texture2;
	sprite2.setTexture(*this->texture2);
	this->sprite2.setPosition(sprite.getPosition().y + sprite.getGlobalBounds().width + 100.f, sprite.getPosition().y + 50.f);
	sprite2.setScale(0.2f, 0.2f);
}


void Start::Draw(RenderTarget& target)
{
	target.draw(this->jmeno);
	target.draw(this->uvod);
	target.draw(this->enter);
	target.draw(this->start);
	target.draw(this->sprite);
	target.draw(this->sprite2);
}
