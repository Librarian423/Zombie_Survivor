#pragma once
#include "Player.h"
#include "Object.h"
#include "../Framework/ObjectPool.h"

class Bullet;
class VertexArrayObj;
class Scene;

enum class WeaponTypes
{
	PISTOL,
	SM,
	SWORD,
};

class Weapon : public SpriteObj
{
protected:
	WeaponTypes type;
	
	Player* player;
	Scene* scene;

	ObjectPool<Bullet>* bulletPool;
	VertexArrayObj* background;

	Vector2f look;

	float fireTimer;

	float intervalPistol;
	float intervalSM;
	float intervalSword;
public:
	Weapon();
	virtual ~Weapon();

	void Init(Player* player);
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void Fire();
	void SetWeaponType(WeaponTypes type);
	
};

