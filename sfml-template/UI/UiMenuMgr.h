#pragma once
#include "UIMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"
#include "../DataTable/StringTable.h"

class Scene;

class UiMenuMgr :    public UIMgr
{
protected:
	TextObj* gameStart;
	SpriteObj* background;
	TextObj* language;
	TextObj* Korean;
	TextObj* English;
	
	SpriteObj* cursor;
	bool isGameStart = false;
	bool isLanguage = false;

	Languages languagesMode;

public:
	UiMenuMgr(Scene* scene);
	virtual ~UiMenuMgr();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

