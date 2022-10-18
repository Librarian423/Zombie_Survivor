#include "SceneMenu.h"
#include "SceneMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/SoundMgr.h"
#include "../UI/UiMenuMgr.h"


SceneMenu::SceneMenu()
	:Scene(Scenes::Menu)
{
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::Init()
{
	Release();

	uiMgr = new UiMenuMgr(this);
	uiMgr->Init();
}

void SceneMenu::Release()
{
	if (uiMgr != nullptr)
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}
	Scene::Release();
}

void SceneMenu::Enter()
{
	//FRAMEWORK->GetWindow().setMouseCursorVisible(false);
	//FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);
	Vector2i size = FRAMEWORK->GetWindowSize();

	worldView.setSize(size.x, size.y);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	Init(); //왜 기본생성자가 영어인데 한글로 출력되냐 ㅅㅂ
}

void SceneMenu::Exit()
{
	//FRAMEWORK->GetWindow().setMouseCursorVisible(true);
	SOUND_MGR->StopAll();
	uiMgr->Reset();
}

void SceneMenu::Update(float dt)
{
	Scene::Update(dt);
	if (((UiMenuMgr*)uiMgr)->getIsGameStart()&&InputMgr::GetMouseDown(Mouse::Left))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev1);
	}
	if (InputMgr::GetKeyDown(Keyboard::Escape))
	{
		SCENE_MGR->ChangeScene(Scenes::Title);
	}

	uiMgr->Update(dt);
}

void SceneMenu::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	uiMgr->Draw(window);
}
