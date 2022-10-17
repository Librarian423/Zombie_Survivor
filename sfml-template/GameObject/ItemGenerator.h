#pragma once
#include "../3rd/Singleton.h"
#include "Object.h"
#include <list>

class Pickup;

class ItemGenerator :public Singleton<ItemGenerator>
{
protected:
	list<Pickup*>itemList;
	Vector2f pos;
	
public:
	ItemGenerator();
	virtual ~ItemGenerator();

	void Init();
	void Release();
	void Erase(int num);
	void Update(float dt);
	void Draw(RenderWindow& window);
	void Generate(Vector2f pos, int value);
};
#define ITEM_GEN (ItemGenerator::GetInstance())