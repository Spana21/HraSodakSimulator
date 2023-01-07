#pragma once

#include "Player.h"
#include "Enemy.h"
#include"Tank.h"
#include "Start.h"
#include "Rocket.h"

using namespace sf;

class Game
{
private:
	RenderWindow* window;
	
	//HitBox tanku
	RectangleShape hitbox;
	
	//TEXT
	Font font;
	Font font2;
	std::vector<Text> staticPlayerText;
	Text followPlayerText;
	Text scoore;
	Text level;
	Text konec;
	Text esc;
	Text gratuluji;

	//StartScreen
	Start *start;
	Texture wasd;
	Texture space;
	
	//HRAC
	Player *player;
	Texture playerTexture;
	Texture playerKlek;
	Texture bulletTexture;
	Texture playerLeft;
	Texture rakev;

	//Enemy
	Texture enemyTexture;
	Texture enemyNuz;
	std::vector<Enemy*>enemies;


	//Tank
	Texture tankTexture;
	std::vector<Tank*> tanky;

	//Rocket
	Texture raketaTexture;
	std::vector<Rocket*> rakety;


	//Background
	Texture back;
	Sprite background;
	
	//You died textura
	Texture ds;
	Sprite youDie;

	//Sound efekty
	SoundBuffer buffer;
	SoundBuffer soundtrack;
	SoundBuffer startBuffer;
	Sound startSound;
	Sound sound;
	Sound ripAndTear;

	bool PlayerDeath;
	bool startGame;
	bool winGame;
	
	float rychlostEnemy;
	float rychlostTanku;
	float rychlostRocket;
	
	int SpawnerTime;
	int SpawnerTimeMax;
	int SpawnerTimeTank;
	int SpawnerTimeMaxTank;
	int SpawnerTimeRocket;
	int SpawnerTimeMaxRocket;
	
	int kills;
	int lv;
	
	int EnemyDamage;
	int TankDamage;
	int rocketDamage;
public:
	Game(RenderWindow* window);
	virtual ~Game();
	
	//PRISTUP
	inline RenderWindow& getWindonw() {
		return *this->window;
	}

	inline const String getKillsAsString()const {
		return "Scoore: " + std::to_string(this->kills);
	}

	inline const String getLevelAsString()const {
		return "Uroven: " + std::to_string(this->lv);
	}
	//SETTERS

	//FUNKCE
	
	//inicializace
	void initUO();
	void iniKonceHry();
	void iniSpawnery();
	void iniSound();
	
	//Start a win game
	void StartScreen();
	void WinGameEnd();
	
	//Textury
	void PlayerTexture();
	void EnemyTankRocketTexture();
	void FontBackground();
	
	//Update
	void UIUpdate();
	void SpawnUpdate();
	void BulletsUpdate();
	void EnemyUpdate();
	void TankyUpdate();
	void RocketUpdate();
	void LevelUpdate();
	
	void Update();
	
	//Draw
	void UIDraw();
	void GameDraw();
	void DeathDraw();
	void WinDraw();
	
	void Draw();
};

