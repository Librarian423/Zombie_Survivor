#pragma once
#include "UIMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"

class Scene;

class UIDev1Mgr :public UIMgr
{
protected:
	//SCORE
	string formatScore;
	TextObj* textScore;
	SpriteObj* cursor;

public:
	UIDev1Mgr(Scene* scene);
	virtual ~UIDev1Mgr();

	void SetScore(int score);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

};

