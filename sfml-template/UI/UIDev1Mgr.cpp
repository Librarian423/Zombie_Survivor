#include "UIDev1Mgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneDev1.h"
#include "../Framework/InputMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/StringTable.h"

UIDev1Mgr::UIDev1Mgr(Scene* scene)
	:UIMgr(scene)
{
}

UIDev1Mgr::~UIDev1Mgr()
{
}

void UIDev1Mgr::Init()
{
	//exp
	expFrame = new SpriteObj();
	expFrame->SetTexture(*RESOURCE_MGR->GetTexture("graphics/background.png"));
	expFrame->SetScale(FRAMEWORK->GetWindowSize().x / background->GetSize().x, FRAMEWORK->GetWindowSize().y / background->GetSize().y);
	uiObjList.push_back(expFrame);

	auto stringTable = DATATABLE_MGR->Get<StringTable>(DataTable::Types::String);
	stringTable->SetLanguage(languagesMode);


	//gameStrat
	gameStart = new TextObj();
	gameStart->SetText(stringTable->Get("Menu_Game"));
	gameStart->SetActive(true);
	gameStart->GetSfmlText().setCharacterSize(40);
	gameStart->SetOrigin(Origins::MC);
	gameStart->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.7f });
	uiObjList.push_back(gameStart);
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
