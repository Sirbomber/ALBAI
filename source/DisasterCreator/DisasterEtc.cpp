#include "DisasterCreator\DisasterCreator.h"

/*
  Blight and unfair super-disasters.
*/

void DisasterCreator::DoBlight(LOCATION blightLoc, int blightTime, disSpeed speed, disShape shape, int size)
{
	//
}

void DisasterCreator::DoUnfairQuake()
{
	TethysGame::SetEarthquake(TethysGame::GetRand(mapSize.x) + mapXOffset, TethysGame::GetRand(mapSize.y), mapPrettyArt);
}

void DisasterCreator::DoUnfairStorms()
{
	for (int y = 1; y < mapSize.y; y++)
	{
		TethysGame::SetLightning(1 + mapXOffset, y - 1, 2000, mapSize.x + mapXOffset, y - 1);
	}
}

void DisasterCreator::DoUnfairVortexes()
{
	// Spawn perma-vortexes (with the no warning flag set) on all player buildings
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		Unit ToVortex;
		PlayerBuildingEnum findStructures(i, mapNone);
		while (findStructures.GetNext(ToVortex))
		{
			TethysGame::SetTornado(ToVortex.Location().x, ToVortex.Location().y, 0,
				                   ToVortex.Location().x, ToVortex.Location().y, 1);
		}
	}
}

void DisasterCreator::DoUnfairMeteors()
{
	// Hit everyone will good old fashioned meteors
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		Unit ToVortex;
		PlayerBuildingEnum findStructures(i, mapNone);
		while (findStructures.GetNext(ToVortex))
		{
			TethysGame::SetTornado(ToVortex.Location().x, ToVortex.Location().y, 0,
				ToVortex.Location().x, ToVortex.Location().y, 1);
		}
	}
}
