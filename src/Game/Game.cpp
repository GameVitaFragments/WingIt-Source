#include "Game.h"
#include <iostream>
#include <vector>

class  HealthUI
{
public:
	HealthUI(Renderer* rend, const char* path, const vec::Vec2 pos) :
		sp(rend, path, false), text(rend, "5", {200,200,200,255})
	{
		sp.setPos({ pos.x,pos.y });
		sp.setSize({sp.getWidth()/10,sp.getHeight()/10});
		
		
		text.CacheNumbers(rend, { 200,200,200,255 });
		text.RenderNumber(5);
		text.setPos({ pos.x + sp.getWidth() + 10,pos.y });

		text.setSize({ text.getWidth() + 20,text.getHeight() + 20 });
	}

	void SetText(Renderer* rend, int num) {
		text.RenderNumber(num);
	}

private:
	Sprite sp;
	StaticText text;
};


class  PointsUI
{
public:
	PointsUI(Renderer* rend, const char* path, const vec::Vec2 pos) :
		sp(rend, path, false)
	{
		sp.setPos({ pos.x - sp.getWidth() - 18,pos.y - sp.getHeight() / 4});
		sp.setSize({ sp.getWidth()/2,sp.getHeight()/2});

		for (int i = 0; i < 4; i++)
		{
			StaticText* text = new StaticText(rend, "0", {0,0,0,255});
			text->CacheNumbers(rend, {0, 0, 0, 255});
			text->RenderNumber(0);
			text->setPos({ pos.x - sp.getWidth() * 2 + 30*(i+1),pos.y - sp.getHeight() / 2 });
			text->setSize({ text->getWidth() + 20,text->getHeight() + 20 });
			textVec.push_back(text);
		}
	}

	void SetText(Renderer* rend, int num) {
		textVec[0]->RenderNumber(num % 10000 / 1000);
		textVec[1]->RenderNumber(num % 1000 / 100);
		textVec[2]->RenderNumber(num % 100 / 10);
		textVec[3]->RenderNumber(num % 10 / 1);
	}

private:
	Sprite sp;
	std::vector<StaticText*> textVec;
};

class RougeRock :
	public Sprite
{
private:
	vec::Vec2f _velocity;
	vec::Vec2 _position;
	vec::Vec2f _positionF;
	float _gravity;
	int wallWidth = 75;
public:
	RougeRock(Renderer* rend, const char* path, bool _collisionDet, float gravity = 0) : Sprite(rend, path, _collisionDet)
	{
		_gravity = gravity;
		_velocity = { 0,0 };
		_position = { getPosX(), getPosY() };
		_positionF = { 1, 1 };
	}

	virtual void update(SDL_Renderer* rend)
	{
		Sprite::update(rend);

		//Smooth Acceleration
		_velocity.y -= _gravity;

		//Smooth Velocity
		_position.x -= (int)_velocity.x;
		_positionF.x += _velocity.x - (int)_velocity.x;
		if (_positionF.x >= 1) {
			_position.x -= (int)_positionF.x;
			_positionF.x -= (int)_positionF.x;
		}
		_position.y -= (int)_velocity.y;
		_positionF.y += _velocity.y - (int)_velocity.y;
		if (_positionF.y >= 1) {
			_position.y -= (int)_positionF.y;
			_positionF.y -= (int)_positionF.y;
		}
		setPos({ _position.x, _position.y });
		reSpawnTop();
		getCol()->setBoundBox();
	}

	void Spawn(vec::Vec2 pos, vec::Vec2 size) {
		_position = pos;
		this->setSize({ size.x, size.y });
	}
	void SpawnTop() {
		int rockType = rand() % 2;
		if (rockType) {
			int SpAreaX = (rand() % (wallWidth - (Global::ScreenWidth - rect.w - wallWidth)) + wallWidth);
			Spawn({ SpAreaX ,-rect.y }, { rect.w,rect.h });
			_velocity.y = 10;
			//printf("%d \n", SpAreaX);
		}
		else {
			int spawnPos = rand() % 2;
			if (spawnPos) {
				int SpAreaX = (rand() % (wallWidth - (Global::ScreenWidth / 2 - rect.w - wallWidth)) + wallWidth);
				Spawn({ SpAreaX ,-rect.y }, { rect.w,rect.h });
				_velocity.x = -3;
				_velocity.y = 10;
				//printf("%d \n", SpAreaX);
			}
			else {
				int SpAreaX = (rand() % (wallWidth - (Global::ScreenWidth / 2 - rect.w - wallWidth)) + Global::ScreenWidth / 2);
				Spawn({ SpAreaX ,-rect.y }, { rect.w,rect.h });
				_velocity.x = 3;
				_velocity.y = 10;
				//printf("%d \n", SpAreaX);
			}
		}
	}

	void reSpawnTop() {
		if (!CheckOutOfBounds())
			return;
		//int SpAreaX = (rand() % (wallWidth - (Global::ScreenWidth - rect.w - wallWidth)) + wallWidth);
		SpawnTop();
	}

	virtual void isCollided(Player* _player) {
		_player->Hearts -= 1;
		SpawnTop();
	}

	bool CheckOutOfBounds()
	{
		if (rect.y > Global::ScreenHeight) {
			return true;
		}
		return false;
	}

	inline void setWallWidth(int _width) {
		wallWidth = _width;
	}
};

class Wall : public Sprite {
private:
	int _velocity;
public:
	Wall(Renderer* rend, const char* path, bool _collisionDet, float velocity = 0) : Sprite(rend, path, _collisionDet)
	{
		_velocity = velocity;
	}
	virtual void update(SDL_Renderer* rend)
	{
		Sprite::update(rend);
		setPos({ getPosX(), getPosY() + _velocity});
		reSpawnTop();
		getCol()->setBoundBox();
	}

	void Spawn(vec::Vec2 pos, vec::Vec2 size) {
		this->setPos({ pos.x, pos.y });
		this->setSize({ size.x, size.y });
	}

	void reSpawnTop() {
		if (!CheckOutOfBounds())
			return;
		Spawn({ rect.x ,-rect.y }, { rect.w,rect.h });
	}

	bool CheckOutOfBounds()
	{
		if (rect.y > Global::ScreenHeight) {
			return true;
		}
		return false;
	}
};

Game::Game(unsigned int w, unsigned int h, const char* t, SDL_Window* win, Renderer* ren, EventHandler* even) {
	_width = w;
	_height = h;
	_title = t;
	_render_flags = SDL_RENDERER_ACCELERATED;
	_isGameClosed = false;
	_fps = 60;
	Global::ScreenHeight = _height;
	Global::ScreenWidth = _width;
	//error::checkReturnCode(SDL_Init(SDL_INIT_EVERYTHING));

	_window = win;
	_renderer = ren;
	_eventhandler = even;

	/*_window = (SDL_Window*)error::checkReturnPointer(SDL_CreateWindow(
		_title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height, 0));

	_renderer = new Renderer(_window, _render_flags);
	_eventhandler = new EventHandler();*/

	//Audio::initMixer();
}

int Game::getTicks() {
	return (SDL_GetTicks64() - _lastFrameTick);
}

void Game::_init() {
}

void Game::update() {
	double points =0;

	Sprite wallpaper(_renderer, "src/Assets/sky.png", true);
	wallpaper.setPos({ 0, 0 });
	wallpaper.setSize({ (int)_width, (int)_height });

	RougeRock* rocks[3];
	for (int i = 0; i < 3; i++) {
		rocks[i] = new RougeRock(_renderer, "src/assets/rock2.png", true, ((float)i + 1) / 10);

	}
	rocks[0]->setPos({ -1000,-200 }); rocks[0]->setSize({75,75 });
	rocks[1]->setPos({ -1000,-600 }); rocks[1]->setSize({75,75 });
	rocks[2]->setPos({ -1000,-100 }); rocks[2]->setSize({75,75});

	Wall* leftwalls[3];
	for (int i = 0; i < 3; i++) {
		leftwalls[i] = new Wall(_renderer, "src/assets/wall.png", true, 10);
		leftwalls[i]->setPos({0, -i * Global::ScreenHeight});
		leftwalls[i]->setSize({Global::wallWidth, Global::ScreenHeight});
	}

	Wall* rightwalls[3];
	for (int i = 0; i < 3; i++) {
		rightwalls[i] = new Wall(_renderer, "src/assets/wall-rev.png", true, 10);
		rightwalls[i]->setPos({Global::ScreenWidth - Global::wallWidth, -i * Global::ScreenHeight});
		rightwalls[i]->setSize({Global::wallWidth, Global::ScreenHeight});
	}

	Player player(_renderer, "src/Assets/bird1.png", true, _eventhandler, 640, 50, 0.1, 3.0f);

	int currentHearts = player.Hearts;

	//UI Area
	Sprite playerCoolDownTimer(_renderer, "src/Assets/cooldowntimer.png", false);
	playerCoolDownTimer.setPos({ 10, 10 });
	int playerCoolDownTimerMaxSize = 100;

	HealthUI hui(_renderer, "src/Assets/heart.png", {Global::ScreenWidth-120,25});
	PointsUI pui(_renderer, "src/Assets/Arrow.png", {Global::ScreenWidth/2,Global::ScreenHeight-50});
	//End UI Area
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double dt = 0;

	//Audio menuMusic("src/Assets/Audio/menumusic.mp3", true);
	Audio gameMusic("src/Assets/Audio/gamemusic.mp3", true);
	Audio hurtSound("src/Assets/Audio/ow.wav", false);
	Audio lowHealthSound("src/Assets/Audio/owsong.wav", false);
	Audio flySound("src/Assets/Audio/up.wav", false);
	Audio deathSound("src/Assets/Audio/away.wav", false);
	std::vector<Audio> sounds = { gameMusic, hurtSound, lowHealthSound, flySound,deathSound };

	while (!_isGameClosed) {
		//Game Music
		gameMusic.playMusic();
		gameMusic.setVolume(200);

		SDL_Event event;
		_eventhandler->setInput(&event);
		_isGameClosed = _eventhandler->isQuit();

		if (player.Hearts < 0) {
			deathSound.playSound();
			deathSound.setVolume(200);
			continue;
		}

		_renderer->ClearScreen();
		_renderer->update();
		player.checkCollision(_renderer);
		hui.SetText(_renderer,player.Hearts);
		pui.SetText(_renderer, points);

		float fraction = (SDL_GetTicks() - player.timeSinceShot) / (float)player.coolDown;
		if (fraction < 1) {
			playerCoolDownTimer.setWidth(playerCoolDownTimerMaxSize * fraction);
			//std::cout << (SDL_GetTicks() - player.timeSinceShot) / (float)player.coolDown << std::endl;
		}
		else {
			playerCoolDownTimer.setWidth(playerCoolDownTimerMaxSize);
		}
		playerCoolDownTimer.setHeight(50);

		if (player.Hearts != currentHearts) {
			hurtSound.playSound();
			hurtSound.setVolume(200);
			currentHearts = player.Hearts;
		}
		if (currentHearts == 0) {
			lowHealthSound.playSound();
			lowHealthSound.setVolume(200);
		}
		if (_eventhandler->getMSInput('1') && !player.underCooldown) {
			flySound.playSound();
			flySound.setVolume(200);
		}
		

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		dt = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		float currentFPS = 1000.0 / dt;
		player.getDt(dt);
		points += dt / 1000;
		
		SDL_Delay(1000 / _fps);
		_lastFrameTick = SDL_GetTicks64();
	}

	for (int i = 0; i < 3; i++) {
		delete leftwalls[i];
		delete rightwalls[i];
	}

	for (auto i : sounds) {
		i.quitMixer();
	}
}

Game::~Game() {
	//delete _eventhandler;
	//delete _renderer;
	//SDL_DestroyWindow(_window);
	//SDL_Quit();
}
