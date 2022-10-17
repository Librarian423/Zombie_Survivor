#include "MachineGun.h"
#include "Bullet.h"
#include "VertexArrayObj.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/SoundMgr.h"
#include "Player.h"

MachineGun::MachineGun(Player* player)
	: Weapon(1.0f, 0.1f)
{
	this->player = player;
	SetName("MachineGun");
}

MachineGun::~MachineGun()
{
}

void MachineGun::Init()
{
	SpriteObj::Init();
	bulletPool = player->GetBulletPool();
	background = player->GetPlayerBackground();
}

void MachineGun::Reset()
{
	SpriteObj::Reset();
}

void MachineGun::Update(float dt)
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

void MachineGun::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void MachineGun::Fire()
{
	SOUND_MGR->Play("sound/pistol.wav", false);
	Vector2f startPos = player->GetPosition() + look * 25.f;
	Bullet* bullet = bulletPool->Get();
	bullet->Fire(startPos, look, 1000, 1000);
	bullet->SetBackground(background);
	fireTimer = 0.f;
}