#include "Bases.h"

void SetupBase1(int p, int aiNum)
{
	Unit x;
	Player[p].CenterViewOn(268 - 1, 124 - 1);

	// Structures
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(268 - 1, 124 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(269 - 1, 127 - 1), p, mapNone, 0);
	x.SetFactoryCargo(0, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(1, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(2, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(3, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(4, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(5, mapAtheistBuildingExplosion, mapNone);
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(274 - 1, 127 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(272 - 1, 124 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(263 - 1, 119 - 1), p, mapNone, 0);

	TethysGame::CreateBeacon(mapMiningBeacon, 276 - 1, 131 - 1, 0, 1, 1);
	TethysGame::CreateUnit(x, mapCommonOreMine, LOCATION(276 - 1, 131 - 1), p, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(x, mapConVec, LOCATION(277 - 1, 124 - 1), p, mapCommandCenter, 7);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapConVec, LOCATION(274-1, 125-1), p, mapStructureFactory, 0);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapConVec, LOCATION(271 - 1, 126 - 1), p, mapCommonOreSmelter, 7);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapConVec, LOCATION(273 - 1, 129 - 1), p, mapTokamak, 0);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapConVec, LOCATION(268 - 1, 125 - 1), p, mapAgridome, 0);
	x.DoSetLights(1);

	if (Player[p].IsEden())
	{
		TethysGame::CreateUnit(x, mapConVec, LOCATION(270 - 1, 128 - 1), p, mapBasicLab, 4);
	}
	else
	{
		TethysGame::CreateUnit(x, mapConVec, LOCATION(267 - 1, 128 - 1), p, mapBasicLab, 4);
	}
	x.DoSetLights(1);
	if (Player[p].Difficulty() == 0)
	{
		x.SetCargo(mapStandardLab, mapNone);
	}

	TethysGame::CreateUnit(x, mapScout, LOCATION(264 - 1, 133 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(269 - 1, 122 - 1), p, mapNone, 0);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(266 - 1, 123 - 1), p, mapNone, 6);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(271 - 1, 124 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	x.SetTruckCargo(truckFood, 1000);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(277 - 1, 122 - 1), p, mapNone, 0);
	x.DoSetLights(1);
	x.SetTruckCargo(truckFood, 1000);

	if (Player[p].Difficulty() < 2)
	{
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(273 - 1, 122 - 1), p, mapNone, 0);
		x.DoSetLights(1);
		x.SetTruckCargo(truckFood, 1000);
	}

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(277 - 1, 127 - 1), p, mapNone, 7);
	x.DoSetLights(1);
	x.SetTruckCargo(truckCommonMetal, 1000);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(276 - 1, 128 - 1), p, mapNone, 7);
	x.DoSetLights(1);
	x.SetTruckCargo(truckCommonMetal, 1000);

	if (Player[p].Difficulty() == 0)
	{
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(275 - 1, 128 - 1), p, mapNone, 4);
		x.DoSetLights(1);
		x.SetTruckCargo(truckCommonMetal, 1000);
	}

	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(275 - 1, 123 - 1), p, mapNone, 7);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(275-1, 132-1), p, mapNone, 0);
	x.DoSetLights(1);
	
	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(277-1, 130-1), p, mapNone, 7);
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
			TethysGame::CreateUnit(x, mapConVec, LOCATION(283 - 1, 134 - 1), p, mapCommandCenter, 0);
			x.DoSetLights(1);
		case 11:
			TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(282 - 1, 134 - 1), p, mapNone, 0);
			x.DoSetLights(1);
		case 10:
			TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(281 - 1, 134 - 1), p, mapNone, 0);
			x.DoSetLights(1);
		case 9:
			TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(280 - 1, 134 - 1), p, mapNone, 0);
			x.DoSetLights(1);
		case 8:
			TethysGame::CreateUnit(x, mapScout, LOCATION(283 - 1, 133 - 1), p, mapNone, 0);
			x.DoSetLights(1);
		case 7:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(282 - 1, 133 - 1), p, wpn, 0);
			x.DoSetLights(1);
		case 6:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(281 - 1, 133 - 1), p, wpn, 0);
			x.DoSetLights(1); 
		case 5:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(280 - 1, 133 - 1), p, wpn, 0);
			x.DoSetLights(1);
		case 4:
			TethysGame::CreateUnit(x, mapLynx, LOCATION(283 - 1, 132 - 1), p, mapStarflare, 0);
			x.DoSetLights(1);
		case 3:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(282 - 1, 132 - 1), p, mapAgridome, 0);
			x.DoSetLights(1);
		case 2:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(281 - 1, 132 - 1), p, mapUniversity, 0);
			x.DoSetLights(1);
		case 1:
			TethysGame::CreateUnit(x, mapConVec, LOCATION(280 - 1, 132 - 1), p, mapNursery, 0);
			x.DoSetLights(1); 
		default:
			break;
	}

	// Auto-movement
	PlayerVehicleEnum mover(p);
	while (mover.GetNext(x))
	{
		x.DoMove(LOCATION(310 - 1, 91 - 1));
	}

	// For reference
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(268 - 1, 120 - 1), aiNum, mapNone, 0);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(264 - 1, 123 - 1), aiNum, mapNone, 0);
	x.SetDamage(250);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(264 - 1, 127 - 1), aiNum, mapNone, 0);
	x.SetDamage(500);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(268 - 1, 131 - 1), aiNum, mapNone, 0);
	x.SetDamage(750);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(272 - 1, 131 - 1), aiNum, mapNone, 0);
	x.SetDamage(1000);
	//TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(276 - 1, 134 - 1), aiNum, mapNone, 0);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(278 - 1, 136 - 1), aiNum, mapAdvancedLab, 3);
	x.DoBuild(mapAdvancedLab, LOCATION(278 - 1, 136 - 1));
	//TethysGame::CreateUnit(x, mapLynx, LOCATION(268 - 1, 118 - 1), p, mapStarflare, 0);

}