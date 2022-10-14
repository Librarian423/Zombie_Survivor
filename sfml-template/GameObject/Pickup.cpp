#include "Pickup.h"
#include "Player.h"
#include "../Framework/ResourceMgr.h"

const int Pickup::TotalTypes = 3;


Pickup::Pickup()
	:type(Types::None), value(0), player(nullptr), timer(0.f)
{
}

Pickup::~Pickup()
{
}

void Pickup::SetPlayer(Player* p)
{
	player = p;
}

void Pickup::SetType(Types t)
{
	type = t;
	switch ( type )
	{
	case Pickup::Types::None:
		//texture clear
		break;
	case Pickup::Types::Ammo:
		SetTexture(*RESOURCE_MGR->GetTexture("graphics/ammo_pickup.png"));
		SetOrigin(Origins::MC);
		break;
	case Pickup::Types::Health:
		SetTexture(*RESOURCE_MGR->GetTexture("graphics/health_pickup.png"));
		SetOrigin(Origins::MC);
		break;
	}
}

void Pickup::SetValue(int v)
{
	value = v;
}



void Pickup::Update(float dt)
{
	//player ����
	if ( GetGlobalBounds().intersects(player->GetGlobalBounds() ))
	{
		player->OnPickupItem(this);
		SetActive(false);
	}
	timer += dt;
	if ( timer > 3.f )
	{
		SetActive(false);
		timer = 0.f;
	}
	
}
