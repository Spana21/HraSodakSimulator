#include "Player.h"



Player::Player(Texture* texture, Texture* bulletTexture, Texture* texture2, Texture* texture3)
{
	// inicializace
	this->hp = 10;
	this->hpMax = 10;
	
	this->damage = 1;

	// aby nelital
	this->jumpdel = 0; 
	
	//hrac otoceni do leva → dulezite pro streli (jestli to poleti do leva nebo do prava]
	this->playerL = false;    
	
	//GunShotSound
	this->IniGunshot();

	//POSTAVA
	this->IniPlayer(texture,texture2, texture3);

	//pohyb
	this->IniPohyb();

	//KULKY
	this->IniKulky(bulletTexture);
}

Player::~Player()
{
}

void Player::IniPlayer(Texture* texture, Texture* texture2, Texture* texture3)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture); // texturu hodime do sprite
	this->sprite.setScale(0.5f, 0.5f); // velikost characteru
	this->sprite.setPosition(960.f, 1080.f - this->sprite.getGlobalBounds().height);
	
	//textura postava miri do leva 
	this->texture2 = texture2; 
	
	//Rakev
	this->rakev = texture3;
	
}

void Player::IniKulky(Texture* bullet)
{
	this->bulletTexture = bullet;
	this->shootTimer = 50;
	this->shootTimerMax = this->shootTimer;
}

void Player::IniPohyb() {
	this->controls[0] = 22;
	this->controls[1] = 18;
	this->controls[2] = 0;
	this->controls[3] = 3;
	this->controls[4] = 57; // 57 = mezernik, zbytek wasd
}

void Player::IniGunshot()
{
	this->buffer.loadFromFile("Sound/gunshot.wav");
	this->sound.setBuffer(buffer);
	sound.setVolume(10.f);
}

void Player::Movement()
{
	//skakani
	this->Jump();

	//a
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[2]))) {
		playerL = true; // hrac je miri doleva
		sprite.setTexture(*this->texture2);  //zmenime texturu
		this->sprite.move(-10.f, 0.f);
		
		//Streli
		Combat();
	}
	
	//d
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[3]))) {
		playerL = false;
		sprite.setTexture(*this->texture);
		this->sprite.move(10.f, 0.f);
		
		//Streli
		Combat();
	}

	//Strileni bez pohybu 
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[4]))) {                   
		Combat();
	}
}

void Player::Combat()
{
	//SPACE
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[4])) && (this->shootTimer >= this->shootTimerMax))
	{
		sound.play();
		this->bullets.push_back(Kulky(bulletTexture, this->sprite.getPosition().x, this->sprite.getPosition().y, playerL));
		this->shootTimer = 0;
	}
	
}


void Player::Jump()
{
	//w
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[0])) && (jumpdel < 35)) // at postava nelita
	{
		this->sprite.move(0.f, -20.f);
		jumpdel++;
		
	}

	//Gravitace
	if (this->sprite.getPosition().y + this->sprite.getGlobalBounds().height < 1080) {
		this->sprite.move(0.f, 10.f);
			
	}
		
	//kdyz uvolnim klavesu w a zmacku neco jineho 
	if (!Keyboard::isKeyPressed(Keyboard::Key(this->controls[0]))) {
		jumpdel = 0;
	}
}


void Player::ColWindow(float x, float y)
{
	//leva obrazovka
	if (this->sprite.getPosition().x < 0)
		this->sprite.setPosition(0, this->sprite.getPosition().y);
	
	//prava obrazovka
	else if (this->sprite.getPosition().x + this->sprite.getGlobalBounds().width > x) {
		this->sprite.setPosition(x - this->sprite.getGlobalBounds().width, this->sprite.getPosition().y);
	}

}


void Player::Update(float windowX, float windowY, bool smrt)
{
	this->ColWindow(windowX, windowY);
	
	//Timers
	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer++;

	//Pokud jsem mrtvy misto textury hrace se objevi rakev
	if (smrt == true) {
		sprite.setTexture(*this->rakev);
		sprite.setPosition(this->sprite.getPosition().x, windowY - this->sprite.getGlobalBounds().height + 28.f);
	}
	else {
		this->Movement();
	}

}


void Player::Draw(RenderTarget &targer, bool smrt)
{

	targer.draw(this->sprite);
	
	//Kdybych pred smrti vystrelil → tak kulka zmizi
	if (smrt == false) {
		for (size_t i = 0; i < this->bullets.size(); i++)
		{
			this->bullets[i].Draw(targer);
		}
	}
}
