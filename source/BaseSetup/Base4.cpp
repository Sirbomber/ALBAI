#include "Bases.h"

void SetupBase4(int p)
{
	Unit x;
	Player[p].CenterViewOn(71+31, 220-1);

	// Structures
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(71+31,220-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(56+31,228-1), p, mapNone, 0);
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
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(61+31,228-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(71+31,217-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(71+31,223-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapCommonStorage, LOCATION(64+31,228-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapRobotCommand, LOCATION(68+31,220-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(64+31,220-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(61+31,220-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(61+31,223-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(69+31,211-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(73+31,211-1), p, mapNone, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 67+31, 235-1, 0, 0, 0);
	TethysGame::CreateUnit(x, mapCommonOreMine, LOCATION(67+31,235-1), p, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(x, mapConVec, LOCATION(69+31, 221-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(69+31, 224-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(53+31, 230-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(58+31, 230-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(67+31, 212-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapScout, LOCATION(75+31, 224-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(74+31, 219-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(74+31, 221-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(62+31, 235-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(62+31, 233-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(65+31, 229-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(66+31, 228-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(66+31, 230-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboDozer, LOCATION(67+31, 229-1), p, mapNone, 4);
		x.DoSetLights(1);

	// Tubes
	TethysGame::CreateWallOrTube(66+31,220-1,0, mapTube);
	CreateTubeOrWallLine(61+31, 225-1, 61+31, 226-1, mapTube);

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
			TethysGame::CreateUnit(x, mapConVec, LOCATION(55+31, 224-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 11:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(54+31, 224-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 10:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(53+31, 224-1), p, mapNone, 0);
				x.SetCargo(mapGuardPost, wpn);
				x.DoSetLights(1);
		case 9:
			TethysGame::CreateUnit(x, mapTradeCenter, LOCATION(64+31, 223-1), p, mapNone, 0);
		case 8:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(56+31, 223-1), p, wpn, 0);
				x.DoSetLights(1);
		case 7:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(55+31, 223-1), p, wpn, 0);
				x.DoSetLights(1);
		case 6:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(54+31, 223-1), p, wpn, 0);
				x.DoSetLights(1);
		case 5:
			TethysGame::CreateUnit(x, mapScout, LOCATION(53+31, 223-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 4:
			TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(56+31, 222-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 3:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(55+31, 222-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 2:
			TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(54+31, 222-1), p, mapNone, 0);
				x.DoSetLights(1);
		case 1:
			TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(53+31, 222-1), p, mapNone, 0);
				x.DoSetLights(1);
		default:
			break;
	}
}