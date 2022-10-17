#pragma once
#include "SpriteObj.h"

class Player;

class Pickup : public SpriteObj
{
public:
	enum class Types
	{
		None = -1,
		Health,
		Exp,
		Count,
	};

	static const int TotalTypes;

protected:
	Types type;
	int value;
	Player* player;

public:
	Pickup();
	virtual ~Pickup();

	void SetPlayer(Player* p);
	void SetType(Types t);
	void SetValue(int v);

	Types GetType() { return type; }
	int GetValue() { return value; }

	virtual void Update(float dt) override;

};