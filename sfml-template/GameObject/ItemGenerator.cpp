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

void ItemGenerator::Generate(Vector2f pos)
{
	Scene* scene = SCENE_MGR->GetCurScene();

	Pickup::Types itemType = (Pickup::Types)Utils::RandomRange(1, (int)Pickup::Types::Count);

	Pickup* item = new Pickup();
	item->SetType(itemType);
	item->SetValue(10);
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

		for ( auto i : itemList )
		{
			if ( i->GetActive() &&
				item->GetGlobalBounds().intersects(i->GetGlobalBounds()) )
			{
				success = false;
				count++;
			}
		}
	}
	if ( success )
	{
		itemList.push_back(item);
	}
	else
	{
		delete item;
	}
}
