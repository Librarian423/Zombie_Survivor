#include "Zombie.h"
#include "Player.h"
#include "VertexArrayObj.h"
#include "../Framework/ResourceMgr.h"
#define _USE_MATH_DEFINES

const int Zombie::TotalTypes = 3;

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::Update(float dt)
{
    SpriteObj::Update(dt);
    dir = Utils::Normalize(player->GetPos() - GetPos());

    Translate(dir * this->speed * dt);

    float distance = Utils::Distance(player->GetPos(), GetPos());
    if ( distance < this->speed * dt * 0.5f )
    {
        SetPos(player->GetPos());
    }
    else
    {
        sprite.setRotation(Utils::Angle(dir));
        hitbox.setRotation(Utils::Angle(dir));
    }
    
    //좀비 벽 충돌
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
        SetPos(pos);
    }

    //플레이어 충돌
    if ( GetGlobalBounds().intersects(player->GetHitbox()) )
    {
        player->OnHitZombie(this);
    }
}

void Zombie::Draw(RenderWindow& window)
{
    SpriteObj::Draw(window);
}

void Zombie::SetBackground(VertexArrayObj* bk)
{
    background = bk;
}

void Zombie::Init(Player* player)
{
    this->player = player;
    SetOrigin(Origins::MC);

    SpriteObj::Init();
}

void Zombie::SetType(Types t)
{
    type = t;

    auto resMgr = RESOURCE_MGR;
    switch ( type )
	{
	case Zombie::Types::Bloater:
	{
        SetTexture(*resMgr->GetTexture("graphics/bloater.png"));
        SetHitbox(FloatRect(0.f, 0.f, 40.f, 45.f));
        SetName("bloater");
	    this->speed = 40 ;
        maxHp = 100.f;
	    break;
	}
	case Zombie::Types::Chaser:
	{
        SetTexture(*resMgr->GetTexture("graphics/chaser.png"));
        SetHitbox(FloatRect(0.f, 0.f, 20.f, 30.f));
        SetName("chaser");
	    this->speed = 70 ;
        maxHp = 75.f;
	    break;
	}
	case Zombie::Types::Crawler:
	{ 
        SetTexture(*resMgr->GetTexture("graphics/crawler.png"));
        SetHitbox({ -30.f, -122.f, 30.f, 18.f });
        SetHitbox(FloatRect(0.f, -3.f, 30.f, 22.f));
        SetName("crawler");
	    this->speed = 20 ;
        maxHp = 50.f;
	    break;
	}
	default:
        break;
    }

    //SetPos(position);
}

Zombie::Types Zombie::GetType() const
{
    return type;
}

void Zombie::Reset()
{
    SpriteObj::Reset();

    dir = { 1.f,0.f };
    hp = maxHp;

   /* dir = Utils::Normalize(player->GetPos() - GetPos());
    float degree = atan2(dir.y, dir.x) * (180 / M_PI);
    sprite.setRotation(degree);*/
    SetPos(position);
}

void Zombie::OnHitBullet(Bullet* bullet)
{
    SetActive(false);
}