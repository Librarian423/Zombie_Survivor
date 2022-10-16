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
	Manual,
	Auto,
	Semi,
};

class Player : public SpriteObj
{
protected:
	Vector2f look;
	Vector2f direction; //이동방향 , 단위 벡터
	float speed;
	float accelation;
	float deaccelation;

	Vector2f velocity;

	Pistol* weapon;

	VertexArrayObj* background;

	ObjectPool<Bullet>* bulletPool;

	Scene* scene;
	UIMgr* uiMgr;

	//int magazineSize;
	//int ammo;
	//int currentAmmo;

	//bool isReloading;
	//float reloadTIme;
	//float reloadTimer;
	float fireTimer;

	float intervalManual;
	float intervalSemiauto;
	float intervalAuto;

	bool isFire;
	int semiTotal;
	int semiCount;
	bool isSemiFiring;

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
	
	void Fire();
	//void Reload();

	void ResetVelocity();
	//void ResetAmo();
	void SetShootType();
	
	void OnPickupItem(Pickup* item);
	void OnHitZombie(Zombie* zombie);

	VertexArrayObj* GetPlayerBackground();
	ObjectPool<Bullet>* GetBulletPool();
	Vector2f GetPosition();
	Vector2f GetLook();
};

