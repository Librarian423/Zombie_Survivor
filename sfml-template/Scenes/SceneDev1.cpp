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
#include "../GameObject/MachineGun.h"
#include "../GameObject/Sword.h"
#include "../UI/UIDev1Mgr.h"

void OnCreateBullet(Bullet* bullet)
{
	SceneDev1* scene = (SceneDev1*)SCENE_MGR->GetScene(Scenes::Dev1);
	bullet->SetTexture(*RESOURCE_MGR->GetTexture("graphics/bullet.png"));
	bullet->SetZombieList(scene->GetZombieList());
	bullet->SetHitbox(FloatRect(0.f, 0.f, 10.f, 10.f));
	//bullet->SetDevMode(true);
	bullet->Init();
}

void OnCreateSlash(Bullet* bullet)
{
	SceneDev1* scene = (SceneDev1*)SCENE_MGR->GetScene(Scenes::Dev1);
	bullet->SetTexture(*RESOURCE_MGR->GetTexture("graphics/sword-slash.png"));
	bullet->SetZombieList(scene->GetZombieList());
	bullet->SetHitbox(FloatRect(0.f, 0.f, 70.f, 70.f));
	//bullet->SetDevMode(true);
	bullet->Init();
}

SceneDev1::SceneDev1()
	: Scene(Scenes::Dev1)
{

}

SceneDev1::~SceneDev1()
{

}

void SceneDev1::Init()
{
	Release();
	

	CreateBackground(20, 30, 50.f, 50.f);

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

	uiMgr = new UIDev1Mgr(this);
	uiMgr->Init();
	bullets.OnCreate = OnCreateBullet;
	bullets.Init();

	slashes.OnCreate = OnCreateSlash;
	slashes.Init();

	ITEM_GEN->Init();

	//weapon
	Pistol* pistol = new Pistol(player);
	objList.push_back(pistol);

	MachineGun* machineGun = new MachineGun(player);
	objList.push_back(machineGun);

	Sword* sword = new Sword(player);
	objList.push_back(sword);

	for ( auto obj : objList )
	{
		obj->Init();
	}

	weapons.push_back(pistol);
	weapons.push_back(machineGun);
	weapons.push_back(sword);
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
}

void SceneDev1::Enter()
{
	SOUND_MGR->Play("sound/battle.wav", true);
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
	stage = 1;
	CreateZombies(stage);

	player->Reset();
	bullets.Reset();
	slashes.Reset();
	uiMgr->Reset();
	ChangeWeapon((int)player->GetFireMode());
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
	SOUND_MGR->StopAll();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	// 비활성화된 좀비 제거
	for (auto it = zombies.begin(); it != zombies.end(); )
	{
		if (!(*it)->GetActive())
		{
			it = zombies.erase(it);
		}
		else
			it++;
	}

	for (auto it = objList.begin(); it != objList.end(); )
	{
		if (!(*it)->GetActive() && !(*it)->GetType().compare("Zombie"))
		{
			delete (*it);
			it = objList.erase(it);
		}
		else
			it++;
	}

	if (zombies.empty())
		CreateZombies(++stage);

	worldView.setCenter(player->GetPos());
	
	uiMgr->Update(dt);
	worldView.setCenter(player->GetPos());
	if (((UIDev1Mgr*)uiMgr)->GetIsMenu() && InputMgr::GetMouseDown(Mouse::Left))
	{
		SCENE_MGR->ChangeScene(Scenes::Menu);
		return;
	}
	if (((UIDev1Mgr*)uiMgr)->GetIsRestart() && InputMgr::GetMouseDown(Mouse::Left))
	{
		//SCENE_MGR->ChangeScene(Scenes::Dev1);
		Exit();
		Enter();
		return;
	}
	if (((UIDev1Mgr*)uiMgr)->GetIsVolumePlus() && InputMgr::GetMouseDown(Mouse::Left))
	{
		SOUND_MGR->SetVolume(10.f);
	}
	if (((UIDev1Mgr*)uiMgr)->GetIsVolumeMinus() && InputMgr::GetMouseDown(Mouse::Left))
	{
		SOUND_MGR->SetVolume(-10.f);
	}

	if (((UIDev1Mgr*)uiMgr)->GetIsPause())
		return;

	Scene::Update(dt);

	// 개발용 start
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
	if (InputMgr::GetKeyDown(Keyboard::F3))
	{
		for (Object* obj : zombies)
		{
			obj->SetActive(false);
		}
	}
	// 개발용 end

	if (InputMgr::GetMouseDown(Mouse::Button::Right))
	{
		ChangeWeapon((int)player->GetFireMode());
	}

	bullets.Update(dt);
	slashes.Update(dt);
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

void SceneDev1::CreateZombies(int wave)
{
	int count = 5 + 5 * wave;
	bool isBossRound = wave % 3 == 0 ? true : false;
	bool isKingRound = wave == 10 ? true : false;

	if (isKingRound)
	{
		Zombie* zombie = new Zombie();
		Vector2f genPos =
			Utils::RandomOutCirclePoint() *
			Utils::RandomRange(400.f, 600.f);
		zombie->SetPos(genPos);
		zombie->SetType("Zombie");
		zombie->SetZombieType(Zombie::Types::King, wave);
		zombie->Init(player);
		zombie->SetBackground(background);
		objList.push_back(zombie);
		zombies.push_back(zombie);
		return ;
	}

	if (isBossRound)
	{
		int bossCount = wave / 3;
		for (int i = 0; i < bossCount; i++)
		{
			Zombie* zombie = new Zombie();
			Vector2f genPos =
				Utils::RandomOutCirclePoint() *
				Utils::RandomRange(400.f, 600.f);
			zombie->SetPos(genPos);
			zombie->SetType("Zombie");
			zombie->SetZombieType(Zombie::Types::Boss, wave);
			zombie->Init(player);
			zombie->SetBackground(background);
			objList.push_back(zombie);
			zombies.push_back(zombie);
		}
	}

	for ( int i = 0; i < count; i++ )
	{
		Zombie* zombie = new Zombie();
		Vector2f genPos =
			Utils::RandomOutCirclePoint() * Utils::RandomRange(400.f, 600.f);
		zombie->SetPos(genPos);
		zombie->SetType("Zombie");
		if (i < count * 0.5f)
			zombie->SetZombieType(Zombie::Types::Crawler, wave);
		else if (i < count * 0.75f)
			zombie->SetZombieType(Zombie::Types::Chaser, wave);
		else
			zombie->SetZombieType(Zombie::Types::Bloater, wave);

		zombie->Init(player);
		zombie->SetBackground(background);
		objList.push_back(zombie);
		zombies.push_back(zombie);
	}
}

void SceneDev1::ChangeWeapon(int mode)
{
	int idx = 0;
	for (auto i : weapons)
	{
		if (idx == mode)
			i->SetActive(true);
		else
			i->SetActive(false);
		idx++;
	}
}