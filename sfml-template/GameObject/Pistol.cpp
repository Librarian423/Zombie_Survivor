#include "Pistol.h"
#include "Bullet.h"
#include "VertexArrayObj.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "Player.h"

Pistol::Pistol(Player* player)
	: Weapon(1.0f, 0.1f)
{
	this->player = player;
	SetName("Pistol");
}

Pistol::~Pistol()
{
}

void Pistol::Init()
{
	SpriteObj::Init();
	bulletPool = player->GetBulletPool();
	background = player->GetPlayerBackground();
}

void Pistol::Reset()
{
	SpriteObj::Reset();
}

void Pistol::Update(float dt)
{
	if (!enabled)
		return;

	if (bulletPool == nullptr)
		return;
	SpriteObj::Update(dt);
	
	look = player->GetLook();

	fireTimer += dt;

	if ( fireTimer > intervalWeapon && InputMgr::GetMouseDown(Mouse::Button::Left) )
	{
		Fire();
	}
}

void Pistol::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Pistol::Fire()
{
	Vector2f startPos = player->GetPosition() + look * 25.f;
	Bullet* bullet = bulletPool->Get();
	bullet->Fire(startPos, look, 1000, 1000);
	bullet->SetBackground(background);
	fireTimer = 0.f;
}