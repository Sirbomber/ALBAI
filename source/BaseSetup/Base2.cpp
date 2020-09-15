#include "Bases.h"

void SetupBase2(int p, int aiNum)
{
	Unit x;
	Player[p].CenterViewOn(253 - 1, 142 - 1);

	// Structures
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(253 - 1, 143 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(249 - 1, 142 - 1), p, mapNone, 0);
	x.SetFactoryCargo(0, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(1, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(2, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(3, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(4, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(5, mapAtheistBuildingExplosion, mapNone);
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(258 - 1, 142 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(244 - 1, 143 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(249 - 1, 134 - 1), p, mapNone, 0);

	TethysGame::CreateBeacon(mapMiningBeacon, 260 - 1, 146 - 1, 0, 1, 1);
	TethysGame::CreateUnit(x, mapCommonOreMine, LOCATION(260 - 1, 146 - 1), p, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(x, mapConVec, LOCATION(253 - 1, 148 - 1), p, mapCommandCenter, 2);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(250 - 1, 146 - 1), p, mapStructureFactory, 2);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapConVec, LOCATION(256 - 1, 145 - 1), p, mapCommonOreSmelter, 3);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapConVec, LOCATION(251 - 1, 139 - 1), p, mapTokamak, 2);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapConVec, LOCATION(244 - 1, 145 - 1), p, mapAgridome, 1);
	x.DoSetLights(1);
	
	if (Player[p].IsEden())
	{
		TethysGame::CreateUnit(x, mapConVec, LOCATION(250 - 1, 143 - 1), p, mapBasicLab, 4);
	}
	else
	{
		TethysGame::CreateUnit(x, mapConVec, LOCATION(247 - 1, 143 - 1), p, mapBasicLab, 4);
	}
	x.DoSetLights(1);
	if (Player[p].Difficulty() == 0)
	{
		x.SetCargo(mapStandardLab, mapNone);
	}

	TethysGame::CreateUnit(x, mapScout, LOCATION(258 - 1, 150 - 1), p, mapNone, 2);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(255 - 1, 143 - 1), p, mapNone, 3);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(251 - 1, 143 - 1), p, mapNone, 1);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(243 - 1, 143 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	x.SetTruckCargo(truckFood, 1000);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(246 - 1, 142 - 1), p, mapNone, 2);
	x.DoSetLights(1);
	x.SetTruckCargo(truckFood, 1000);

	if (Player[p].Difficulty() < 2)
	{
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(241 - 1, 142 - 1), p, mapNone, 2);
		x.DoSetLights(1);
		x.SetTruckCargo(truckFood, 1000);
	}
	
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(259 - 1, 143 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	x.SetTruckCargo(truckCommonMetal, 1000);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(259 - 1, 146 - 1), p, mapNone, 2);
	x.DoSetLights(1);
	x.SetTruckCargo(truckCommonMetal, 1000);

	if (Player[p].Difficulty() == 0)
	{
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(260 - 1, 145 - 1), p, mapNone, 3);
		x.DoSetLights(1);
		x.SetTruckCargo(truckCommonMetal, 1000);
	}

	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(248 - 1, 146 - 1), p, mapNone, 2);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(261 - 1, 146 - 1), p, mapNone, 3);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(260 - 1, 149 - 1), p, mapNone, 2);
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
		TethysGame::CreateUnit(x, mapConVec, LOCATION(243 - 1, 149 - 1), p, mapCommandCenter, 0);
		x.DoSetLights(1);
	case 11:
		TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(242 - 1, 149 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 10:
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(241 - 1, 149 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 9:
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(240 - 1, 149 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 8:
		TethysGame::CreateUnit(x, mapScout, LOCATION(243 - 1, 148 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 7:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(242 - 1, 148 - 1), p, wpn, 0);
		x.DoSetLights(1);
	case 6:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(241 - 1, 148 - 1), p, wpn, 0);
		x.DoSetLights(1);
	case 5:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(240 - 1, 148 - 1), p, wpn, 0);
		x.DoSetLights(1);
	case 4:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(243 - 1, 147 - 1), p, mapStarflare, 0);
		x.DoSetLights(1);
	case 3:
		TethysGame::CreateUnit(x, mapConVec, LOCATION(242 - 1, 147 - 1), p, mapAgridome, 0);
		x.DoSetLights(1);
	case 2:
		TethysGame::CreateUnit(x, mapConVec, LOCATION(241 - 1, 147 - 1), p, mapUniversity, 0);
		x.DoSetLights(1);
	case 1:
		TethysGame::CreateUnit(x, mapConVec, LOCATION(240 - 1, 147 - 1), p, mapNursery, 0);
		x.DoSetLights(1);
	default:
		break;
	}

	// Auto-movement
	PlayerVehicleEnum mover(p);
	while (mover.GetNext(x))
	{
		x.DoMove(LOCATION(254 - 1, 167 - 1));
	}

	// For reference
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(263 - 1, 147 - 1), aiNum, mapNone, 0);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(262 - 1, 142 - 1), aiNum, mapNone, 0);
	x.SetDamage(250);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(258 - 1, 138 - 1), aiNum, mapNone, 0);
	x.SetDamage(500);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(253 - 1, 139 - 1), aiNum, mapNone, 0);
	x.SetDamage(750);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(249 - 1, 138 - 1), aiNum, mapNone, 0);
	x.SetDamage(1000);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(246 - 1, 141 - 1), aiNum, mapAdvancedLab, 3);
	x.DoBuild(mapAdvancedLab, LOCATION(246 - 1, 141 - 1));
	//TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(244 - 1, 139 - 1), aiNum, mapNone, 0);
	//TethysGame::CreateUnit(x, mapLynx, LOCATION(263 - 1, 149 - 1), p, mapStarflare, 0);
	
}