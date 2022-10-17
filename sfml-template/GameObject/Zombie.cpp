#include "Zombie.h"
#include "Player.h"
#include "VertexArrayObj.h"
#include "ItemGenerator.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneMgr.h"
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
    if ( hitbox.getGlobalBounds().intersects(player->GetHitbox().getGlobalBounds()) )
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
    scene = SCENE_MGR->GetCurScene();
    SpriteObj::Init();
}

void Zombie::SetZombieType(Types t)
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
        maxHp = 50.f;
        damage = 10.f;
	    break;
	}
	case Zombie::Types::Chaser:
	{
        SetTexture(*resMgr->GetTexture("graphics/chaser.png"));
        SetHitbox(FloatRect(0.f, 0.f, 20.f, 30.f));
        SetName("chaser");
	    this->speed = 70 ;
        maxHp = 20.f;
        damage = 5.f;
	    break;
	}
	case Zombie::Types::Crawler:
	{ 
        SetTexture(*resMgr->GetTexture("graphics/crawler.png"));
        SetHitbox(FloatRect(0.f, 0.f, 30.f, 22.f));
        SetName("crawler");
	    this->speed = 20 ;
        maxHp = 10.f;
        damage = 2.f;
	    break;
	}
	default:
        break;
    }
    health = maxHp;
}

Zombie::Types Zombie::GetZombieType() const
{
    return type;
}

Vector2f Zombie::GetDir()
{
    return dir;
}

void Zombie::Reset()
{
    SpriteObj::Reset();

    dir = { 1.f,0.f };
    health = maxHp;
    SetPos(position);
    
}

void Zombie::OnHitBullet(Bullet* bullet)
{
    SetHealth(-player->GetDamage());

    if (health <= 0.001f)
    {
        // 경험치 아이템을 드랍하게 하고, 드랍한 아이템을 획득하면 경험치를 획득하게 함
        ITEM_GEN->Generate(GetPos(), maxHp);
        //player->SetExp(maxHp);
        SetActive(false);
    }
}