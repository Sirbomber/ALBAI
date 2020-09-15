// Class definition file for the advanced lab building AI
// IMPORTANT NOTE: The use of dynamically allocated structures makes this AI incompatible with saved games!

#pragma once

#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <OP2Types\OP2Units.h>
#include <OP2Types\OP2Map.h>
#include <vector>
#include <map>
#include <algorithm>

const int UNIT_LIMIT_SAFETY = 1800;		// OP2's hardcoded unit limit is 2048.  The game will crash if we try to exceed that value.  Blow some labs up if we start to approach the limit.

class ConVec;

class LabBuilder
{
public:
	LabBuilder();
	~LabBuilder();

	// Initialization
	void SetPlayerNum(int aiNum);
	void AnalyzeMap();

	// Update cycle
	void UpdateCycle(int curTime);
	void CheckConVecs();
	void CheckLabs();
	void CheckSpawnConVecs(int curTime);
	void CheckDetonateLab(int curTime);
	void AddLab(UnitEx newLab);

	// Adjust the amount of fun everyone will have
	void SetSpawnDelay(int ticksBetweenSpawns);
	void SetDetonationDelay(int ticksBetweenDetonations);
	void SetSpawnCount(int newSpawnCount);
	void SetMaxLabsPerConVec(int newMaximum);
	void SetConVecStats(int speed = 4, int turnRate = 4, int prodRate = 128);
	void SetAdvancedLabStats(int buildTime = 1800);
	void SetStructureBuildTime(map_id building, int buildTime);		// Generic version of SetAdvancedLabStats
	void SetPayloadBuilding(map_id newBuilding = mapAdvancedLab);

	// ConVec helper functions
	bool CheckLabPlacement(LOCATION candidate);
	int GetMaxLabsPerConVec() { return info_MaxLabsPerConVec; }
	map_id GetPayloadBuilding() { return info_UnitToBuild; }
	bool ValidStructure(map_id toCheck);

	// Etc
	int GetPlayerNum() { return info_PlayerNum; }

	// Debugging
	void CreateDebugConVec(LOCATION spawnAt);	// Creates a ConVec under player control that the AI thinks is its own.  For debugging the ConVec update cycle.  Fails silently in non-debug builds.

private:
	void SpawnConVec();
	void DetonateRandomLab();
	bool TileIsPassable(LOCATION tile, bool ignoreUnits);

	int info_PlayerNum;
	int info_TimeSinceLastSpawn;
	int info_TimeSinceLastDetonation;
	int info_SpawnDelay;				// Minimum time between ConVec spawns.  Set to 0 to disable spawning.
	int info_DetonateDelay;				// Minimum time between lab detonations.  Set to 0 to disable detonations.
	int info_SpawnCount;				// How many ConVecs to spawn each time.
	int info_MaxLabsPerConVec;			// Maximum number* of Advanced Labs a ConVec can deploy before automatically detonating.  Default is 6.
	                                    // * - Actually this number +1 since the first Advanced Lab gets 100% health (and may be more if lab's HP doesn't divide cleanly).
	map_id info_UnitToBuild;			// What unit should get loaded into ConVecs.  Advanced Lab by default.  But Magma Wells also explode, and fit in smaller spaces.  Just a thought.
	std::vector<map_id> info_okTypes;	// List of all structure types that have ever been buildable by the AI.

	// Use this function to get the info for a tile.
	inline int GetMapIndex(int x, int y) { return map_MapSize.x * y + x; }


	int *map_AiMapData;					// Stores the sector ID for each tile on the map.
	LOCATION map_MapSize;				// Playable map size; buffer area not included.
	bool map_MapAnalyzed;				// True if the map has been analyzed.
	int map_MainSector;					// Largest contiguous sector - it's assumed this is the playing area
	
	std::vector<ConVec> units_ConVecList;
	std::vector<UnitEx> units_LabList;
	//std::vector<UnitEx> units_EarthworkerList;		// To Do: Give the AI earthworkers to tear down player walls.
	//std::map<ConVec, MAP_RECT> units_plannedLabLocations;	// To Do: add {ConVec,build area} pairs to this when issuing a new build order, to prevent ConVecs tripping over each other.  Remove entries when construction happens or a ConVec dies.  Build area should only cover the actual building, not the bulldozed padding around it.
};
