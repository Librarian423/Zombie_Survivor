#pragma once
#include "SpriteObj.h"
#include "../Framework/ObjectPool.h"

class Bullet;
class Pickup;
class VertexArrayObj;
class Zombie;
class Scene;
class UIMgr;
class Pistol;


enum class FireModes
{
	PISTOL,
	SUBMACHINE,
	SWORD,
};

class Player : public SpriteObj
{
//public:
//	enum class FireModes
//	{
//		PISTOL,
//		SUBMACHINE,
//		SWORD,
//	};
protected:
	Vector2f look;
	Vector2f direction; //이동방향 , 단위 벡터
	float speed;
	float accelation;
	float deaccelation;
	Vector2f velocity;

	VertexArrayObj* background;
	ObjectPool<Bullet>* bulletPool;
	//Bullet* bullet;

	Scene* scene;
	UIMgr* uiMgr;

	FireModes fireMode;

public:
	Player();
	virtual ~Player();

	void SetBulletPool(ObjectPool<Bullet>* ptr);
	void SetBackground(VertexArrayObj* bk);
	
	virtual void Init() override;
	
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void ResetVelocity();
	void SetShootType();
	
	void OnPickupItem(Pickup* item);
	void OnHitZombie(Zombie* zombie);

	VertexArrayObj* GetPlayerBackground();
	ObjectPool<Bullet>* GetBulletPool();
	Vector2f GetPosition();
	Vector2f GetLook();
	FireModes GetFireMode();
};

