// Class definition file for the advanced lab building AI

#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <vector>

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

	// Use this function to get the info for a tile.
	inline int GetMapIndex(int x, int y) { return map_MapSize.x * y + x; }


	int *map_AiMapData;					// Stores the sector ID for each tile on the map.
	LOCATION map_MapSize;
	bool map_MapAnalyzed;
	int map_MainSector;
	

	std::vector<ConVec> units_ConVecList;
	std::vector<UnitEx> units_LabList;
};
