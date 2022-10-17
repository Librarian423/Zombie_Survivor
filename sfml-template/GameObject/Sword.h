#pragma once
#include "Weapon.h"

class Sword : public Weapon
{
public:
	Sword(Player* player);
	virtual ~Sword();

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void Fire();
};