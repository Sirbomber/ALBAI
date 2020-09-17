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

	if (Player[p].Difficulty() == 0)
	{
		TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(253 - 1, 146 - 1), p, mapNone, 2);
		x.DoSetLights(1);
	}

	// Initial resources
	DoInitRes(p);

	// Initial vehicles
	DoInitVehicles(p, 240, 147);

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