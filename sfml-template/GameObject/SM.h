#pragma once
#include "../Framework/ObjectPool.h"
#include "SpriteObj.h"

class Bullet;
class VertexArrayObj;
class Scene;
class Player;

class SM : public SpriteObj
{
protected:
	Player* player;
	Scene* scene;

	ObjectPool<Bullet>* bulletPool;
	VertexArrayObj* background;

	Vector2f look;

	float fireTimer;
	float intervalSM;
	
public:
	SM();
	virtual ~SM();

	void Init(Player* player);
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void Fire();
};

