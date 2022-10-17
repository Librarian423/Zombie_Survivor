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
	RectangleShape expBar;
	//player hp
	RectangleShape playerHpBar;
	//zombie hp
	RectangleShape zombieHpBar;
	//Timer
	TextObj* timer;
	//setting
	SpriteObj* settingBackground;
	TextObj* setting;
	TextObj* home;
	TextObj* restart;
	TextObj* volume;
	TextObj* volumePlus;
	TextObj* volumeMinus;
	TextObj* speed;
	TextObj* speedPlus;
	TextObj* speedMinus;

	SpriteObj* cursor;

	Languages languagesMode;
public:
	UIDev1Mgr(Scene* scene);
	virtual ~UIDev1Mgr();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

};