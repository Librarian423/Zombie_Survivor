#include "UIDev1Mgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneDev1.h"
#include "../Framework/InputMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/StringTable.h"
#include <string>

UIDev1Mgr::UIDev1Mgr(Scene* scene)
	:UIMgr(scene)
{
}

UIDev1Mgr::~UIDev1Mgr()
{
}

void UIDev1Mgr::Init()
{
	Vector2i WindowSize = FRAMEWORK->GetWindowSize();
	//exp
	expFrame = new SpriteObj();
	expFrame->SetTexture(*RESOURCE_MGR->GetTexture("graphics/expbar.png"));
	expFrame->SetOrigin(Origins::TC);
	expFrame->SetScale((WindowSize.x / expFrame->GetSize().x) , 1);
	expFrame->SetPos({WindowSize.x * 0.5f,5 });
	uiObjList.push_back(expFrame);

	expBar = new RectangleShape({ expFrame->GetSize().x,expFrame->GetSize().y});
	expBar->setFillColor(Color::Green);
	expBar->setPosition(expFrame->GetPos().x - expFrame->GetSize().x * 0.5f, expFrame->GetPos().y);
	
	//player hp
	playerHpBar = new RectangleShape({ expFrame->GetSize().x,expFrame->GetSize().y });
	playerHpBar->setFillColor(Color::Green);
	playerHpBar->setPosition(expFrame->GetPos().x - expFrame->GetSize().x * 0.5f, expFrame->GetPos().y);
	//zombie hp
	zombieHpBar = new RectangleShape({ expFrame->GetSize().x,expFrame->GetSize().y });
	zombieHpBar->setFillColor(Color::Green);
	zombieHpBar->setPosition(expFrame->GetPos().x - expFrame->GetSize().x * 0.5f, expFrame->GetPos().y);
	
	auto stringTable = DATATABLE_MGR->Get<StringTable>(DataTable::Types::String);
	stringTable->SetLanguage(StringTable::getCurrentLang());
	//Timer
	timer = new TextObj();
	timer->SetText(L"00:00");
	timer->SetActive(true);
	timer->GetSfmlText().setCharacterSize(40);
	timer->SetOrigin(Origins::TC);
	timer->SetPos({ WindowSize.x * 0.5f,expFrame->GetSize().y});
	uiObjList.push_back(timer);
	//setting
	settingBackground = new SpriteObj();
	settingBackground->SetTexture(*RESOURCE_MGR->GetTexture("graphics/settingbackground.png"));
	settingBackground->SetActive(false);
	settingBackground->SetOrigin(Origins::TL);
	settingBackground->SetScale(FRAMEWORK->GetWindowSize().x / settingBackground->GetSize().x, FRAMEWORK->GetWindowSize().y / settingBackground->GetSize().y);
	settingBackground->SetPos({ 0,0});
	uiObjList.push_back(settingBackground);

	setting = new TextObj();
	setting->SetText(stringTable->Get("Game_Setting"));
	setting->SetActive(false);
	setting->GetSfmlText().setCharacterSize(60);
	setting->SetOrigin(Origins::MC);
	setting->SetColor(Color::Red);
	setting->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.5f-170 });
	uiObjList.push_back(setting);
	
	Menu = new TextObj();
	Menu->SetText(stringTable->Get("Game_Menu"));
	Menu->SetActive(false);
	Menu->GetSfmlText().setCharacterSize(40);
	Menu->SetOrigin(Origins::MC);
	Menu->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.5f-80 });
	uiObjList.push_back(Menu);
	
	restart = new TextObj();
	restart->SetText(stringTable->Get("Game_Restart"));
	restart->SetActive(false);
	restart->GetSfmlText().setCharacterSize(40);
	restart->SetOrigin(Origins::MC);
	restart->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.5f });
	uiObjList.push_back(restart);
	
	volume = new TextObj();
	volume->SetText(stringTable->Get("Game_Volume"));
	volume->SetActive(false);
	volume->GetSfmlText().setCharacterSize(40);
	volume->SetOrigin(Origins::MC);
	volume->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.5f+80 });
	uiObjList.push_back(volume);
	
	volumePlus = new TextObj();
	volumePlus->SetText(stringTable->Get("Game_VolumeUp"));
	volumePlus->SetActive(false);
	volumePlus->GetSfmlText().setCharacterSize(40);
	volumePlus->SetOrigin(Origins::MC);
	volumePlus->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.5f+160 });
	uiObjList.push_back(volumePlus);
	
	volumeMinus = new TextObj();
	volumeMinus->SetText(stringTable->Get("Game_VolumeDown"));
	volumeMinus->SetActive(false);
	volumeMinus->GetSfmlText().setCharacterSize(40);
	volumeMinus->SetOrigin(Origins::MC);
	volumeMinus->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.5f+240 });
	uiObjList.push_back(volumeMinus);
	
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
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		isPause = !isPause;
	}
	if (isPause)
	{
		settingBackground->SetActive(true);
		setting->SetActive(true);
		Menu->SetActive(true);
		restart->SetActive(true);
		volume->SetActive(true);
		if (Menu->GetGlobalBounds().intersects(cursor->GetGlobalBounds()))
		{
			Menu->SetColor(Color::Magenta);
			isMenu = !isMenu;
		}
		else
		{
			Menu->SetColor(Color::White);
			isMenu = !isMenu;
		}
		if (restart->GetGlobalBounds().intersects(cursor->GetGlobalBounds()))
		{
			restart->SetColor(Color::Magenta);
			isRestart = !isRestart;
		}
		else
		{
			restart->SetColor(Color::White);
			isRestart = !isRestart;
		}
		if (volume->GetGlobalBounds().intersects(cursor->GetGlobalBounds()))
		{
			volume->SetColor(Color::Magenta);
			isVolume = !isVolume;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				volumePlus->SetActive(true);
				volumeMinus->SetActive(true);
			}
		}
		else
		{
			volume->SetColor(Color::White);
			isVolume = !isVolume;
		}
		if (volumePlus->GetGlobalBounds().intersects(cursor->GetGlobalBounds()))
		{
			volumePlus->SetColor(Color::Magenta);
			isVolumePlus = !isVolumePlus;
		}
		else
		{
			volumePlus->SetColor(Color::White);
			isVolumePlus = !isVolumePlus;
		}
		if (volumeMinus->GetGlobalBounds().intersects(cursor->GetGlobalBounds()))
		{
			volumeMinus->SetColor(Color::Magenta);
			isVolumeMinus = !isVolumeMinus;
		}
		else
		{
			volumeMinus->SetColor(Color::White);
			isVolumeMinus = !isVolumeMinus;
		}
	}
	else
	{
		settingBackground->SetActive(false);
		setting->SetActive(false);
		Menu->SetActive(false);
		restart->SetActive(false);
		volume->SetActive(false);
		volumePlus->SetActive(false);
		volumeMinus->SetActive(false);
	}
	
	Vector2f worldMousePos = parentScene->ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);

	int windowtime = (float)FRAMEWORK->GetRealDT();
	int mintext = windowtime / 60;
	int sectext = windowtime % 60;
	String time = to_string(mintext) + ":" + to_string(sectext);
	timer->SetText(time);
	
}

void UIDev1Mgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UIMgr::Draw(window);
}

bool UIDev1Mgr::GetIsPause()
{
	return isPause;
}

bool UIDev1Mgr::GetIsMenu()
{
	return isMenu;
}

bool UIDev1Mgr::GetIsRestart()
{
	return isRestart;
}

bool UIDev1Mgr::GetIsVolumePlus()
{
	return isVolumePlus;
}

bool UIDev1Mgr::GetIsVolumeMinus()
{
	return isVolumeMinus;
}
