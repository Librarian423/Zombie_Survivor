#pragma once
#include "SpriteObj.h"

class Player;
class Bullet;
class VertexArrayObj;

class Zombie : public SpriteObj
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};

	static const int TotalTypes;

protected:
	Types type;

	Vector2f dir;
	float speed;

	float maxHp;
	float health;
	float damage;

	Player* player;

	VertexArrayObj* background;
public:
	Zombie();
	~Zombie();

	void SetBackground(VertexArrayObj* bk);

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	void Init(Player* player);

	virtual void Reset() override;

	void SetType(Types t);
	Types GetType()const;

	Vector2f GetDir();

	void OnHitBullet(Bullet* bullet);

	void SetHealth(float delta) { health = health + delta; }
	float GetDamage() const { return damage; }
};