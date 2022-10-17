#include "Zombie.h"
#include "Player.h"
#include "VertexArrayObj.h"
#include "ItemGenerator.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneMgr.h"
#include "../Framework/ResourceMgr.h"
#define _USE_MATH_DEFINES

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

void Zombie::SetZombieType(Types t, int wave)
{
    type = t;

    auto resMgr = RESOURCE_MGR;
    switch ( type )
	{
    case Zombie::Types::Crawler:
    {
        SetTexture(*resMgr->GetTexture("graphics/crawler.png"));
        SetHitbox(FloatRect(0.f, 0.f, 30.f, 22.f));
        SetName("Crawler");
        this->speed = 150;
        maxHp = 10.f + wave * 1.f;
        damage = 2.f + wave * 1.f;
        break;
    }
    case Zombie::Types::Chaser:
    {
        SetTexture(*resMgr->GetTexture("graphics/chaser.png"));
        SetHitbox(FloatRect(0.f, 0.f, 20.f, 30.f));
        SetName("Chaser");
        this->speed = 100;
        maxHp = 20.f + wave * 3.f;
        damage = 5.f + wave * 2.f;
        break;
    }
	case Zombie::Types::Bloater:
	{
        SetTexture(*resMgr->GetTexture("graphics/bloater.png"));
        SetHitbox(FloatRect(0.f, 0.f, 25.f, 40.f));
        SetName("Bloater");
	    this->speed = 70;
        maxHp = 50.f + wave * 5.f;
        damage = 10.f + wave * 3.f;
	    break;
	}
    case Zombie::Types::Boss:
    {
        SetTexture(*resMgr->GetTexture("graphics/chaser.png"));
        SetHitbox(FloatRect(0.f, 0.f, 125.f, 200.f));
        SetScale(5.f, 5.f);
        SetName("Boss");
        this->speed = 85;
        maxHp = 200.f + wave * 100.f;
        damage = 25.f + wave * 15.f;
        break;
    }
    case Zombie::Types::King:
    {
        SetTexture(*resMgr->GetTexture("graphics/bloater.png"));
        SetHitbox(FloatRect(0.f, 0.f, 250.f, 400.f));
        SetScale(10.f, 10.f);
        SetName("King");
        this->speed = 350;
        maxHp = 10000.f;
        damage = 200.f;
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
    cout << name << health << endl;

    if (health <= 0.001f)
    {
        ITEM_GEN->Generate(GetPos(), maxHp);
        SetActive(false);
    }
}