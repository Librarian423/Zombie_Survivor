#include "PlayerStatTable.h"

string PlayerStatTable::PlayerDataPath("gamedata/playerData.csv");

PlayerStatTable::PlayerStatTable()
{
    // player data Load
    rapidcsv::Document doc(PlayerDataPath, rapidcsv::LabelParams(0, -1));

    auto reqexp = doc.GetColumn<int>(0);
    auto health = doc.GetColumn<int>(1);
    auto damage = doc.GetColumn<int>(2);
    maxLevel = doc.GetRowCount();
    for (int i = 0; i < maxLevel; ++i)
    {
        playerData.insert({ i, new StatData(reqexp[i], health[i], damage[i]) });
    }
}

PlayerStatTable::~PlayerStatTable()
{
}