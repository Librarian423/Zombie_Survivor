#pragma once
#include "UIMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"
#include "../DataTable/StringTable.h"

class Scene;

class UIDev1Mgr :public UIMgr
{
protected:
	//exp
	SpriteObj* expFrame;
	RectangleShape* expBar;
	float requireExp;
	float exp;
	//player hp
	RectangleShape* playerHpBar;
	float maxHealth;
	float health;
	//zombie hp
	RectangleShape* zombieHpBar;
	//Timer
	TextObj* timer;
	//setting
	SpriteObj* settingBackground;
	TextObj* setting;
	TextObj* Menu;
	TextObj* restart;
	TextObj* volume;
	TextObj* volumePlus;
	TextObj* volumeMinus;
	//TextObj* speed;
	//TextObj* speedPlus;
	//TextObj* speedMinus;
	//win
	SpriteObj* win;
	//Lose
	SpriteObj* Lose;

	SpriteObj* cursor;
	
	bool isPause = false;
	bool isMenu = false;
	bool isRestart = false;
	bool isVolume = false;
	bool isVolumePlus = false;
	bool isVolumeMinus = false;

public:
	UIDev1Mgr(Scene* scene);
	virtual ~UIDev1Mgr();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	bool GetIsPause();
	bool GetIsMenu();
	bool GetIsRestart();
	bool GetIsVolumePlus();
	bool GetIsVolumeMinus();

	void SetsettingBackground(bool is) { settingBackground->SetActive(is); };

	void SetRequireExp(float requireExp) {  this->requireExp= requireExp; }
	void SetExp(float exp) { this->exp= exp; }
	void SetMaxHealth(float maxHealth) { this->maxHealth= maxHealth; }
	void SetHealth(float health) { this->health= health; }
};