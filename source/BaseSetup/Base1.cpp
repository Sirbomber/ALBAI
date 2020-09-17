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

	if (Player[p].Difficulty() == 0)
	{
		TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(271 - 1, 120 - 1), p, mapNone, 0);
		x.DoSetLights(1);
	}

	// Initial resources
	DoInitRes(p);

	// Initial vehicles
	DoInitVehicles(p, 280, 132);

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