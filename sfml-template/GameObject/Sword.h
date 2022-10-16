#pragma once
#include "../Framework/ObjectPool.h"
#include "SpriteObj.h"

class Bullet;
class VertexArrayObj;
class Scene;
class Player;

class Sword : public SpriteObj
{
protected:
	Player* player;
	Scene* scene;
	//Bullet* bullet;
	//ObjectPool<Bullet>* bulletPool;
	VertexArrayObj* background;

	Vector2f look;

	float fireTimer;
	float intervalSword;

public:
	Sword();
	virtual ~Sword();

	void Init(Player* player);
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void Fire();
};
