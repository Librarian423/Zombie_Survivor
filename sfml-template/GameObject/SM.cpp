#include "SM.h"
#include "Bullet.h"
#include "VertexArrayObj.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/SceneMgr.h"

SM::SM()
	:fireTimer(1.0f), intervalSM(0.1f)
{
}

SM::~SM()
{
}

void SM::Init(Player* player)
{
	this->player = player;
	scene = SCENE_MGR->GetCurScene();
	bulletPool = player->GetBulletPool();
	background = player->GetPlayerBackground();
	SpriteObj::Init();
}

void SM::Reset()
{
	SpriteObj::Reset();
}

void SM::Update(float dt)
{
	SpriteObj::Update(dt);

	look = player->GetLook();
	if ( bulletPool == nullptr )
	{
		return;
	}
	
	fireTimer += dt;
	if ( fireTimer > intervalSM && InputMgr::GetMouse(Mouse::Button::Left) )
	{
		Fire();
	}
	
	
}

void SM::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void SM::Fire()
{
	Vector2f startPos = player->GetPosition() + look * 25.f;
	Bullet* bullet = bulletPool->Get();
	bullet->Fire(startPos, look, 1000, 1000);
	bullet->SetBackground(background);
	fireTimer = 0.f;
}
