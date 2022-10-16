#include "Slash.h"
#include "Zombie.h"
#include "../Framework/Utils.h"
#include "../GameObject/VertexArrayObj.h"
#include "../Scenes/SceneMgr.h"

Slash::Slash()
	:speed(0), range(0.f)
{
}

Slash::~Slash()
{
}

void Slash::SetBackground(VertexArrayObj* bk)
{
	background = bk;
}

void Slash::Fire(const Vector2f pos, const Vector2f dir, float speed, float range)
{
	sprite.setRotation(Utils::Angle(dir));
	SetPos(pos);

	this->dir = dir;
	this->speed = speed;
	this->range = range;
}

void Slash::Init()
{
	SpriteObj::Init();
	SetOrigin(Origins::MC);
	//SetZombieList(Scenes::)
}

void Slash::Release()
{
	SpriteObj::Release();
}

void Slash::Reset()
{
	dir = { 1, 0 };
	speed = 0.f;
	range = 0.f;
	sprite.setRotation(0.f);
	SetPos({ 0,0 });

	SpriteObj::Reset();
}

void Slash::Update(float dt)
{
	SpriteObj::Update(dt);
	Translate(dir * speed * dt);
	range -= Utils::Magnitude(dir * dt * speed);

	if ( range < 0 )
	{
		SetActive(false);
	}
	else
	{
		//zombies
		/*for ( Zombie* zombie : *zombies )
		{
			if ( zombie->GetActive() )
			{
				if ( GetGlobalBounds().intersects(zombie->GetGlobalBounds()) )
				{
					zombie->OnHitSlash(this);
					SetActive(false);
					break;
				}
			}
		}*/
	}
}

void Slash::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}
