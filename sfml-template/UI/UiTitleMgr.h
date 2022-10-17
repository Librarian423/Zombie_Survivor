#pragma once
#include "UIMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"
#include "../DataTable/StringTable.h"

class Scene;

class UiTitleMgr : public UIMgr
{
protected:
	TextObj* title;
	SpriteObj* background;
	TextObj* guide;

public:
	UiTitleMgr(Scene* scene);
	virtual ~UiTitleMgr();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

