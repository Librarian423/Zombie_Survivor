#pragma once
#include "../Framework/ObjectPool.h"
#include "SpriteObj.h"

class Bullet;
class Player;
class VertexArrayObj;

class Weapon : public SpriteObj
{
protected:
	Player* player;

	ObjectPool<Bullet>* bulletPool;
	VertexArrayObj* background;

	Vector2f look;

	float fireTimer;
	float intervalWeapon;

public:
	Weapon(float fireTimer, float interval);
	virtual ~Weapon();
};