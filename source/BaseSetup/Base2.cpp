#include "Bases.h"

void SetupBase2(int p)
{
	Unit x;
	Player[p].CenterViewOn(42+31, 204-1);

	// Structures
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(42+31,204-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(33+31,204-1), p, mapNone, 0);
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
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(33+31,200-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(42+31,207-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(46+31,207-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapCommonStorage, LOCATION(29+31,200-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapRobotCommand, LOCATION(39+31,204-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(26+31,207-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(26+31,204-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(26+31,201-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(31+31,210-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(35+31,210-1), p, mapNone, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 31+31, 195-1, 0, 0, 0);
	TethysGame::CreateUnit(x, mapCommonOreMine, LOCATION(31+31,195-1), p, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(x, mapConVec, LOCATION(40+31, 205-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(44+31, 208-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(30+31, 202-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(30+31, 206-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(29+31, 211-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapScout, LOCATION(26+31, 193-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(41+31, 201-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(43+31, 201-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(30+31, 197-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(30+31, 195-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(38+31, 210-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(39+31, 209-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(40+31, 210-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboDozer, LOCATION(39+31, 211-1), p, mapNone, 4);
		x.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(36+31, 204-1, 37+31, 204-1, mapTube);
	CreateTubeOrWallLine(28+31, 204-1, 30+31, 204-1, mapTube);

	// Initial resources
	Player[p].SetKids(10);
	Player[p].SetWorkers(35);
	Player[p].SetScientists(20);
	Player[p].SetOre(2000);
	Player[p].SetFoodStored(2000);

	// Initial Vehicles
	map_id wpn = mapMicrowave;
	if (Player[p].IsEden())
	{
		wpn = mapLaser;
	}

	switch (TethysGame::InitialUnits())
	{
		case 12:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(26+31, 212-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 11:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(25+31, 212-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 10:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(24+31, 212-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 9:
			TethysGame::CreateUnit(x, mapTradeCenter, LOCATION(46+31, 204-1), p, mapNone, 0);
		case 8:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(27+31, 211-1), p, wpn, 0);
				x.DoSetLights(1);
		case 7:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(26+31, 211-1), p, wpn, 0);
				x.DoSetLights(1);
		case 6:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(25+31, 211-1), p, wpn, 0);
				x.DoSetLights(1);
		case 5:
			TethysGame::CreateUnit(x, mapScout, LOCATION(24+31, 211-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 4:
			TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(27+31, 210-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 3:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(26+31, 210-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 2:
			TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(25+31, 210-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 1:
			TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(24+31, 210-1), p, mapNone, 0);
				x.DoSetLights(1);
		default:
			break;
	}
}