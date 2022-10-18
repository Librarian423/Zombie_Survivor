#include "ItemGenerator.h"
#include "../Scenes/SceneMgr.h"
#include "Pickup.h"

ItemGenerator::ItemGenerator()
{
}

ItemGenerator::~ItemGenerator()
{
	Release();
}

void ItemGenerator::Init()
{
	itemList.push_back(new Pickup());
}

void ItemGenerator::Release()
{
	for ( auto& item: itemList )
	{
		delete item;
	}
	itemList.clear();
}

void ItemGenerator::Erase(int num)
{
	for ( auto it = itemList.begin(); it != itemList.end(); )
	{
		if ( (*it)->GetObjId() == num )
		{
			(*it)->SetActive(false);
			return;
		}
		else
		{
			it++;
		}
	}
}

void ItemGenerator::Update(float dt)
{
	for ( auto it = itemList.begin(); it != itemList.end(); )
	{
		if ( (*it)->GetActive() )
		{
			(*it)->Update(dt);
			it++;
		}
		else
		{
			(*it)->SetActive(false);
			it = itemList.erase(it);
		}
	}
}

void ItemGenerator::Draw(RenderWindow& window)
{
	for ( auto& item : itemList )
	{
		if ( item->GetActive() )
		{
			item->Draw(window);
		}
	}
}

void ItemGenerator::Generate(Vector2f pos, int value)
{
	Scene* scene = SCENE_MGR->GetCurScene();
	int healthChance = Utils::RandomRange(0, 100);
	Pickup::Types itemType;
	if ( healthChance <= 9 )
	{
		itemType = Pickup::Types::Health;
	}
	else
	{
		itemType = Pickup::Types::Exp;
	}

	Pickup* item = new Pickup();
	item->SetType(itemType);
	if ( item->GetType() == Pickup::Types::Exp )
	{
		float scale = 0.06f + sqrt(value) * 0.02f;
		item->SetScale(scale, scale);
		item->SetValue(value);
	}
	else
	{
		item->SetValue(10);
	}
	item->SetPlayer((Player*)scene->FindGameObj("Player"));
	item->Init();

	Vector2f center = { 0,0 };
	bool success = false;
	int count = 0;

	while ( !success && count < 100 )
	{
		success = true;
		Vector2f position = pos;

		item->SetPos(position);

	}
	itemList.push_back(item);
}
