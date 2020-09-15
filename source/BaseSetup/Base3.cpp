#include "Bases.h"

void SetupBase3(int p, int aiNum)
{
	Unit x;
	Player[p].CenterViewOn(253 - 1, 111 - 1);

	// Structures
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(253 - 1, 111 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(253 - 1, 107 - 1), p, mapNone, 0);
	x.SetFactoryCargo(0, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(1, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(2, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(3, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(4, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(5, mapAtheistBuildingExplosion, mapNone);
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(262 - 1, 106 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(257 - 1, 107 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(245 - 1, 108 - 1), p, mapNone, 0);

	TethysGame::CreateBeacon(mapMiningBeacon, 264 - 1, 110 - 1, 0, 1, 1);
	TethysGame::CreateUnit(x, mapCommonOreMine, LOCATION(264 - 1, 110 - 1), p, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(x, mapConVec, LOCATION(256 - 1, 103 - 1), p, mapCommandCenter, 6);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(254 - 1, 105 - 1), p, mapStructureFactory, 6);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(261 - 1, 109 - 1), p, mapCommonOreSmelter, 5);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(245 - 1, 104 - 1), p, mapTokamak, 7);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(250 - 1, 106 - 1), p, mapAgridome, 6);
	x.DoSetLights(1);

	if (Player[p].IsEden())
	{
		TethysGame::CreateUnit(x, mapConVec, LOCATION(254 - 1, 108 - 1), p, mapBasicLab, 4);
	}
	else
	{
		TethysGame::CreateUnit(x, mapConVec, LOCATION(251 - 1, 108 - 1), p, mapBasicLab, 4);
	}
	x.DoSetLights(1);
	if (Player[p].Difficulty() == 0)
	{
		x.SetCargo(mapStandardLab, mapNone);
	}

	TethysGame::CreateUnit(x, mapScout, LOCATION(260 - 1, 104 - 1), p, mapNone, 5);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(255 - 1, 111 - 1), p, mapNone, 6);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(252 - 1, 112 - 1), p, mapNone, 5);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(256 - 1, 107 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	x.SetTruckCargo(truckFood, 1000);
	
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(259 - 1, 107 - 1), p, mapNone, 6);
	x.DoSetLights(1);
	x.SetTruckCargo(truckFood, 1000);

	if (Player[p].Difficulty() < 2)
	{
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(255 - 1, 106 - 1), p, mapNone, 0);
		x.DoSetLights(1);
		x.SetTruckCargo(truckFood, 1000);
	}

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(264 - 1, 105 - 1), p, mapNone, 5);
	x.DoSetLights(1);
	x.SetTruckCargo(truckCommonMetal, 1000);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(264 - 1, 106 - 1), p, mapNone, 6);
	x.DoSetLights(1);
	x.SetTruckCargo(truckCommonMetal, 1000);

	if (Player[p].Difficulty() == 0)
	{
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(263 - 1, 107 - 1), p, mapNone, 4);
		x.DoSetLights(1);
		x.SetTruckCargo(truckCommonMetal, 1000);
	}

	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(259 - 1, 102 - 1), p, mapNone, 6);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(265 - 1, 110 - 1), p, mapNone, 6);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(262 - 1, 111 - 1), p, mapNone, 5);
	x.DoSetLights(1);

	// Initial resources
	Player[p].SetKids(10);
	Player[p].SetWorkers(35);
	Player[p].SetScientists(20);
	Player[p].SetOre(1200);
	Player[p].SetFoodStored(8000);
	switch (Player[p].Difficulty())
	{
	case 0:
		Player[p].MarkResearchComplete(2701);
		Player[p].MarkResearchComplete(2702);
		Player[p].MarkResearchComplete(2703);
		Player[p].MarkResearchComplete(2704);
		Player[p].MarkResearchComplete(2705);
		Player[p].MarkResearchComplete(2707);
		Player[p].MarkResearchComplete(2708);
		Player[p].MarkResearchComplete(3401);
		Player[p].MarkResearchComplete(3304);
		break;
	case 1:
		Player[p].MarkResearchComplete(2703);
		Player[p].MarkResearchComplete(2704);
		Player[p].MarkResearchComplete(2707);
		Player[p].MarkResearchComplete(3304);
		break;
	case 2:
		Player[p].MarkResearchComplete(3304);
		break;
	}
	// Initial vehicles
	map_id wpn = mapMicrowave;
	if (Player[p].IsEden())
	{
		wpn = mapLaser;
	}

	switch (TethysGame::InitialUnits())
	{
	case 12:
		TethysGame::CreateUnit(x, mapConVec, LOCATION(270 - 1, 105 - 1), p, mapCommandCenter, 0);
		x.DoSetLights(1);
	case 11:
		TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(289 - 1, 105 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 10:
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(268 - 1, 105 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 9:
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(267 - 1, 105 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 8:
		TethysGame::CreateUnit(x, mapScout, LOCATION(270 - 1, 104 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 7:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(269 - 1, 104 - 1), p, wpn, 0);
		x.DoSetLights(1);
	case 6:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(268 - 1, 104 - 1), p, wpn, 0);
		x.DoSetLights(1);
	case 5:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(267 - 1, 104 - 1), p, wpn, 0);
		x.DoSetLights(1);
	case 4:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(270 - 1, 103 - 1), p, mapStarflare, 0);
		x.DoSetLights(1);
	case 3:
		TethysGame::CreateUnit(x, mapConVec, LOCATION(269 - 1, 103 - 1), p, mapAgridome, 0);
		x.DoSetLights(1);
	case 2:
		TethysGame::CreateUnit(x, mapConVec, LOCATION(268 - 1, 103 - 1), p, mapUniversity, 0);
		x.DoSetLights(1);
	case 1:
		TethysGame::CreateUnit(x, mapConVec, LOCATION(267 - 1, 103 - 1), p, mapNursery, 0);
		x.DoSetLights(1);
	default:
		break;
	}
	
	// Auto-movement
	PlayerVehicleEnum mover(p);
	while (mover.GetNext(x))
	{
		x.DoMove(LOCATION(263 - 1, 76 - 1));
	}
	
	// For reference
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(267 - 1, 109 - 1), aiNum, mapNone, 0);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(263 - 1, 113 - 1), aiNum, mapNone, 0);
	x.SetDamage(250);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(258 - 1, 111 - 1), aiNum, mapNone, 0);
	x.SetDamage(500);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(254 - 1, 114 - 1), aiNum, mapNone, 0);
	x.SetDamage(750);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(249 - 1, 112 - 1), aiNum, mapNone, 0);
	x.SetDamage(1000);
	//TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(248 - 1, 107 - 1), aiNum, mapNone, 0);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(250 - 1, 109 - 1), aiNum, mapAdvancedLab, 3);
	x.DoBuild(mapAdvancedLab, LOCATION(250 - 1, 109 - 1));
	//TethysGame::CreateUnit(x, mapLynx, LOCATION(267 - 1, 111 - 1), p, mapStarflare, 0);
}