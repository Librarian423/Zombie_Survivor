#pragma once
#include "SpriteObj.h"
#include "../Framework/ObjectPool.h"
#include "PlayerStatTable.h"

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
	COUNT
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

	VertexArrayObj* background;
	ObjectPool<Bullet>* bulletPool;
	ObjectPool<Bullet>* SlashPool;

	Scene* scene;
	UIMgr* uiMgr;

	FireModes fireMode;

	// stats
	PlayerStatTable pst;
	int level;
	float requireExp;
	float maxHealth;
	float health;
	float damage;
	float exp;

public:
	Player();
	virtual ~Player();

	void SetBulletPool(ObjectPool<Bullet>* ptr);
	void SetSlashPool(ObjectPool<Bullet>* ptr);
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
	ObjectPool<Bullet>* GetSlashPool();
	Vector2f GetPosition();
	Vector2f GetLook();
	FireModes GetFireMode();

	void SetHealth(float delta) { health += delta; }
	float GetDamage() const { return damage; }
	void SetExp(float delta) { exp += delta; }
	void SetStatData(int idx)
	{
		requireExp = pst.LoadReqExp(idx);
		maxHealth = pst.LoadHealth(idx);
		health = pst.LoadHealth(idx);
		damage = pst.LoadDamage(idx);
	}
	float GetRequireExp() {	return requireExp; }
	float GetExp() { return exp; }
	float GetMaxHealth() { return maxHealth; }
	float GetHealth() { return health; }
};