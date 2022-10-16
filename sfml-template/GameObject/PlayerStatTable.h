#pragma once
#include <map>
#include <string>
#include "../3rd/rapidcsv.h"

using namespace std;

// Player는 1레벨로 시작

class PlayerStatTable
{
public:
	struct StatData
	{
		int reqexp;
		int health;
		int damage;
		StatData(int req, int hp, int dmg)
		{
			reqexp = req;
			health = hp;
			damage = dmg;
		}
	};
	PlayerStatTable();
	~PlayerStatTable();

	int LoadReqExp(int idx) { return playerData[idx - 1]->reqexp; }
	int LoadHealth(int idx) { return playerData[idx - 1]->health; }
	int LoadDamage(int idx) { return playerData[idx - 1]->damage; }

private:
	static string PlayerDataPath;
	map<int, StatData*> playerData;
	int maxLevel;
};