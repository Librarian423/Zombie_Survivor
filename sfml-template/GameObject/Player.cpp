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
#include "MachineGun.h"

Player::Player()
	:speed(500), accelation(1000), deaccelation(1000), fireMode(FireModes::PISTOL), exp(0.f)
{
}

Player::~Player()
{
}

void Player::SetBulletPool(ObjectPool<Bullet>* ptr)
{
	bulletPool = ptr;
}

void Player::SetSlashPool(ObjectPool<Bullet>* ptr)
{
	SlashPool = ptr;
}

void Player::SetBackground(VertexArrayObj* bk)
{
	background = bk;
}

void Player::Init()
{
	SetOrigin(Origins::MC);
	SpriteObj::Init();

	level = 1;
	exp = 0.f;
	SetStatData(level);

	scene = SCENE_MGR->GetCurScene();
	uiMgr = scene->GetUIMgr();
}

void Player::Reset()
{
	direction = { 1.f,0.f };
	velocity = { 0.f,0.f };
	level = 1;
	exp = 0.f;
	fireMode = FireModes::PISTOL;
	SetStatData(level);
}

void Player::Update(float dt)
{
	SpriteObj::Update(dt);

	RenderWindow& window = FRAMEWORK->GetWindow();
	Vector2i mousePos = (Vector2i)InputMgr::GetMousePos();
	Vector2f mouseWorldPos = scene->ScreenToWorldPos(mousePos);

	look = Utils::Normalize(mouseWorldPos);

	sprite.setRotation(Utils::Angle(look));
	hitbox.setRotation(Utils::Angle(look));

	direction.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	direction.y = InputMgr::GetAxisRaw(Axis::Vertical);
	
	//가속
	velocity += direction * accelation * dt;
	if ( Utils::Magnitude(velocity) > speed )
	{
		velocity = Utils::Normalize(velocity) * speed;
	}

	//감속
	if (Utils::Magnitude(direction) == 0.f)
	{
		velocity = { 0.f, 0.f };
	}

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

	// test
	if (InputMgr::GetKeyDown(Keyboard::P))
	{
		cout << "level: " << level << endl <<
			"requireExp: " << requireExp << endl <<
			"health: " << health << endl <<
			"damage: " << damage << endl <<
			"exp: " << exp << endl;
	}

	if ( InputMgr::GetMouseDown(Mouse::Button::Right) )
	{
		SetShootType();
	}

	// die
	if (health <= 0.f)
	{
		cout << "die" << endl;
	}

	// level up
	if (exp >= requireExp)
	{
		exp -= requireExp;
		level++;
		SetStatData(level);
		cout << "level up!! " << level << endl;
	}
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Player::ResetVelocity()
{
	velocity = Vector2f(0, 0);
}

void Player::SetShootType()
{
	fireMode = (FireModes)((int)fireMode + 1);
	if (fireMode == FireModes::COUNT)
		fireMode = FireModes::PISTOL;
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
		health += item->GetValue();
		break;
	}
}

void Player::OnHitZombie(Zombie* zombie)
{
	if (Utils::OBB(hitbox, zombie->GetHitbox()))
	{
		cout << zombie->GetObjId() << zombie->GetName() << "-충돌" << health << endl;
		SetHealth(-FRAMEWORK->GetRealDT() * 10.f * zombie->GetDamage());
	}
	else
	{
		cout << zombie->GetObjId() << zombie->GetName() << "-충돌 아님" << endl;
	}
}

VertexArrayObj* Player::GetPlayerBackground()
{
	return background;
}

ObjectPool<Bullet>* Player::GetBulletPool()
{
	return bulletPool;
}

ObjectPool<Bullet>* Player::GetSlashPool()
{
	return SlashPool;
}

Vector2f Player::GetPosition()
{
	return position;
}

Vector2f Player::GetLook()
{
	return look;
}

FireModes Player::GetFireMode()
{
	return fireMode;
}