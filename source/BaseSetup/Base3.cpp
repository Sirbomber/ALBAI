#include "Bases.h"

void SetupBase3(int p)
{
	Unit x;
	Player[p].CenterViewOn(54+31, 212-1);

	// Structures
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(54+31,212-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(54+31,203-1), p, mapNone, 0);
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
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(59+31,203-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(54+31,215-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(50+31,212-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapCommonStorage, LOCATION(50+31,203-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapRobotCommand, LOCATION(47+31,222-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(50+31,219-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(50+31,222-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(47+31,219-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(60+31,212-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(60+31,208-1), p, mapNone, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 69+31, 203-1, 0, 0, 0);
	TethysGame::CreateUnit(x, mapCommonOreMine, LOCATION(69+31,203-1), p, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(x, mapConVec, LOCATION(52+31, 213-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(52+31, 216-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(51+31, 206-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(56+31, 206-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(59+31, 210-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapScout, LOCATION(45+31, 213-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(53+31, 209-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(55+31, 209-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(63+31, 204-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(63+31, 202-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(43+31, 213-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(42+31, 214-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(42+31, 212-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboDozer, LOCATION(41+31, 213-1), p, mapNone, 4);
		x.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(54+31, 206-1, 54+31, 210-1, mapTube);
	CreateTubeOrWallLine(54+31, 217-1, 54+31, 219-1, mapTube);
	CreateTubeOrWallLine(52+31, 219-1, 53+31, 219-1, mapTube);

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
			TethysGame::CreateUnit(x, mapConVec, LOCATION(53+31, 210-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 11:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(54+31, 209-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 10:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(52+31, 209-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 9:
			TethysGame::CreateUnit(x, mapTradeCenter, LOCATION(44+31, 219-1), p, mapNone, 0);
		case 8:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(55+31, 208-1), p, wpn, 0);
				x.DoSetLights(1);
		case 7:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(54+31, 208-1), p, wpn, 0);
				x.DoSetLights(1);
		case 6:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(53+31, 208-1), p, wpn, 0);
				x.DoSetLights(1);
		case 5:
			TethysGame::CreateUnit(x, mapScout, LOCATION(52+31, 208-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 4:
			TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(55+31, 207-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 3:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(54+31, 207-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 2:
			TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(53+31, 207-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 1:
			TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(52+31, 207-1), p, mapNone, 0);
				x.DoSetLights(1);
		default:
			break;
	}
}