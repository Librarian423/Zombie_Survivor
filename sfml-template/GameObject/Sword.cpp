#include "Sword.h"
#include "Slash.h"
#include "VertexArrayObj.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/ResourceMgr.h"
#include "../Scenes/SceneMgr.h"
#include "Player.h"
#include "Slash.h"

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
	//this->slash = slash;
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
		Slash* slash = new Slash();
		slash->SetTexture(*RESOURCE_MGR->GetTexture("graphics/sword-slash.png"));
		slash->Init();
		Fire(slash);
		scene->AddGameObj(slash);
		
		
	}
}

void Sword::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Sword::Fire(Slash* slash)
{
	Vector2f startPos = player->GetPosition() + look * 25.f;
	slash->Fire(startPos, look, 1000, 50);
	slash->SetBackground(background);
	//scene->AddGameObj(slash);
	
	fireTimer = 0.f;
	
}
