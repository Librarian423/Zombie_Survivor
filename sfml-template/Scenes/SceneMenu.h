#pragma once
#include "Scene.h"
#include "../UI/UiMenuMgr.h"

class SceneMenu : public Scene
{
protected:
public:
	SceneMenu();
	virtual ~SceneMenu();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

