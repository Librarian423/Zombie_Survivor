#include "UiMenuMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneMenu.h"
#include "../Framework/InputMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/StringTable.h"
#include "../SFML-2.5.1/include/SFML/Graphics/Font.hpp"

using namespace sf;

UiMenuMgr::UiMenuMgr(Scene* scene)
	:UIMgr(scene), languagesMode(Languages::ENG)
{
}

UiMenuMgr::~UiMenuMgr()
{
}

void UiMenuMgr::Init()
{
	Release();
	//문제점 화면 출력 크기 이상함
	//문제점 한글 파일 출력 시 깨짐 현상
	Vector2i WindowSize = FRAMEWORK->GetWindowSize();
	//background
	background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/background.png"));
	background->SetScale(FRAMEWORK->GetWindowSize().x / background->GetSize().x, FRAMEWORK->GetWindowSize().y / background->GetSize().y);
	uiObjList.push_back(background);

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

	//language
	language = new TextObj();
	language->SetText(stringTable->Get("Menu_Language"));
	language->SetActive(true);
	language->GetSfmlText().setCharacterSize(40);
	language->SetOrigin(Origins::MC);
	language->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.8f });
	uiObjList.push_back(language);

	//language_Korean
	Korean = new TextObj();
	Korean->SetText(stringTable->Get("Menu_Korean"));
	Korean->SetActive(false);
	Korean->GetSfmlText().setCharacterSize(40);
	Korean->SetOrigin(Origins::MC);
	Korean->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.42f });
	uiObjList.push_back(Korean);

	//language_English
	English = new TextObj();
	English->SetText(stringTable->Get("Menu_English"));
	English->SetActive(false);
	English->GetSfmlText().setCharacterSize(40);
	English->SetOrigin(Origins::MC);
	English->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.58f });
	uiObjList.push_back(English);

	//cursor
	cursor = new SpriteObj();
	cursor->SetTexture(*RESOURCE_MGR->GetTexture("graphics/crosshair.png"));
	cursor->SetOrigin(Origins::MC);
	uiObjList.push_back(cursor);

	UIMgr::Init();
}

void UiMenuMgr::Release()
{
	UIMgr::Release();
}

void UiMenuMgr::Reset()
{
	UIMgr::Reset();
}

void UiMenuMgr::Update(float dt)
{
	UIMgr::Update(dt);
	auto stringTable = DATATABLE_MGR->Get<StringTable>(DataTable::Types::String);
	Vector2f worldMousePos = parentScene->ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);

	if (gameStart->GetGlobalBounds().intersects(cursor->GetGlobalBounds()))
	{
		gameStart->SetColor(Color::Magenta);
		isGameStart = true;
		cout << isGameStart << endl;
	}
	else
	{
		gameStart->SetColor(Color::White);
		isGameStart = false;
	}
	if (language->GetGlobalBounds().intersects(cursor->GetGlobalBounds()))
	{
		language->SetColor(Color::Magenta);
		isLanguage = true;
		cout << isLanguage << endl;
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			gameStart->SetActive(false);
			language->SetActive(false);
			Korean->SetActive(true);
			English->SetActive(true);
			isLanguage = true;
		}
	}
	else
	{
		language->SetColor(Color::White);
		isLanguage = false;
	}
	if (Korean->GetGlobalBounds().intersects(cursor->GetGlobalBounds()))
	{
		Korean->SetColor(Color::Magenta);
		cout << Korean << endl;
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			languagesMode = Languages::KOR;
			Init();
		}
	}
	else
	{
		Korean->SetColor(Color::White);
	}
	if (English->GetGlobalBounds().intersects(cursor->GetGlobalBounds()))
	{
		English->SetColor(Color::Magenta);
		cout << English << endl;
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			languagesMode = Languages::ENG;
			Init();
		}
	}
	else
	{
		English->SetColor(Color::White);
	}
}

void UiMenuMgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UIMgr::Draw(window);
}
