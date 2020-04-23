#include "Bases.h"

void SetupBase1(int p)
{
	Unit x;
	Player[p].CenterViewOn(10+31, 191-1);

	// Structures
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(10+31,191-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(10+31,197-1), p, mapNone, 0);
	switch (Player[p].Difficulty())
	{
		case 0:
			x.SetFactoryCargo(0, mapStructureFactory, mapNone);
			x.SetFactoryCargo(1, mapCommandCenter, mapNone);
			x.SetFactoryCargo(2, mapAgridome, mapNone);
			break;
		case 1:
			x.SetFactoryCargo(0, mapTokamak, mapNone);
			x.SetFactoryCargo(1, mapAgridome, mapNone);
			break;
		case 2:
			x.SetFactoryCargo(0, mapBasicLab, mapNone);
			break;
		default:
			x.SetFactoryCargo(5, mapSpaceport, mapNone);
			break;
	}
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(15+31,197-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(14+31,191-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(10+31,188-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapCommonStorage, LOCATION(17+31,191-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapRobotCommand, LOCATION(7+31,191-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(3+31,194-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(3+31,197-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(3+31,200-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(3+31,189-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(3+31,185-1), p, mapNone, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 21+31, 203-1, 0, 0, 0);
	TethysGame::CreateUnit(x, mapCommonOreMine, LOCATION(21+31,203-1), p, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(x, mapConVec, LOCATION(8+31, 192-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(12+31, 192-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(7+31, 199-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(12+31, 199-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(2+31, 191-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapScout, LOCATION(16+31, 189-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(9+31, 193-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(11+31, 193-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(16+31, 201-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(16+31, 203-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(10+31, 201-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(9+31, 202-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(11+31, 202-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboDozer, LOCATION(10+31, 203-1), p, mapNone, 4);
		x.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(10+31, 193-1, 10+31, 195-1, mapTube);
	CreateTubeOrWallLine( 5+31, 197-1,  7+31, 197-1, mapTube);

	// Initial resources
	Player[p].SetKids(10);
	Player[p].SetWorkers(35);
	Player[p].SetScientists(20);
	Player[p].SetOre(2000);
	Player[p].SetFoodStored(2000);

	// Initial vehicles
	map_id wpn = mapMicrowave;
	if (Player[p].IsEden())
	{
		wpn = mapLaser;
	}

	switch (TethysGame::InitialUnits())
	{
		case 12:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(4+31, 204-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 11:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(3+31, 204-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 10:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(2+31, 204-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 9:
			TethysGame::CreateUnit(x, mapTradeCenter, LOCATION(7+31, 188-1), p, mapNone, 0);
		case 8:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(5+31, 203-1), p, wpn, 0);
				x.DoSetLights(1);
		case 7:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(4+31, 203-1), p, wpn, 0);
				x.DoSetLights(1);
		case 6:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(3+31, 203-1), p, wpn, 0);
				x.DoSetLights(1);
		case 5:
			TethysGame::CreateUnit(x, mapScout, LOCATION(2+31, 203-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 4:
			TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(5+31, 202-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 3:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(4+31, 202-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 2:
			TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(3+31, 202-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 1:
			TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(2+31, 202-1), p, mapNone, 0);
				x.DoSetLights(1);
		default:
			break;
	}

}