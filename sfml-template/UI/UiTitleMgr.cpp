#include "UiTitleMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneTitle.h"
#include "../Framework/InputMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/StringTable.h"
#include "../SFML-2.5.1/include/SFML/Graphics/Font.hpp"

using namespace sf;

UiTitleMgr::UiTitleMgr(Scene* scene)
	:UIMgr(scene)
{
}

UiTitleMgr::~UiTitleMgr()
{
}

void UiTitleMgr::Init()
{
	UIMgr::Init();
	Vector2i WindowSize = FRAMEWORK->GetWindowSize();
	//background
	background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/background.png"));
	background->SetScale(FRAMEWORK->GetWindowSize().x/background->GetSize().x, FRAMEWORK->GetWindowSize().y / background->GetSize().y);
	uiObjList.push_back(background);
	
	auto stringTable = DATATABLE_MGR->Get<StringTable>(DataTable::Types::String);
	stringTable->SetLanguage(StringTable::getCurrentLang());

	//title
	title = new TextObj();
	title->SetText(stringTable->Get("Title_Title"));
	title->GetSfmlText().setCharacterSize(120);
	title->SetOrigin(Origins::MC);
	title->SetPos({ WindowSize.x *0.5f,WindowSize.y *0.2f });
	uiObjList.push_back(title);
		
	//Guide
	guide = new TextObj();
	guide->SetText(stringTable->Get("Title_Guide"));
	guide->GetSfmlText().setCharacterSize(40);
	guide->SetOrigin(Origins::MC);
	guide->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.8f });
	uiObjList.push_back(guide);
	
}

void UiTitleMgr::Release()
{
	UIMgr::Release();
}

void UiTitleMgr::Reset()
{
	UIMgr::Reset();
}

void UiTitleMgr::Update(float dt)
{
	UIMgr::Update(dt);
}

void UiTitleMgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UIMgr::Draw(window);
}
