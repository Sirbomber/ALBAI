#include <windows.h>

#include <Outpost2DLL.h>
#include <HFL.h>

#include "Globals.h"
#include "LabBuilder\LabBuilder.h"

#include "Bases.h"
#include "DisasterCreator\DisasterCreator.h"

HINSTANCE hInstDLL = NULL;
/*
ExportLevelDetails("5P, SRV, 'Research & Development'", "Crossfire.map", "survtech.txt", MultiSpaceRace, 5)
Export int DescBlockEx[] = { 1, 0, 0, 0, 0, 0, 0, 0 };
*/
//ExportLevelDetails("5P, SRV, 'Research & Development'", "Crossfire.map", "survtech.txt", Colony, 6)
ExportLevelDetails("5P, SRV, 'Research & Development'", "newworld.map", "survtech.txt", Colony, 2)
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		HFLInit();

		DisableThreadLibraryCalls(hinstDLL);
		hInstDLL = hinstDLL;
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		// Unlock Dans_RULE_UIFrame (locked by PlayAvi)
		LockWindowUpdate(NULL);

		TethysGame::SetMicrobeSpreadSpeed(0);
	}

	return TRUE;
}
LabBuilder LB;
DisasterCreator DC;

Export int InitProc()
{
	// Determine AI player number
	for (int i = 0; i < 6; i++)
	{
		if (!Player[i].IsHuman())
		{
			LB.SetPlayerNum(i);
			break;
		}
	}

	LB.AnalyzeMap();
	//LB.SetSpawnDelay(3000);
	//LB.SetDetonationDelay(10000);
	LB.SetSpawnDelay(500);
	LB.SetDetonationDelay(2500);
	LB.SetSpawnCount(TethysGame::NoPlayers() + 1);
	CreateTimeTrigger(1, 0, 4, "LB_UpdateCycle");

	// Test - use morale steady setting later
	TethysGame::ForceMoraleGood(-1);

	Unit Unit1;
	Player[0].CenterViewOn(107 - 1, 100 - 1);
	Player[0].GoEden();
	Player[0].SetWorkers(30);
	Player[0].SetScientists(20);
	Player[0].SetFoodStored(10000);
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(107 - 1, 100 - 1), 0, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(104 - 1, 102 - 1), 0, mapStructureFactory, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(105 - 1, 102 - 1), 0, mapCommonOreSmelter, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(106 - 1, 102 - 1), 0, mapGeothermalPlant, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(107 - 1, 102 - 1), 0, mapAgridome, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(108 - 1, 102 - 1), 0, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.SetTruckCargo(truckCommonMetal, 2000);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(109 - 1, 102 - 1), 0, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.SetTruckCargo(truckCommonMetal, 2000);
	TethysGame::CreateUnit(Unit1, mapRoboMiner, LOCATION(110 - 1, 102 - 1), 0, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapRoboSurveyor, LOCATION(111 - 1, 102 - 1), 0, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(112 - 1, 102 - 1), 0, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateBeacon(mapMiningBeacon, 114 - 1, 106 - 1, 0, 0, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 94 - 1, 112 - 1, 1, 0, 0);

	// Due to Blight, day/night is required
	TethysGame::SetDaylightEverywhere(0);
	TethysGame::SetDaylightMoves(1);
	GameMap::SetInitialLightLevel(32);

	// Disasters - test values; change before release!
	DC.EnableDisaster(disQuake);
	DC.EnableDisaster(disStorm);
	DC.EnableDisaster(disVortex);
	DC.EnableDisaster(disMeteor);
	DC.SetMapSize(64, 64);
	DC.SetMinimumWait(3700);
	DC.SetDisasterTypeWeight(disQuake, 30);
	DC.SetDisasterTypeWeight(disStorm, 20);
	DC.SetDisasterTypeWeight(disVortex, 10);
	DC.SetDisasterTypeWeight(disMeteor, 40);
	DC.SetDisasterPowerWeight(pwrLow, 30);
	DC.SetDisasterPowerWeight(pwrMedium, 20);
	DC.SetDisasterPowerWeight(pwrHigh, 10);
	DC.SetDisasterPowerWeight(pwrApocalyptic, 1);
	DC.SetDisasterTargetWeight(trgPlayer, 100);
	DC.SetCallbackTrigger("DisasterCreator_Callback", 200);

	// The all-important playlist
	SongIds CCFSpecial[] = { songEP62, songStatic01, songPlymth12, songStatic05, songPlymth11, songEden21, songEden22, songEP42, songEP51, songEP52, songEP63, songEP61, songEden22 };
	TethysGame::SetMusicPlayList(13, 0, CCFSpecial);

	return 1; // return 1 if OK; 0 on failure
}

Export void DisasterCreator_Callback()
{
	DC.RollRandom();
	DC.CheckVolcanoes();
}

Export void AIProc() 
{
	//
}

void __cdecl GetSaveRegions(struct BufferDesc &bufDesc)
{
	bufDesc.bufferStart = 0;
	bufDesc.length = 0;
}

// NoResponseToTrigger
Export void None()
{
}

Export void LB_UpdateCycle()
{
	LB.UpdateCycle(TethysGame::Tick());
}
