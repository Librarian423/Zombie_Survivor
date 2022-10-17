#include "Pickup.h"
#include "Player.h"
#include "../Framework/ResourceMgr.h"
#include "ItemGenerator.h"

const int Pickup::TotalTypes = 3;

Pickup::Pickup()
	:type(Types::None), value(0), player(nullptr)
{
	SetHitbox(FloatRect(0.f, 0.f, 20.f, 20.f));
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
	case Pickup::Types::Health:
		SetTexture(*RESOURCE_MGR->GetTexture("graphics/health_pickup.png"));
		SetOrigin(Origins::MC);
		break;
	case Pickup::Types::Exp:
		SetTexture(*RESOURCE_MGR->GetTexture("graphics/exp.png"));
		SetOrigin(Origins::MC);
		sprite.setScale({ 0.1f, 0.1f });
		break;
	}
}

void Pickup::SetValue(int v)
{
	value = v;
}

void Pickup::Update(float dt)
{
	//player Á¢ÃË
	if (Utils::OBB(GetHitbox(), player->GetHitbox()))
	{
		player->OnPickupItem(this);
		SetActive(false);
		ITEM_GEN->Erase(this->GetObjId());
		cout << this->GetObjId() << endl;
	}
}