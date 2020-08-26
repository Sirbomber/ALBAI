#include "LabBuilder\LabBuilder.h"
#include "LabBuilder\LB_ConVec.h"

LabBuilder::LabBuilder()
{
	// Mark all our data as uninitialized (or set some default values)
	info_PlayerNum = -1;
	map_MapAnalyzed = false;

	info_SpawnDelay = -1;
	info_DetonateDelay = -1;
	info_TimeSinceLastSpawn = 0;
	info_TimeSinceLastDetonation = 0;
	info_SpawnCount = -1;
	info_MaxLabsPerConVec = 6;
}

LabBuilder::~LabBuilder()
{
	if (map_AiMapData != nullptr)
	{
		delete map_AiMapData;
	}
}

void LabBuilder::SetPlayerNum(int aiNum)
{
	// Sanity check
	if (aiNum < 0 || aiNum > 6)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetPlayerNum: Player ID invalid", -1, sndDirt);
	}

	else
	{
		// Record AI player number
		info_PlayerNum = aiNum;
	}
}

void LabBuilder::UpdateCycle(int curTime)
{
	// Abort if AI player number not set or map not analyzed
	if (info_PlayerNum == -1)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in UpdateCycle: AI not init'd", -1, sndDirt);
		return;
	}
	else if (!map_MapAnalyzed)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in UpdateCycle: Map not analyzed", -1, sndDirt);
		return;
	}

	// Check the status of all our units
	CheckConVecs();
	//CheckLabs();		// Since the labs don't do anything, checking them every 2 ticks wasted CPU time.  It's only necessary to check them right before detonating one.

	// Check if it's time to spawn new ConVecs
	CheckSpawnConVecs(curTime);

	// Check if it's time to detonate an Advanced Lab
	CheckDetonateLab(curTime);
}

void LabBuilder::CheckConVecs()
{
	// Iterate over all AI ConVecs and have them run their update process.
	// ConVecs shouldn't be able to die but remove them from the list just in case.
	// They also shouldn't be capturable, so implement a nasty surprise for any cheater who gets their hands on one...
	std::vector<ConVec>::iterator i = units_ConVecList.begin();
	while (i != units_ConVecList.end())
	{
		if (!i->GetHandle().IsLive() || i->GetHandle().GetType() != mapConVec /*|| (i->GetHandle().CreatorID() != info_PlayerNum && !i->IsDebug())*/)
		{
			i = units_ConVecList.erase(i);
		}
		else if (i->GetHandle().OwnerID() != info_PlayerNum && !i->IsDebug())
		{
			// Doom mode (to do, once I figure out how to make Advanced Lab crash into player bases like meteors)
			// In the meantime, just self-destruct the ConVec and silently spawn Blight
			GameMap::SetVirusUL(i->GetHandle().Location(), 1);
			TethysGame::SetMicrobeSpreadSpeed(100);

			#ifdef _DEBUG
			TethysGame::AddMessage(i->GetHandle(), "Blight spawned", -1, sndBeep5);
			#endif

			i->GetHandle().DoSelfDestruct();
			i = units_ConVecList.erase(i);
			
		}
		else
		{
			i->CheckStatus();
			i->GetHandle().SetDamage(0);
			i++;
		}
	}

}

void LabBuilder::CheckLabs()
{
	// Iterate over all the labs in our unit list and remove any that are dead.
	std::vector<UnitEx>::iterator i = units_LabList.begin();
	while (i != units_LabList.end())
	{
		if (!i->IsLive() || i->OwnerID() != info_PlayerNum || i->GetType() != mapAdvancedLab)
		{
			i = units_LabList.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void LabBuilder::CheckSpawnConVecs(int curTime)
{
	if (curTime == 0 ||
		(info_SpawnDelay > 0 && curTime > (info_TimeSinceLastSpawn + info_SpawnDelay)) )
	{
		// Update the last spawn time
		info_TimeSinceLastSpawn = curTime;

		// Attempt to spawn ConVecs for the AI such that they can immediately deploy their Advanced Lab cargo.
		// If after 12 attempts we can't find such a location, just place them literally anywhere.
		int numAttempts = 0;
		LOCATION spawnAt;
		for (int i = 0; i < info_SpawnCount; i++)
		{
			SpawnConVec();
		}
	}
}

void LabBuilder::CheckDetonateLab(int curTime)
{
	if (info_DetonateDelay > 0 && curTime > (info_TimeSinceLastDetonation + info_DetonateDelay))
	{
		// Update the last detonation time
		info_TimeSinceLastDetonation = curTime;

		// Update the lab list
		CheckLabs();

		// Pick a lab at random to detonate (if one exists)
		DetonateRandomLab();
	}
}

void LabBuilder::DetonateRandomLab()
{
	if (units_LabList.size() > 0)
	{
		int labIndex = TethysGame::GetRand(units_LabList.size());
		units_LabList[labIndex].DoDeath();

		#ifdef _DEBUG
		TethysGame::AddMessage(units_LabList[labIndex].Location().x * 32, units_LabList[labIndex].Location().y * 32, "Lab detonated", -1, sndBigexp1);
		#endif
	}
}

void LabBuilder::AnalyzeMap()
{
	// Initialize AI map data
	map_MapSize = LOCATION(1024, 1024);
	map_MapSize.Clip();

	// Get actual map dimensions
	if (map_MapSize.x == 0)
	{
		map_MapSize.x = 512;
	}
	else
	{
		map_MapSize.x -= 32;
	}
	map_MapSize.y += 1;

	// Initialize map structure to 0's
	map_AiMapData = new int[map_MapSize.x * map_MapSize.y];
	for (int y = 0; y < map_MapSize.y; y++)
	{
		for (int x = 0; x < map_MapSize.x; x++)
		{
			map_AiMapData[GetMapIndex(x, y)] = 0;
		}
	}

	// ** To Do: Insert analysis code here **

	// Test
	/*
	Unit Unit1;
	for (int x = 49; x <= 52; x++)
	{
		for (int y = 119; y <= 122; y++)
		{
			int t = 1;
			if (TileIsPassable(LOCATION(x, y), true))
			{
				t = 0;
			}
			TethysGame::CreateUnit(Unit1, mapScout, LOCATION(x - 3 - 1, y - 6 - 1), t, mapNone, 0);
		}
	}
	*/

	// Mark map analysis as completed so we don't get errors later.
	map_MapAnalyzed = true;
}

void LabBuilder::SetSpawnDelay(int ticksBetweenSpawns)
{
	if (ticksBetweenSpawns < 0)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetSpawnDelay: Invalid spawn delay", -1, sndDirt);
	}
	else
	{
		info_SpawnDelay = ticksBetweenSpawns;
	}
}

void LabBuilder::SetDetonationDelay(int ticksBetweenDetonations)
{
	if (ticksBetweenDetonations < 0)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetDetonationDelay: Invalid detonation delay", -1, sndDirt);
	}
	else
	{
		info_DetonateDelay = ticksBetweenDetonations;
	}
}

void LabBuilder::SetSpawnCount(int newSpawnCount)
{
	if (newSpawnCount < 0)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetSpawnCount: Invalid spawn count", -1, sndDirt);
	}
	else
	{
		info_SpawnCount = newSpawnCount;
	}
}

void LabBuilder::SetMaxLabsPerConVec(int newMaximum)
{
	if (newMaximum < 1)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetMaxLabsPerConVec: Invalid argument", -1, sndDirt);
	}
	else
	{
		info_MaxLabsPerConVec = newMaximum;
	}
}

void LabBuilder::SetConVecStats(int speed, int turnRate, int prodRate)
{
	// Sanity checks
	if (info_PlayerNum == -1)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetConVecStats: AI not init'd", -1, sndDirt);
	}
	else if (speed < 0)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetConVecStats: Invalid move speed", -1, sndDirt);
	}
	else if (turnRate < 0)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetConVecStats: Invalid turn rate", -1, sndDirt);
	}
	else if (prodRate < 0)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetConVecStats: Invalid production rate", -1, sndDirt);
	}

	else
	{
		OP2UnitInfo *convecPtr = unitInfoArray[mapConVec];
		convecPtr->playerData[info_PlayerNum].moveSpeed = speed;
		convecPtr->playerData[info_PlayerNum].turnRate = turnRate;
		convecPtr->playerData[info_PlayerNum].productionRate = prodRate;
	}
}

void LabBuilder::SetAdvancedLabStats(int buildTime)
{
	// Sanity checks
	if (info_PlayerNum == -1)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetAdvancedLabStats: AI not init'd", -1, sndDirt);
	}
	else if (buildTime < 0)
	{
		TethysGame::AddMessage(-1, -1, "LB Error in SetAdvancedLabStats: Invalid build time", -1, sndDirt);
	}

	else
	{
		OP2UnitInfo *advLabPtr = unitInfoArray[mapAdvancedLab];
		advLabPtr->playerData[info_PlayerNum].buildTime = buildTime;
	}
}

void LabBuilder::SpawnConVec()
{
	LOCATION candidate;
	int numAttempts = 0;	// Make sure we don't spend *too* long trying to find a spawn point.
	bool canBuildLabHere = false;
	do
	{
		// Get a random passible location
		candidate = LOCATION(TethysGame::GetRand(map_MapSize.x), TethysGame::GetRand(map_MapSize.y));
		if (TileIsPassable(candidate, false))
		{
			// Only count attempts where we found a a spot for the ConVec but not for the lab.
			numAttempts++;
			canBuildLabHere = CheckLabPlacement(candidate);
		}
	} while (!canBuildLabHere && numAttempts < 1000);

	UnitEx Unit1;
	TethysGame::CreateUnit(Unit1, mapConVec, candidate, info_PlayerNum, mapAdvancedLab, 3);
	if (!TethysGame::UsesDayNight())
	{
		Unit1.DoSetLights(1);
	}
	OP2Unit *internalUnit = &(*unitArray)[Unit1.unitID];
	internalUnit->flags &= ~UNIT_CANBEDAMAGED;
	Unit1.DoBuild(mapAdvancedLab, candidate);
	ConVec newConVec(Unit1, this);
	units_ConVecList.push_back(newConVec);

	#ifdef _DEBUG
	if (canBuildLabHere)
	{
		TethysGame::AddMessage(candidate.x * 32, candidate.y * 32, "ConVec spawned", 0, sndBeep2);
	}
	else
	{
		TethysGame::AddMessage(candidate.x * 32, candidate.y * 32, "ConVec spawned (could not find lab placement)", 0, sndBeep2);
	}
	#endif
}

bool LabBuilder::CheckLabPlacement(LOCATION candidate)
{
	LOCATION labCheck = LOCATION(candidate.x - 4, candidate.y - 4);
	if (labCheck.x < 0)
	{
		labCheck.x = map_MapSize.x - 4 + candidate.x;
	}
	LOCATION checkedTile = labCheck;
	while (checkedTile.x <= candidate.x && checkedTile.y <= candidate.y)
	{
		// Normally, if another unit exists on a tile, it will be considered blocked.  Units on padding tiles won't block construction though, so skip that check for those tiles.
		bool isPadding = (checkedTile.x == labCheck.x || checkedTile.x == candidate.x ||
			checkedTile.y == labCheck.y || checkedTile.y == candidate.y);
		if (!TileIsPassable(checkedTile, isPadding))
		{
			return false;
		}

		// Move to the next tile.
		checkedTile.x += 1;

		// Adjust coordinates for world maps.
		if (checkedTile.x > map_MapSize.x)
		{
			checkedTile.x -= map_MapSize.x;
		}

		// Check if we're at the end of the row and adjust search tile to the start of the next row if so.
		if (checkedTile.x == candidate.x + 1)
		{
			checkedTile.x = labCheck.x;
			checkedTile.y++;
		}
	}
	return true;
}

void LabBuilder::AddLab(UnitEx newLab)
{
	// Sanity check
	if (newLab.OwnerID() == info_PlayerNum && newLab.GetType() == mapAdvancedLab)
	{
		units_LabList.push_back(newLab);
	}
}

bool LabBuilder::TileIsPassable(LOCATION tile, bool ignoreUnits)
{
	// Make sure this tile is on the map
	if (tile.x < 1 ||
		tile.x > map_MapSize.x ||
		tile.y < 1 ||
		tile.y > map_MapSize.y)
	{
		return false;
	}

	// Check if tile is impassable or has a unit on it.
	int type = GameMap::GetCellType(tile);
	if (type == cellImpassible1 ||
		type == cellImpassible2 ||
		type == cellNorthCliffs ||
		type == cellCliffsHighSide ||
		type == cellCliffsLowSide ||
		type == cellVentsAndFumaroles ||
		GameMapEx::GetTileEx(tile).lava ||
		GameMapEx::GetTileEx(tile).microbe ||
		GameMapEx::GetTileEx(tile).wallOrBuilding ||
		(!ignoreUnits && GameMapEx::GetTileEx(tile).unitIndex > 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void LabBuilder::CreateDebugConVec(LOCATION spawnAt)
{
#ifdef _DEBUG
	UnitEx Unit1;
	TethysGame::CreateUnit(Unit1, mapConVec, spawnAt, 0, mapAdvancedLab, 3);
	//Unit1.DoSetLights(1);
	//Unit1.DoBuild(mapAdvancedLab, spawnAt);
	ConVec newConVec(Unit1, this, true);
	units_ConVecList.push_back(newConVec);
#endif
}
