#include "SceneMenu.h"
#include "SceneMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
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
}

void SceneMenu::Exit()
{
	//FRAMEWORK->GetWindow().setMouseCursorVisible(true);
	uiMgr->Reset();
}

void SceneMenu::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev1);
	}

	uiMgr->Update(dt);
}

void SceneMenu::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	uiMgr->Draw(window);
}
