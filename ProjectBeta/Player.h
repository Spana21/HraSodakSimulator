#pragma once
#include "Kulky.h"


using namespace sf;

class Player
{
private:

	//Hrac
	Texture* texture;
	Sprite sprite;

	//Rakev
	Texture* texture2;
	Texture* rakev;

	//GunShotSound
	SoundBuffer buffer;
	Sound sound;

	//ShootTimer
	int shootTimer;
	int shootTimerMax;

	//Kulky
	Texture* bulletTexture;
	std::vector<Kulky>bullets;

	//Klavesnice
	int controls[5];

	bool playerL;
	
	int jumpdel;
	
	int hp;
	int hpMax;
	
	int damage;
	
public:
	Player(Texture* texture, Texture* bulletTexture, Texture* texture2, Texture* texture3);
	virtual ~Player();

	inline FloatRect getGlobalBounds()const {
		return this->sprite.getGlobalBounds();
	}

	inline std::vector<Kulky>& getBullets() {
		return this->bullets;
	}
	

	inline const Vector2f& getPosition()const {
		return this->sprite.getPosition();
	}
	
	inline const String getHpAsString()const {
		return std::to_string(this->hp) + "/" + std::to_string(this->hpMax);
	}
	
	inline void takeDamage(int damage) { this->hp -= damage; }
	
	inline const int& getHp() const { return this->hp;}

	void IniPlayer(Texture* texture, Texture* texture2, Texture* texture6);
	void IniKulky(Texture* bullet);
	void IniPohyb();
	void IniGunshot();
	void Combat();
	void Jump();
	void Movement();
	void ColWindow(float x, float y);
	void Update(float windowX, float windowY, bool smrt);
	void Draw(RenderTarget &targer, bool smrt);


};

