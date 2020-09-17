#include "Bases.h"

void SetupBase4(int p, int aiNum)
{
	Unit x;
	Player[p].CenterViewOn(235 - 1, 108 - 1);

	// Structures
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(235 - 1, 108 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(235 - 1, 111 - 1), p, mapNone, 0);
	x.SetFactoryCargo(0, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(1, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(2, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(3, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(4, mapAtheistBuildingExplosion, mapNone);
	x.SetFactoryCargo(5, mapAtheistBuildingExplosion, mapNone);
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(235 - 1, 115 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(235 - 1, 105 - 1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(227 - 1, 104 - 1), p, mapNone, 0);

	TethysGame::CreateBeacon(mapMiningBeacon, 237 - 1, 119 - 1, 0, 1, 1);
	TethysGame::CreateUnit(x, mapCommonOreMine, LOCATION(237 - 1, 119 - 1), p, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(x, mapConVec, LOCATION(216 - 1, 117 - 1), p, mapCommandCenter, 4);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(224 - 1, 109 - 1), p, mapStructureFactory, 4);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(223 - 1, 117 - 1), p, mapCommonOreSmelter, 4);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(220 - 1, 105 - 1), p, mapTokamak, 3);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapConVec, LOCATION(221 - 1, 113 - 1), p, mapAgridome, 4);
	x.DoSetLights(1);

	if (Player[p].IsEden())
	{
		TethysGame::CreateUnit(x, mapConVec, LOCATION(226 - 1, 112 - 1), p, mapBasicLab, 4);
	}
	else
	{
		//TethysGame::CreateUnit(x, mapConVec, LOCATION(223 - 1, 112 - 1), p, mapBasicLab, 4);
		TethysGame::CreateUnit(x, mapConVec, LOCATION(226 - 1, 112 - 1), p, mapBasicLab, 4);
	}
	x.DoSetLights(1);
	if (Player[p].Difficulty() == 0)
	{
		x.SetCargo(mapStandardLab, mapNone);
	}

	TethysGame::CreateUnit(x, mapScout, LOCATION(229 - 1, 121 - 1), p, mapNone, 4);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(219 - 1, 118 - 1), p, mapNone, 4);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(227 - 1, 108 - 1), p, mapNone, 7);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(223 - 1, 107 - 1), p, mapNone, 3);
	x.DoSetLights(1);
	x.SetTruckCargo(truckFood, 1000);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(224 - 1, 105 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	x.SetTruckCargo(truckFood, 1000);

	if (Player[p].Difficulty() < 2)
	{
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(226 - 1, 106 - 1), p, mapNone, 5);
		x.DoSetLights(1);
		x.SetTruckCargo(truckFood, 1000);
	}

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(226 - 1, 116 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	x.SetTruckCargo(truckCommonMetal, 1000);

	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(226 - 1, 117 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	x.SetTruckCargo(truckCommonMetal, 1000);

	if (Player[p].Difficulty() == 0)
	{
		TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(227 - 1, 116 - 1), p, mapNone, 4);
		x.DoSetLights(1);
		x.SetTruckCargo(truckCommonMetal, 1000);
	}

	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(221 - 1, 124 - 1), p, mapNone, 3);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapRoboMiner, LOCATION(228 - 1, 120 - 1), p, mapNone, 4);
	x.DoSetLights(1);

	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(223 - 1, 121 - 1), p, mapNone, 4);
	x.DoSetLights(1);
	
	if (Player[p].Difficulty() == 0)
	{
		TethysGame::CreateUnit(x, mapEvacuationTransport, LOCATION(232 - 1, 109 - 1), p, mapNone, 4);
		x.DoSetLights(1);
	}

	// Initial resources
	DoInitRes(p);

	// Initial vehicles
	DoInitVehicles(p, 222, 111);

	// Auto-movement
	PlayerVehicleEnum mover(p);
	while (mover.GetNext(x))
	{
		x.DoMove(LOCATION(183 - 1, 105 - 1));
	}

	// For reference
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(237 - 1, 122 - 1), aiNum, mapNone, 0);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(233 - 1, 119 - 1), aiNum, mapNone, 0);
	x.SetDamage(250);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(230 - 1, 115 - 1), aiNum, mapNone, 0);
	x.SetDamage(500);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(230 - 1, 111 - 1), aiNum, mapNone, 0);
	x.SetDamage(750);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(231 - 1, 107 - 1), aiNum, mapNone, 0);
	x.SetDamage(1000);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(233 - 1, 105 - 1), aiNum, mapAdvancedLab, 3);
	x.DoBuild(mapAdvancedLab, LOCATION(233 - 1, 105 - 1));
	//TethysGame::CreateUnit(x, mapLynx, LOCATION(237 - 1, 124 - 1), p, mapStarflare, 0);
}