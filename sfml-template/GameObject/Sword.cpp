#include "Sword.h"
#include "VertexArrayObj.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/ResourceMgr.h"
#include "Player.h"
#include "Bullet.h"

Sword::Sword(Player* player)
	: Weapon(1.0f, 0.5f)
{
	this->player = player;
	SetName("Sword");
}

Sword::~Sword()
{

}

void Sword::Init()
{
	SpriteObj::Init();
	bulletPool = player->GetSlashPool();
	background = player->GetPlayerBackground();
}

void Sword::Reset()
{
	SpriteObj::Reset();
}

void Sword::Update(float dt)
{
	if (!enabled)
		return;

	SpriteObj::Update(dt);

	look = player->GetLook();

	if ( bulletPool == nullptr )
	{
		return;
	}

	fireTimer += dt;

	if ( fireTimer > intervalWeapon && InputMgr::GetMouse(Mouse::Button::Left) )
	{
		Fire();
	}
}

void Sword::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Sword::Fire()
{
	Vector2f startPos = player->GetPosition() + look * 25.f;
	Bullet* bullet = bulletPool->Get();
	bullet->Fire(startPos, look, 300, 75);
	bullet->SetBackground(background);
	fireTimer = 0.f;
}