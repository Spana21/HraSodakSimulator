#include "Game.h"

Game::Game(RenderWindow* window)
{
	srand(time(0));
	this->window = window;
	this->window->setFramerateLimit(60);  //FPSka
	
	this->kills = 0;
	this->lv = 1;
	
	//Ini rychlosti
	this->rychlostEnemy = -10;
	this->rychlostTanku = 15;
	this->rychlostRocket = 10;
	
	//Ini Damage
	this->EnemyDamage = 1;
	this->TankDamage = 1;
	this->rocketDamage = 2;

	hitbox.setFillColor(Color::Transparent);
	hitbox.setSize(Vector2f(280, 100));
	
	
	//Spawnery
	this->iniSpawnery();

	//Font a pozadi
	this->FontBackground();

	
	//Player
	this->PlayerTexture();
	
	
	//Enemy a Tanl
	this->EnemyTankRocketTexture();
	
	//Win Game
	this->WinGameEnd();
	
	//Start
	this->StartScreen();

	//Konec
	this->iniKonceHry();

	//SOUND
	this->iniSound();
	
	//TEXT
	this->initUO();
}

Game::~Game()
{
	delete player;
	for (auto* i : this->enemies)
	{
		delete i;
	}

	for (auto* i : this->tanky)
	{
		delete i;
	}

	for (auto* i : this->rakety)
	{
		delete i;
	}
}



void Game::initUO()
{

	//Zivoty
	this->followPlayerText.setFont(this->font);
	this->followPlayerText.setCharacterSize(20);
	
	//Scoore
	this->scoore.setFont(this->font);
	this->scoore.setCharacterSize(30);
	this->scoore.setPosition(window->getSize().x - 250.f, 50.f);

	//Level
	this->level.setFont(this->font);
	this->level.setCharacterSize(30);
	this->level.setPosition(window->getSize().x - 250.f, 100.f);

}

void Game::iniKonceHry()
{
	//Konec hry
	this->konec.setFont(this->font2);
	this->konec.setCharacterSize(30);
	this->konec.setString("Pro ukonceni hry stiskni: ");
	this->konec.setPosition(640.f, 700.f);

	//Button esc
	this->esc.setFont(this->font2);
	this->esc.setCharacterSize(30);
	this->esc.setFillColor(Color::Red);
	this->esc.setString("ESC");
	this->esc.setPosition(640.f + konec.getGlobalBounds().width, 700.f);
}

void Game::iniSpawnery()
{
	//Tank
	this->SpawnerTimeTank = 0;
	this->SpawnerTimeMaxTank = 500;
	
	//Enemy
	this->SpawnerTimeMax = rand() % 200 + 180; //nahodna hodnota 
	this->SpawnerTime = 0;
	
	//Rocket
	this->SpawnerTimeRocket = 0;
	this->SpawnerTimeMaxRocket = 120;
}

void Game::iniSound()
{
	//Sound kdyz budu zasazen texturou
	this->buffer.loadFromFile("Sound/die.wav");
	this->sound.setBuffer(this->buffer);
	this->sound.setVolume(30.f);

	//Soundtrack hry
	this->soundtrack.loadFromFile("Sound/soundtrack.wav");   
	this->ripAndTear.setBuffer(this->soundtrack);      
	this->ripAndTear.setVolume(15.f);
	this->ripAndTear.setLoop(true); //at to hraje v loopu 

	//Soundtrack uvodni obrazovky
	this->startBuffer.loadFromFile("Sound/start.wav");  
	this->startSound.setBuffer(this->startBuffer);
	this->startSound.setVolume(20.f);
	this->startSound.setLoop(true);
	this->startSound.play();

}

void Game::StartScreen()
{

	this->startGame = false;
	this->PlayerDeath = false;
	this->winGame = false;
	
	//Pixel font
	this->font2.loadFromFile("Font/Pix.ttf");
	
	//Klavesnice
	this->wasd.loadFromFile("Texture/wasd.png");
	this->space.loadFromFile("Texture/space.png");
	
	start = new Start(&font2,&this->wasd,&this->space);              //Text, a klavesnice wasd a space, ktere budou v uvodu

}

void Game::WinGameEnd()
{
	this->gratuluji.setFont(this->font2);
	this->gratuluji.setString("Zachranil jsi univerzitu. Rektorka je na tebe hrda, \na tak ziskavas medaili za hrdinstvi.");
	this->gratuluji.setCharacterSize(30);
	this->gratuluji.setPosition(540.f, 500.f);
}

void Game::PlayerTexture()
{
	//hrac
	this->playerTexture.loadFromFile("Texture/boy.png"); //miri doprava 
	this->playerLeft.loadFromFile("Texture/boy2.png");  //miri doleva
	
	//Kulky
	this->bulletTexture.loadFromFile("Texture/kulka1.png");
	
	//Rakev → kdyz zemru
	this->rakev.loadFromFile("Texture/rip.png");
	
	player = new Player(&playerTexture, &bulletTexture, &playerLeft, &rakev); //textury posilam do class player
	
}

void Game::EnemyTankRocketTexture()
{
	//Enemy
	this->enemyTexture.loadFromFile("Texture/enemy.png", IntRect(382, 123, 163, 439));
	this->enemyNuz.loadFromFile("Texture/enemy.png", IntRect(246, 119, 146, 466)); //zvlaz nuz abych nemusel delat hitbox ctverec
	
	//Tank
	this->tankTexture.loadFromFile("Texture/tank.png", IntRect(69, 83, 432, 219));

	//Raketa
	this->raketaTexture.loadFromFile("Texture/rocket.png");
}

void Game::FontBackground()
{
	//Nastaveni fontu
	this->font.loadFromFile("Font/MW.ttf");   
	
	//Background
	this->back.loadFromFile("Texture/background.png");  
	this->background.setTexture(back);

	//Kdyz umru
	this->ds.loadFromFile("Texture/d.png");  //You die textura
	this->ds.setSmooth(true);               //Vyhlazeni
	this->youDie.setTexture(ds);
	this->youDie.setPosition(-100.f, 420.f);
	this->youDie.setScale(3.5f, 3.f);
	
}

void Game::UIUpdate()
{
	//Nasledovat hrace
	this->followPlayerText.setPosition(this->player->getPosition().x + 25.f, this->player->getPosition().y - 50.f);
	followPlayerText.setString(player->getHpAsString());

	//Menit scoore
	scoore.setString(this->getKillsAsString());

	//Menit level
	level.setString(this->getLevelAsString());

}

void Game::SpawnUpdate()
{
	//Terorista
	if (this->SpawnerTime < this->SpawnerTimeMax)
		this->SpawnerTime++;
	if (this->SpawnerTime >= this->SpawnerTimeMax) {
		this->enemies.push_back(new Enemy(&this->enemyTexture, &this->enemyNuz));
		this->SpawnerTime = 0;
	}

	//Tank
	if (this->SpawnerTimeTank < this->SpawnerTimeMaxTank)
	{
		this->SpawnerTimeTank++;
	}
	if (this->SpawnerTimeTank >= this->SpawnerTimeMaxTank) {
		this->tanky.push_back(new Tank(&this->tankTexture));
		this->SpawnerTimeTank = 0;
	}

	//Rocket
	if (this->SpawnerTimeRocket < this->SpawnerTimeMaxRocket)
	{
		this->SpawnerTimeRocket++;
	}
	if (this->SpawnerTimeRocket >= this->SpawnerTimeMaxRocket) {
		this->rakety.push_back(new Rocket(&this->raketaTexture, player->getPosition().x));
		this->SpawnerTimeRocket = 0;
	}
}

void Game::BulletsUpdate()
{
	for (size_t i = 0; i < this->player->getBullets().size(); i++)
	{
		this->player->getBullets()[i].Update();

		// Kulka za obrazovkou
		if (this->player->getBullets()[i].getPosition().x > this->window->getSize().x) {
			this->player->getBullets().erase(this->player->getBullets().begin() + i);
			break;
		}
	}
	unsigned counter = 0;   //ktery z enemy se spawnul
	for (auto* enemy : this->enemies)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->player->getBullets().size() && enemy_deleted == false; k++)
		{
			//Stret kulky a enemy
			if (this->player->getBullets()[k].getGlobalBounds().intersects(enemy->getGlobalBounds()))
			{
				delete this->enemies.at(counter);
				this->enemies.erase(this->enemies.begin() + counter);

				this->player->getBullets().erase(this->player->getBullets().begin() + k);
				kills++;
				enemy_deleted = true;
			}
		}
		counter++;
	}


}

void Game::EnemyUpdate()
{

	unsigned counter = 0;

	for (auto* enemy : this->enemies)
	{
		//Rychlost
		enemy->Update(this->rychlostEnemy);

		// kdyz enenem zajede mimo obrazovku tak se smaze
		if (enemy->getPosition().x < 0 - enemy->getGlobalBounds().width) {
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			break;
		}
		//kdyz se stretne s hracem = -hp
		else if (this->player->getGlobalBounds().intersects(enemy->getGlobalBounds())) {
			this->player->takeDamage(this->EnemyDamage); // kolik dmg bude davat
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			sound.play();
			return;
		}
		counter++;
	}

}

void Game::TankyUpdate()
{
	unsigned counter = 0;

	for (auto* tank : this->tanky)
	{
		tank->Update(this->rychlostTanku);

		//Nastaveni hitboxu.. textura byla velka takze to davalo dmg i kdyz jsem se "nedotkl" tanku
		this->hitbox.setPosition(tank->getPosition().x + 23.f, tank->getPosition().y + 55.f);

		// kdyz tank zajede mimo obrazovku tak se smaze
		if (tank->getPosition().x > 1920) {
			delete this->tanky.at(counter);
			this->tanky.erase(this->tanky.begin() + counter);
			break;
		}

		//kdyz se stretne s hracem = -hp
		else if (this->player->getGlobalBounds().intersects(hitbox.getGlobalBounds())) {

			// kolik dmg bude davat
			this->player->takeDamage(this->TankDamage);
			delete this->tanky.at(counter);
			tanky.erase(tanky.begin() + counter);
			this->hitbox.setPosition(0.f, 0.f);
			sound.play();
			return;
		}
		counter++;
	}
}

void Game::RocketUpdate()
{
	unsigned counter = 0;

	for (auto* rocket : this->rakety)
	
	{
		rocket->Update(this->rychlostRocket);
		if (rocket->getPosition().y + rocket->getGlobalBounds().height > 1080) {
			delete this->rakety.at(counter);
			this->rakety.erase(this->rakety.begin() + counter);
			break;
		}
		else if (this->player->getGlobalBounds().intersects(rocket->getGlobalBounds())) {
			this->player->takeDamage(this->rocketDamage);
			delete this->rakety.at(counter);
			rakety.erase(rakety.begin() + counter);
			sound.play();
			return;
		}
	}
}

void Game::LevelUpdate()
{
	// kdy bude level up
	switch (kills) {
		case 10:
			lv = 2;
			break;
		case 20:
			lv = 3;
			break;
		case 30:
			lv = 4;
			break;
		case 40:
			lv = 5;
			break;
		case 50:
			lv = 6;
			break;
		case 60:
			lv = 7;
			break;
		case 70:
			lv = 8;
			break;
		case 80:
			lv = 9;
			break;
		case 90:
			lv = 10;
			break;
		default:
			break;
	}

	//co se bude menit v danem levelu
	switch (lv)
	{
		case 2:
			this->SpawnerTimeMax = rand() % 180 + 150; ;
			break;
		case 3:
			this->rychlostEnemy = -15;
			this->rychlostTanku = 18;
			this->SpawnerTimeMax = rand() % 150 + 130;;
			this->SpawnerTimeMaxRocket = 100;
			break;
		case 4:
			this->SpawnerTimeMax = rand() % 130 + 110;;
			break;
		case 5:
			this->rychlostEnemy = -22;
			this->rychlostTanku = 20;
			this->SpawnerTimeMax = rand() % 110 + 90;
			this->EnemyDamage = 2;
			this->TankDamage = 2;
			this->SpawnerTimeMaxRocket = 95;
			break;
		case 6:
			this->SpawnerTimeMax = rand() % 90 + 85;
			break;
		case 7:
			this->rychlostEnemy = -27;
			this->rychlostTanku = 25;
			this->SpawnerTimeMax = rand() % 85 + 70;
			this->SpawnerTimeMaxRocket = 80;
			break;
		case 8:
			this->rychlostTanku = 30;
			break;
		case 9:
			this->rychlostEnemy = -29;
			this->SpawnerTimeMax = rand() % 70 + 65;
			this->SpawnerTimeMaxRocket = 85;
			break;
	default:
		break;
	}
}


void Game::Update()
{
	//uvod 
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		this->startGame = true;
		this->ripAndTear.play();
		this->startSound.stop();
	}
	
	//samotna hra
	if (this->startGame == true && this->PlayerDeath == false && winGame == false) {
		//PLAYER
		player->Update(this->window->getSize().x, this->window->getSize().y, this->PlayerDeath);

		//SPAWNER
		this->SpawnUpdate();

		//BULLETS
		this->BulletsUpdate();

		//ENEMIES
		this->EnemyUpdate();

		//Tanky
		this->TankyUpdate();

		this->RocketUpdate();

		//UPDATE UI
		this->UIUpdate();

		//Lv Update 
		this->LevelUpdate();

		
		}
	
	//Kdy umru 
	if (player->getHp() <= 0) {
		PlayerDeath = true;
		player->Update(this->window->getSize().x, this->window->getSize().y, this->PlayerDeath);
		this->ripAndTear.stop();
	}

	//Kdyz vyhraju
	if (this->lv == 10) {
		this->winGame = true;
		this->ripAndTear.stop();
	}

}



void Game::UIDraw()
{
	//UI draw
	window->draw(this->followPlayerText);
	window->draw(this->scoore);
	window->draw(this->level);
}

void Game::GameDraw()
{
	//UI
	this->UIDraw();

	//Hitbow
	window->draw(this->hitbox);

	//Player
	player->Draw(*this->window, PlayerDeath);
	
	//Enemy,Tanky a rakety

	for (auto* enemy : this->enemies)
	{
		enemy->Draw(*this->window);
	}
	for (auto* tank : this->tanky)
	{
		tank->Draw(*this->window);
	}
	for (auto* rocket : this->rakety)
	{
		rocket->Draw(*this->window);
	}
}

void Game::DeathDraw()
{
	window->draw(this->esc);
	window->draw(this->konec);
	window->draw(this->youDie);
	
	//Vykresli se hrob
	player->Draw(*this->window, PlayerDeath);
}

void Game::WinDraw()
{
	window->draw(this->gratuluji);
	window->draw(this->esc);
	window->draw(this->konec);
}


void Game::Draw()
{
	
	window->clear();
	
	window->draw(this->background);
	
	// vykreslovani uvodni obrazovky 
	if (this->startGame == false) {
		this->start->Draw(*this->window);
	}
	
	// vykreslovani hry
	if (startGame == true && PlayerDeath==false) {
		this->GameDraw();
	}
	
	// Vzkreslovani smrtici obrazovky 
	if (this->PlayerDeath == true) {
		this->DeathDraw();
		
	}
	
	//Vzkreslovani vyherni obrazovky 
	if (this->winGame == true) {
		this->WinDraw();
	}
	window->display();

}
