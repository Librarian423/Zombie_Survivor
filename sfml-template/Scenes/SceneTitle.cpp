#include "SceneTitle.h"
#include "SceneMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../UI/UiTitleMgr.h"

SceneTitle::SceneTitle()
	:Scene(Scenes::Title)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	Release();

	uiMgr = new UiTitleMgr(this);
	uiMgr->Init();
}

void SceneTitle::Release()
{
	if (uiMgr != nullptr)
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}
	Scene::Release();
}

void SceneTitle::Enter()
{
	//FRAMEWORK->GetWindow().setMouseCursorVisible(false);
	//FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);
}

void SceneTitle::Exit()
{
	//FRAMEWORK->GetWindow().setMouseCursorVisible(true);
	uiMgr->Reset();
}

void SceneTitle::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev1);
	}
	Scene::Update(dt);
}

void SceneTitle::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	uiMgr->Draw(window);
}
