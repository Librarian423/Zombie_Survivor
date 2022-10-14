#include "Bullet.h"
#include "Zombie.h"
#include "../Framework/Utils.h"
#include "../GameObject/VertexArrayObj.h"

Bullet::Bullet()
	:dir(), speed(0.f), range(0.f)
{
}

Bullet::~Bullet()
{
}

void Bullet::SetBackground(VertexArrayObj* bk)
{
	background = bk;
}

void Bullet::Fire(const Vector2f pos, const Vector2f dir, float speed, float range)
{
	sprite.setRotation(Utils::Angle(dir));
	SetPos(pos);

	this->dir = dir;
	this->speed = speed;
	this->range = range;
}

void Bullet::Init()
{
	SetOrigin(Origins::MC);
	SpriteObj::Init();
}

void Bullet::Release()
{
	SpriteObj::Release();
}

void Bullet::Reset()
{
	this->dir = { 1,0 };
	this->speed = 0.f;
	this->range = 0.f;
	sprite.setRotation(0.f);
	SetPos({ 0.f,0.f });

	SpriteObj::Reset();
}

void Bullet::Update(float dt)
{
	SpriteObj::Update(dt);
	Translate(dir * this->speed * dt);
	range -= Utils::Magnitude(dir * this->speed * dt);

	//wall bound
	float border = 50.f;
	FloatRect wallBound = background->GetGlobalBounds();
	Vector2f pos;
	pos.x = Utils::Clamp(position.x,
		wallBound.left + border,
		wallBound.left + wallBound.width - border);
	pos.y = Utils::Clamp(position.y,
		wallBound.top + border,
		wallBound.top + wallBound.height - border);

	if ( pos != position )
	{
		SetActive(false);
	}

	if ( range < 0 )
	{
		SetActive(false);
	}
	else
	{
		//zombies
		for ( Zombie* zombie : *zombies )
		{
			if ( zombie->GetActive() )
			{
				if ( GetGlobalBounds().intersects(zombie->GetHitbox()) )
				{
					zombie->OnHitBullet(this);
					SetActive(false);
					break;
				}
			}
		}
	}
	
}

void Bullet::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}