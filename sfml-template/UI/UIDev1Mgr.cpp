#include "UIDev1Mgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneDev1.h"
#include "../Framework/InputMgr.h"

UIDev1Mgr::UIDev1Mgr(Scene* scene)
	:UIMgr(scene), formatScore("SCORE: ")
{
}

UIDev1Mgr::~UIDev1Mgr()
{
}

void UIDev1Mgr::SetScore(int score)
{
	textScore->SetText(formatScore + to_string(score));
}

void UIDev1Mgr::Init()
{
	textScore = new TextObj();
	textScore->SetFont(*RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf"));
	textScore->GetSfmlText().setCharacterSize(75);
	textScore->SetPos({ 50,50 });
	uiObjList.push_back(textScore);

	//cursor
	cursor = new SpriteObj();
	cursor->SetTexture(*RESOURCE_MGR->GetTexture("graphics/crosshair.png"));
	cursor->SetOrigin(Origins::MC);
	uiObjList.push_back(cursor);

	UIMgr::Init();
}

void UIDev1Mgr::Release()
{
	UIMgr::Release();
}

void UIDev1Mgr::Reset()
{
	UIMgr::Reset();
	SetScore(0);
}

void UIDev1Mgr::Update(float dt)
{
	UIMgr::Update(dt);
	Vector2f worldMousePos = parentScene->ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);
}

void UIDev1Mgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UIMgr::Draw(window);
}
