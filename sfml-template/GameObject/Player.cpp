#include "Player.h"
#include "../FrameWork/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Pickup.h"
#include "../GameObject/Zombie.h"
#include "../GameObject/VertexArrayObj.h"
#include "../Framework/Framework.h"
#include "../Scenes/SceneMgr.h"
#include "../UI/UIDev1Mgr.h"
#include "Pistol.h"
#include "SM.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <algorithm>

Player::Player()
	:speed(500), accelation(1000), deaccelation(1000), bulletPool(nullptr), fireMode(FireModes::PISTOL), isFire(false), semiTotal(3), intervalManual(0.1f), intervalAuto(0.1f), intervalSemiauto(0.1f), fireTimer(1.0f), isSemiFiring(false), semiCount(0)
{
}

Player::~Player()
{
}

void Player::SetBulletPool(ObjectPool<Bullet>* ptr)
{
	bulletPool = ptr;
	//weapon->SetBulletPool(bulletPool);
}

void Player::SetBackground(VertexArrayObj* bk)
{
	background = bk;
}

void Player::Init()
{
	SetOrigin(Origins::MC);
	SpriteObj::Init();

	scene = SCENE_MGR->GetCurScene();
	uiMgr = scene->GetUIMgr();
	
	//weapon = new Weapon();
}

void Player::Reset()
{
	direction = { 1.f,0.f };
	velocity = { 0.f,0.f };
	//ResetAmo();
}

void Player::Update(float dt)
{	
	if ( InputMgr::GetKeyDown(Keyboard::Key::B) )
	{
		((UIDev1Mgr*)uiMgr)->SetScore(Utils::RandomRange(0, 10000));
	}

	SpriteObj::Update(dt);

	RenderWindow& window = FRAMEWORK->GetWindow();
	Vector2i mousePos = (Vector2i)InputMgr::GetMousePos();
	Vector2f mouseWorldPos = scene->ScreenToWorldPos(mousePos);

	look = Utils::Normalize(mouseWorldPos - GetPos());
	
	float degree = atan2(look.y, look.x) * (180.f / M_PI);
	sprite.setRotation(degree);

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	
	//accelation
	velocity += direction * accelation * dt;
	if ( Utils::Magnitude(velocity) > speed )
	{
		velocity = Utils::Normalize(velocity) * speed;
	}
	//°¨¼Ó
	if ( direction.x == 0.f )
	{
		if ( velocity.x > 0.f )
		{
			velocity.x -= deaccelation * dt;
			if ( velocity.x < 0.f )
				velocity.x = 0.f;
		}
		if ( velocity.x < 0.f )
		{
			velocity.x += deaccelation * dt;
			if ( velocity.x > 0.f )
				velocity.x = 0.f;
		}
	}

	if ( direction.y == 0.f )
	{
		if ( velocity.y > 0.f )
		{
			velocity.y -= deaccelation * dt;
			if ( velocity.y < 0.f )
				velocity.y = 0.f;
		}
		if ( velocity.y < 0.f )
		{
			velocity.y += deaccelation * dt;
			if ( velocity.y > 0.f )
				velocity.y = 0.f;
		}
	}

	Translate(velocity * dt);
	
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
		SetPos(pos);
		ResetVelocity();
	}

	if ( bulletPool == nullptr ) 
	{
		return;
	}

	fireTimer += dt;


	if ( InputMgr::GetMouseDown(Mouse::Button::Right) )
	{
		SetShootType();
		fireTimer = numeric_limits<float>::max();
	}
	//weapon->Update(dt);
	//weapon->SetLook(look);
	//weapon->SetBackground(background);
	//weapon->SetBulletPool(bulletPool);
	/*if ( InputMgr::GetMouseDown(Mouse::Button::Left) )
	{
		SM sm;
		sm.Fire();
	}*/

	/*switch ( fireMode )
	{
	case FireModes::Manual:
	{
		if ( fireTimer > intervalManual && InputMgr::GetMouseDown(Mouse::Button::Left) )
		{
			Fire();
		}
		break;
	}

	case FireModes::Auto:
	{
		if ( fireTimer > intervalAuto && InputMgr::GetMouse(Mouse::Button::Left) )
		{
			Fire();	
		}
		break;
	}
	case FireModes::Semi:
	{
		if ( fireTimer > intervalSemiauto && (isSemiFiring || InputMgr::GetMouseDown(Mouse::Button::Left)) )
		{
			if ( semiCount == 0 )
			{
				isSemiFiring = true;
			}
			semiCount++;
			if ( semiCount <= semiTotal )
			{
				Fire();
			}
			else
			{
				isSemiFiring = false;
				fireTimer = 0.f;
				semiCount = 0;
			}
		}
		break;
	}
	}*/
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Player::Fire()
{
	Vector2f startPos = position + look * 25.f;
	//look = Utils::Normalize(InputMgr::GetMousePos() - startPos);
	Bullet* bullet = bulletPool->Get();
	bullet->Fire(startPos, look, 1000, 1000);
	bullet->SetBackground(background);
	fireTimer = 0.f;
}

void Player::ResetVelocity()
{
	velocity = Vector2f(0, 0);
}

//void Player::ResetAmo()
//{
//	ammo = 100;
//	currentAmmo = 10;
//	magazineSize = 10;
//}

void Player::SetShootType()
{
	//isSemiFiring = false;
	switch ( fireMode )
	{
	case FireModes::PISTOL:
		fireMode = FireModes::SUBMACHINE;
		break;
	case FireModes::SUBMACHINE:
		fireMode = FireModes::SWORD;
		break;
	case FireModes::SWORD:
		fireMode = FireModes::PISTOL;
		//isSemiFiring = true;
		break;
	default:
		break;
	}
}

void Player::OnPickupItem(Pickup* item)
{

	switch ( item->GetType() )
	{
	case Pickup::Types::Ammo:
		//ammo += item->GetValue();
		break;
	case Pickup::Types::Health:
		//hp increase
		break;
	}
}

void Player::OnHitZombie(Zombie* zombie)
{
	zombie->SetActive(false);
}

VertexArrayObj* Player::GetPlayerBackground()
{
	return background;
}

ObjectPool<Bullet>* Player::GetBulletPool()
{
	return bulletPool;
}

Vector2f Player::GetPosition()
{
	return position;
}

Vector2f Player::GetLook()
{
	return look;
}

Player::FireModes Player::GetFireMode()
{
	return fireMode;
}



