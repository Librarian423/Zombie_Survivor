#include "Pistol.h"
#include "Bullet.h"
#include "VertexArrayObj.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/SceneMgr.h"
#include <iostream>

Pistol::Pistol()
	:fireTimer(1.0f), intervalPistol(0.1f), intervalSM(0.1f), intervalSword(0.3f), type(WeaponTypes::PISTOL)
{
}

Pistol::~Pistol()
{
}

void Pistol::Init(Player* player)
{
	this->player = player;
	scene = SCENE_MGR->GetCurScene();
	bulletPool = player->GetBulletPool();
	background = player->GetPlayerBackground();
	SpriteObj::Init();
}

void Pistol::Reset()
{
	SpriteObj::Reset();
}

void Pistol::Update(float dt)
{
	SpriteObj::Update(dt);
	/*RenderWindow& window = FRAMEWORK->GetWindow();
	Vector2i mousePos = (Vector2i)InputMgr::GetMousePos();
	Vector2f mouseWorldPos = scene->ScreenToWorldPos(mousePos);

	look = Utils::Normalize(mouseWorldPos - GetPos());*/
	look = player->GetLook();
	if ( bulletPool == nullptr )
	{
		return;
	}
	if ( InputMgr::GetKeyDown(Keyboard::Key::Num1) )
	{
		SetWeaponType(WeaponTypes::PISTOL);
	}
	if ( InputMgr::GetKeyDown(Keyboard::Key::Num2) )
	{
		SetWeaponType(WeaponTypes::SM);
	}
	if ( InputMgr::GetKeyDown(Keyboard::Key::Num3) )
	{
		SetWeaponType(WeaponTypes::SWORD);
	}
	fireTimer += dt;
	if ( fireTimer > intervalPistol && InputMgr::GetMouseDown(Mouse::Button::Left) )
	{
		Fire();
	}
	//bulletPool = player->GetBulletPool();
	//background = player->GetPlayerBackground();
	std::cout << (int)type << endl;
}

void Pistol::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Pistol::Fire()
{
	Vector2f startPos = player->GetPosition() + look * 25.f;
	//look = Utils::Normalize(InputMgr::GetMousePos() - startPos);
	Bullet* bullet = bulletPool->Get();

	bullet->Fire(startPos, look, 1000, 1000);
	bullet->SetBackground(background);
	fireTimer = 0.f;
}

void Pistol::SetWeaponType(WeaponTypes type)
{
	this->type = type;
}
