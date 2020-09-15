#include "Bases.h"

void SetupBase5(int p, int aiNum)
{
	Unit x;
	Player[p].CenterViewOn(230 - 1, 137 - 1);

	// Structures
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(230 - 1, 137 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(225 - 1, 140 - 1), p, mapNone, 0);
	x.SetFactoryCargo(0, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(1, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(2, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(3, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(4, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(5, mapAtheistBuildingExplosion, mapNone);
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(230 - 1, 140 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(224 - 1, 144 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(228 - 1, 149 - 1), p, mapNone, 0);

	TethysGame::CreateBeacon(mapMiningBeacon, 232 - 1, 144 - 1, 0, 1, 1);
	TethysGame::CreateUnit(x, mapCommonOreMine, LOCATION(232 - 1, 144 - 1), p, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(x, mapConVec, LOCATION(226 - 1, 135 - 1), p, mapCommandCenter, 5);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(227 - 1, 139 - 1), p, mapStructureFactory, 6);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(222 - 1, 138 - 1), p, mapCommonOreSmelter, 5);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(218 - 1, 142 - 1), p, mapTokamak, 5);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(224 - 1, 142 - 1), p, mapAgridome, 4);
	x.DoSetLights(1);

	if (Player[p].IsEden())
	{
		TethysGame::CreateUnit(x, mapConVec, LOCATION(226 - 1, 141 - 1), p, mapBasicLab, 4);
	}
	else
	{
		TethysGame::CreateUnit(x, mapConVec, LOCATION(223 - 1, 141 - 1), p, mapBasicLab, 4);
	}
	x.DoSetLights(1);
	if (Player[p].Difficulty() == 0)
	{
		x.SetCargo(mapStandardLab, mapNone);
	}

	TethysGame::CreateUnit(x, mapScout, LOCATION(228 - 1, 134 - 1), p, mapNone, 4);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(228 - 1, 137 - 1), p, mapNone, 5);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(230 - 1, 138 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(221 - 1, 146 - 1), p, mapNone, 5);
	x.DoSetLights(1);
	x.SetTruckCargo(truckFood, 1000);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(223 - 1, 144 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	x.SetTruckCargo(truckFood, 1000);

	if (Player[p].Difficulty() < 2)
	{
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(224 - 1, 145 - 1), p, mapNone, 4);
		x.DoSetLights(1);
		x.SetTruckCargo(truckFood, 1000);
	}

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(231 - 1, 141 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	x.SetTruckCargo(truckCommonMetal, 1000);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(230 - 1, 142 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	x.SetTruckCargo(truckCommonMetal, 1000);

	if (Player[p].Difficulty() == 0)
	{
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(232 - 1, 140 - 1), p, mapNone, 4);
		x.DoSetLights(1);
		x.SetTruckCargo(truckCommonMetal, 1000);
	}

	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(220 - 1, 140 - 1), p, mapNone, 3);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(230 - 1, 143 - 1), p, mapNone, 4);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(232 - 1, 145 - 1), p, mapNone, 4);
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
		TethysGame::CreateUnit(x, mapConVec, LOCATION(225 - 1, 113 - 1), p, mapCommandCenter, 0);
		x.DoSetLights(1);
	case 11:
		TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(224 - 1, 113 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 10:
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(223 - 1, 113 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 9:
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(222 - 1, 113 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 8:
		TethysGame::CreateUnit(x, mapScout, LOCATION(225 - 1, 112 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	case 7:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(224 - 1, 112 - 1), p, wpn, 0);
		x.DoSetLights(1);
	case 6:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(223 - 1, 112 - 1), p, wpn, 0);
		x.DoSetLights(1);
	case 5:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(222 - 1, 112 - 1), p, wpn, 0);
		x.DoSetLights(1);
	case 4:
		TethysGame::CreateUnit(x, mapLynx, LOCATION(225 - 1, 111 - 1), p, mapStarflare, 0);
		x.DoSetLights(1);
	case 3:
		TethysGame::CreateUnit(x, mapConVec, LOCATION(224 - 1, 111 - 1), p, mapAgridome, 0);
		x.DoSetLights(1);
	case 2:
		TethysGame::CreateUnit(x, mapConVec, LOCATION(223 - 1, 111 - 1), p, mapUniversity, 0);
		x.DoSetLights(1);
	case 1:
		TethysGame::CreateUnit(x, mapConVec, LOCATION(222 - 1, 111 - 1), p, mapNursery, 0);
		x.DoSetLights(1);
	default:
		break;
	}

	// Auto-movement
	PlayerVehicleEnum mover(p);
	while (mover.GetNext(x))
	{
		x.DoMove(LOCATION(200 - 1, 122 - 1));
	}

	// For reference
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(220 - 1, 143 - 1), aiNum, mapNone, 0);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(224 - 1, 147 - 1), aiNum, mapNone, 0);
	x.SetDamage(250);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(228 - 1, 144 - 1), aiNum, mapNone, 0);
	x.SetDamage(500);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(232 - 1, 147 - 1), aiNum, mapNone, 0);
	x.SetDamage(750);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(234 - 1, 141 - 1), aiNum, mapNone, 0);
	x.SetDamage(1000);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(236 - 1, 139 - 1), aiNum, mapAdvancedLab, 3);
	x.DoBuild(mapAdvancedLab, LOCATION(236 - 1, 139 - 1));
	//TethysGame::CreateUnit(x, mapLynx, LOCATION(220 - 1, 145 - 1), p, mapStarflare, 0);
}