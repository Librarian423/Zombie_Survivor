#pragma once
#include "SpriteObj.h"

class Player;
class Bullet;
class VertexArrayObj;
class Slash;
class Scene;

class Zombie : public SpriteObj
{
public:
	enum class Types
	{
		Crawler,
		Chaser,
		Bloater,
		Boss,
		King,
	};

protected:
	Types type;
	
	Vector2f dir;
	float speed;

	float maxHp;
	float health;
	float damage;

	Player* player;

	VertexArrayObj* background;

	Scene* scene;
public:
	Zombie();
	~Zombie();

	void SetBackground(VertexArrayObj* bk);

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	void Init(Player* player);

	virtual void Reset() override;

	void SetZombieType(Types t, int wave);
	Types GetZombieType() const;

	Vector2f GetDir();
	void OnHitBullet(Bullet* bullet);

	void SetHealth(float delta) { health = health + delta; }
	float GetDamage() const { return damage; }
	void SetScene(Scene* scene) { this->scene = scene; }
};