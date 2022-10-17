#pragma once
#include "Weapon.h"

class MachineGun : public Weapon
{
public:
	MachineGun(Player* player);
	virtual ~MachineGun();

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void Fire();
};