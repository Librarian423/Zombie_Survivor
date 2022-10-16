#pragma once
#include "Scene.h"
#include <list>
#include "../Framework/ObjectPool.h"

class Player;
class VertexArrayObj;
class Zombie;
class Bullet;
class SpriteObj;
class Pickup;
class Pistol;
class SM;
class Sword;
class Slash;

class SceneDev1 : public Scene
{
protected:
	Player* player;
	Pistol* pistol;
	SM* sm;
	Sword* sword;
	
	VertexArrayObj* background;
	list<Zombie*> zombies;

	ObjectPool<Bullet> bullets;

public:
	SceneDev1();
	virtual ~SceneDev1();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void CreateBackground(int width, int height, float quadWidth, float quadHeight);
	void CreateZombies(int count);
	
	list<Zombie*>* GetZombieList() { return &zombies; }
};

