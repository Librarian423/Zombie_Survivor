#include "Sword.h"
#include "Bullet.h"
#include "VertexArrayObj.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneMgr.h"
#include "Player.h"

Sword::Sword()
	:fireTimer(1.0f), intervalSword(0.5f)
{
}

Sword::~Sword()
{

}

void Sword::Init(Player* player)
{
	this->player = player;
	scene = SCENE_MGR->GetCurScene();
	//bulletPool = player->GetBulletPool();
	background = player->GetPlayerBackground();
	SpriteObj::Init();
}

void Sword::Reset()
{
	SpriteObj::Reset();
}

void Sword::Update(float dt)
{
	SpriteObj::Update(dt);

	look = player->GetLook();
	/*if ( bulletPool == nullptr )
	{
		return;
	}*/

	fireTimer += dt;

	if ( fireTimer > intervalSword && InputMgr::GetMouse(Mouse::Button::Left) )
	{
		//Fire();
		
	}
}

void Sword::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Sword::Fire()
{
	Vector2f startPos = player->GetPosition() + look * 25.f;
	Bullet* bullet = new Bullet();
	bullet->SetTexture(*RESOURCE_MGR->GetTexture("graphics/bullet.png"));
	bullet->Init();
	bullet->Fire(startPos, look, 1000, 50);
	bullet->SetBackground(background);
	scene->AddGameObj(bullet);
	
	fireTimer = 0.f;
	
}
