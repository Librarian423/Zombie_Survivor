#pragma once
#include "Scene.h"

class SceneTitle :    public Scene
{
protected:
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

