#include "SceneDev1.h"
#include "SceneMgr.h"
#include "../Frameworks.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/Player.h"
#include "../GameObject/Zombie.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Pickup.h"
#include "../GameObject/VertexArrayObj.h"
#include "../GameObject/ItemGenerator.h"
#include "../GameObject/Pistol.h"
#include "../GameObject/SM.h"
#include "../GameObject/Sword.h"
#include "../UI/UIDev1Mgr.h"

void OnCreateBullet(Bullet* bullet)
{
	SceneDev1* scene = (SceneDev1*)SCENE_MGR->GetScene(Scenes::Dev1);
	bullet->SetTexture(*RESOURCE_MGR->GetTexture("graphics/bullet.png"));
	bullet->SetZombieList(scene->GetZombieList());
	bullet->Init();
}

void OnCreateSlash(Bullet* bullet)
{
	SceneDev1* scene = (SceneDev1*)SCENE_MGR->GetScene(Scenes::Dev1);
	bullet->SetTexture(*RESOURCE_MGR->GetTexture("graphics/sword-slash.png"));
	bullet->SetZombieList(scene->GetZombieList());
	bullet->Init();
}

SceneDev1::SceneDev1() : Scene(Scenes::Dev1)
{

}

SceneDev1::~SceneDev1()
{

}

void SceneDev1::Init()
{
	Release();
	
	uiMgr = new UIDev1Mgr(this);
	uiMgr->Init();

	CreateBackground(15, 26, 50.f, 50.f);

	Vector2i centerPos = FRAMEWORK->GetWindowSize() / 2;
	background->SetPos({ 0,0 });
	background->SetOrigin(Origins::MC);
	
	//player
	player = new Player();
	player->SetName("Player");
	player->SetTexture(*RESOURCE_MGR->GetTexture("graphics/player.png"));
	player->SetHitbox(FloatRect(0.f, 0.f, 25.f, 25.f));
	player->SetBulletPool(&bullets);
	player->SetSlashPool(&slashes);
	player->SetBackground(background);
	objList.push_back(player);

	bullets.OnCreate = OnCreateBullet;
	bullets.Init();

	slashes.OnCreate = OnCreateSlash;
	slashes.Init();

	ITEM_GEN->Init();

	//weapon
	pistol = new Pistol();
	pistol->Init(player);

	sm = new SM();
	sm->Init(player);

	sword = new Sword();
	sword->Init(player);
	
	//objList.push_back(uiMgr);
	for ( auto obj : objList )
	{
		obj->Init();
	}
}

void SceneDev1::Release()
{
	if ( uiMgr != nullptr )
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}
	bullets.Release();
	slashes.Release();
	Scene::Release();
	player = nullptr;
	pistol = nullptr;
	sm = nullptr;
	sword = nullptr;
}

void SceneDev1::Enter()
{
	ITEM_GEN->Release();

	//마우스 커서
	FRAMEWORK->GetWindow().setMouseCursorVisible(false);
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);
	Vector2i size = FRAMEWORK->GetWindowSize();

	worldView.setSize(size.x, size.y);
	worldView.setCenter(0.f, 0.f);
	
	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	player->SetPos({ 0, 0 });

	//zombie
	CreateZombies(25);
}

void SceneDev1::Exit()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(true);
	
	auto it = zombies.begin();
	while ( it != zombies.end() )
	{
		objList.remove(*it);
		delete* it;

		it = zombies.erase(it);
	}
	//item
	ITEM_GEN->Release();

	player->Reset();
	bullets.Reset();
	slashes.Reset();

	uiMgr->Reset();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	worldView.setCenter(player->GetPos());

	if ( InputMgr::GetKeyDown(Keyboard::Space) )
	{
		SCENE_MGR->ChangeScene(Scenes::Dev2);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::F1))
	{
		for (Object* obj : objList)
		{
			obj->SetDevMode(false);
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::F2))
	{
		for (Object* obj : objList)
		{
			obj->SetDevMode(true);
		}
	}
	bullets.Update(dt);
	slashes.Update(dt);

	switch ( player->GetFireMode() )
	{
	case FireModes::PISTOL:
		pistol->Update(dt);
		break;
	case FireModes::SUBMACHINE:
		sm->Update(dt);
		break;
	case FireModes::SWORD:
		
		sword->Update(dt);
		break;
	default:
		break;
	}
	ITEM_GEN->Update(dt);
	uiMgr->Update(dt);
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	const auto& bulletsList = bullets.GetUseList();
	for ( auto bullet : bulletsList )
	{
		bullet->Draw(window);
	}
	const auto& slashesList = slashes.GetUseList();
	for ( auto slash : slashesList )
	{
		slash->Draw(window);
	}
	ITEM_GEN->Draw(window);
	uiMgr->Draw(window);
}

void SceneDev1::CreateBackground(int width, int height, float quadWidth, float quadHeight)
{
	if ( background == nullptr )
	{
		background = new VertexArrayObj();
		background->SetTexture(GetTexture("graphics/background_sheet.png"));
		objList.push_back(background);
	}

	Vector2f startPos = background->GetPos();
	VertexArray& va = background->GetVA();
	va.clear();
	va.setPrimitiveType(Quads);
	va.resize(width * height * 4);
	Vector2f currPos = startPos;

	Vector2f offsets[4] = {
		{0, 0},
		{quadWidth, 0},
		{quadWidth, quadHeight},
		{0, quadHeight},
	};

	for ( int i = 0; i < width; ++i )
	{
		for ( int j = 0; j < height; ++j )
		{
			int texIndex = Utils::RandomRange(0, 3);
			if ( (i == 0 || i == width - 1) || (j == 0 || j == height - 1) )
			{
				texIndex = 3;
			}
			int quadIndex = i * height + j;
			for ( int k = 0; k < 4; ++k )
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = currPos + offsets[k];
				va[vertexIndex].texCoords = offsets[k];
				va[vertexIndex].texCoords.y += quadHeight * texIndex;
			}
			currPos.x += 50;
		}
		currPos.x = startPos.x;
		currPos.y += 50;
	}
}

// wave(stage)마다 좀비의 능력치를 올려주려면 wave에 비례해서 높은 스탯을 주게함.
// CreateZombies는 GenerateWave등으로 대체, wave마다 좀비의 수/배치/종류를 다르게 줌
void SceneDev1::CreateZombies(int count)
{
	Vector2f point;

	for ( int i = 0; i < count; i++ )
	{
		Zombie* zombie = new Zombie();
		Vector2f genPos = Utils::RandomOutCirclePoint() * Utils::RandomRange(300.f, 500.f);
		zombie->SetPos(genPos);
		zombie->SetType((Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes));
		zombie->Init(player);
		zombie->SetBackground(background);
		objList.push_back(zombie);
		zombies.push_back(zombie);
	}
}
