#pragma once
#include "Player.h"
#include "Object.h"
#include "../Framework/ObjectPool.h"

class SM : public SpriteObj
{
protected:
	//WeaponTypes type;

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
	//void SetWeaponType(WeaponTypes type);
};

