#include <windows.h>

#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <Patches.h>

#include "Globals.h"
#include "LabBuilder\LabBuilder.h"

#include "Bases.h"
#include "DisasterCreator\DisasterCreator.h"

#include <windows.h>
#include <winuser.h>
#include <vfw.h>
#include "OP2App/CConfig.h"
#include "OP2Types/OP2Game.h"
#include "OP2App/ResManager.h"
#include "OP2App/TApp.h"

HINSTANCE hInstDLL = NULL;

ExportLevelDetails("5P, SRV, 'Research & Development'", "newworld.map", "survtech.txt", MultiSpaceRace, 5)
Export int DescBlockEx[] = { 1, 0, 0, 0, 0, 0, 0, 0 };

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		if (HFLInit() == HFLCANTINIT
			|| !SetMissionEndHook(true, MissionEnd)
			|| !SetNukePatch(true))
		{
			return false;
		}

		DisableThreadLibraryCalls(hinstDLL);
		g_hInst = hInstDLL = hinstDLL;				// This needs to get set for cutscenes to properly blank out the rest of the window at mission end.
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		// Unlock Dans_RULE_UIFrame (locked by PlayAvi)
		LockWindowUpdate(NULL);

		HFLCleanup();
		SetMissionEndHook(false, NULL);
		SetNukePatch(false);
	}

	return TRUE;
}

void DoRandomBases(int aiNum)
{
	int i[5] = { 0, 1, 2, 3, 4 };
	RandomizeList(autosize(i));

	// Create bases - check to make sure owner is active first!
	if (Player[i[0]].IsHuman())
	{
		SetupBase1(i[0], aiNum);
	}

	if (Player[i[1]].IsHuman())
	{
		SetupBase2(i[1], aiNum);
	}

	if (Player[i[2]].IsHuman())
	{
		SetupBase3(i[2], aiNum);
	}
	
	if (Player[i[3]].IsHuman())
	{
		SetupBase4(i[3], aiNum);
	}
	
	if (Player[i[4]].IsHuman())
	{
		SetupBase5(i[4], aiNum);
	}

}

LabBuilder LB;
DisasterCreator DC;
Export int InitProc()
{
	// Determine AI player number
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		if (!Player[i].IsHuman())
		{
			LB.SetPlayerNum(i);
			Player[i].SetTechLevel(13);
			break;
		}
	}

	// Setup alliances
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		for (int j = 0; j < TethysGame::NoPlayers(); j++)
		{
			if (Player[i].IsHuman() && Player[j].IsHuman() && i != j)
			{
				Player[i].AllyWith(j);
			}
		}
	}

	LB.AnalyzeMap();

#ifndef _DEBUG
	
	// Player base setup
	DoRandomBases(LB.GetPlayerNum());
	CreateTimeTrigger(1, 1, 399, "BlowIntroLabs");
	CreateCountTrigger(1, 0, -1, mapConVec, mapAtheistBuildingExplosion, 1, cmpGreaterEqual, "NoFun");
	DoQuickTestOre();

	// ** TESTING  - Test base placements + additional ConVecs.  Comment out/remove for actual release build! **
	/*
	SetupBase1(0, LB.GetPlayerNum());
	Player[0].GoEden();
	SetupBase2(0, LB.GetPlayerNum());
	Player[0].GoPlymouth();
	SetupBase3(0, LB.GetPlayerNum());
	Player[0].GoEden();
	SetupBase4(0, LB.GetPlayerNum());
	Player[0].GoPlymouth();
	SetupBase5(0, LB.GetPlayerNum());
	Player[0].GoEden();

	Unit x;
	map_id testkits[] = { mapCommandCenter,mapStructureFactory,mapCommonOreSmelter,mapTokamak,mapAgridome,mapMagmaWell };
	for (int i = 0; i < 6; i++)
	{
		TethysGame::CreateUnit(x, mapConVec, LOCATION(253 + i, 123), 0, mapAdvancedLab, 0);
		x.DoSetLights(1);
		TethysGame::CreateUnit(x, mapConVec, LOCATION(253 + i, 124), 0, testkits[i], 0);
		x.DoSetLights(1);
	}
	*/

	// Morale
	TethysGame::ForceMoraleGood(-1);
	if (TethysGame::UsesMorale())
	{
		CreateTimeTrigger(1, 1, 18005, "FreeMorale");
	}

	// Day/night cycle
	TethysGame::SetDaylightEverywhere(1);
	if (TethysGame::UsesDayNight())
	{
		TethysGame::SetDaylightEverywhere(0);
		GameMap::SetInitialLightLevel(198);
		TethysGame::SetDaylightMoves(1);
	}

	// Disasters
	if (TethysGame::CanHaveDisasters())
	{
		DC.SetMapSize(512, 256);
		CreateTimeTrigger(1, 1,  5000, "FirstDisasters");
		CreateTimeTrigger(1, 1, 12000, "SecondDisasters");
		CreateTimeTrigger(1, 1, 18000, "ThirdDisasters");
		CreateTimeTrigger(1, 1, 24000, "FourthDisasters");
		CreateTimeTrigger(1, 1, 32000, "FifthDisasters");
		CreateTimeTrigger(1, 1, 44000, "SixthDisasters");
		CreateTimeTrigger(1, 1, 60000, "FinalDisasters");
		CreateTimeTrigger(1, 1, 100000, "Doomsday");
	}

	// AI progression
	CreateTimeTrigger(1, 1, 3400, "Labs1");
	CreateTimeTrigger(1, 1, 8900, "Labs2");
	CreateTimeTrigger(1, 1, 15000, "Labs3");
	CreateTimeTrigger(1, 1, 22000, "Labs4");
	CreateTimeTrigger(1, 1, 29000, "Labs5");
	CreateTimeTrigger(1, 1, 35000, "Labs6");
	CreateTimeTrigger(1, 1, 41000, "Labs7");
	CreateTimeTrigger(1, 1, 60000, "LabsFinal");

#else
		TethysGame::ForceMoraleGreat(-1);
		CreateCountTrigger(1, 0, -1, mapConVec, mapAtheistBuildingExplosion, 1, cmpGreaterEqual, "NoFun");

		UnitEx Unit1,
			COS, COM, ROS, ROM;
		Player[0].CenterViewOn(107 - 1, 100 - 1);
		Player[0].GoEden();
		Player[0].SetWorkers(60);
		Player[0].SetScientists(45);
		Player[0].SetKids(35);
		Player[0].SetFoodStored(20000);
		Player[0].SetTechLevel(13);

		TethysGame::CreateBeacon(mapMiningBeacon, 114 - 1, 106 - 1, 0, 0, 0);
		TethysGame::CreateBeacon(mapMiningBeacon, 94 - 1, 112 - 1, 1, 0, 0);
		TethysGame::CreateBeacon(mapFumarole, 122 - 1, 91 - 1, -1, -1, -1);

		TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(107 - 1, 100 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(COM, mapCommonOreMine, LOCATION(115 - 1, 106 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapGeothermalPlant, LOCATION(122 - 1, 91 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(111 - 1, 100 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(111 - 1, 97 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(107 - 1, 94 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(111 - 1, 94 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapBasicLab, LOCATION(115 - 1, 100 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(115 - 1, 97 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(104 - 1, 94 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(115 - 1, 94 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(COS, mapCommonOreSmelter, LOCATION(111 - 1, 103 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapCommonOreSmelter, LOCATION(111 - 1, 107 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapCommonOreSmelter, LOCATION(116 - 1, 103 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(106 - 1, 103 - 1), 0, mapNone, 0);
		Unit1.SetFactoryCargo(0, mapAtheistBuildingExplosion, mapNone);
		TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(106 - 1, 107 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(107 - 1, 97 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapNursery, LOCATION(104 - 1, 100 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapUniversity, LOCATION(104 - 1, 97 - 1), 0, mapNone, 0);

		CreateTubeOrWallLine(101 - 1, 111 - 1, 119 - 1, 111 - 1, mapWall);
		CreateTubeOrWallLine(83 - 1, 97- 1, 83 - 1, 117 - 1, mapWall);
		CreateTubeOrWallLine(86 - 1, 96 - 1, 99 - 1, 96 - 1, mapWall);
		CreateTubeOrWallLine(120 - 1, 94 - 1, 120 - 1, 108 - 1, mapWall);
		CreateTubeOrWallLine(100 - 1, 94 - 1, 100 - 1, 90 - 1, mapWall);
		CreateTubeOrWallLine(103 - 1, 90 - 1, 117 - 1, 90 - 1, mapWall);
		CreateTubeOrWallLine(85 - 1, 117 - 1, 98 - 1, 117 - 1, mapWall);
		CreateTubeOrWallLine(99 - 1, 109 - 1, 99 - 1, 115 - 1, mapWall);
		CreateTubeOrWallLine(98 - 1, 105 - 1, 98 - 1,  98 - 1, mapWall);

		Player[0].SetOre(14000);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(107 - 1, 104 - 1), 0, mapNone, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(107 - 1, 105 - 1), 0, mapNone, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(107 - 1, 106 - 1), 0, mapNone, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(116 - 1, 101 - 1), 0, mapNone, 3);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(113 - 1, 106 - 1), 0, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(COM, COS);
		//Unit1.SetTruckCargo(truckCommonMetal, 2000);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(113 - 1, 107 - 1), 0, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(COM, COS);
		//Unit1.SetTruckCargo(truckCommonMetal, 2000);
		TethysGame::CreateUnit(Unit1, mapRoboMiner, LOCATION(118 - 1, 102 - 1), 0, mapNone, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapRoboSurveyor, LOCATION(118 - 1, 103 - 1), 0, mapNone, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(118 - 1, 104 - 1), 0, mapNone, 0);
		Unit1.DoSetLights(1);

		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(98 - 1, 98 - 1), 0, mapEMP, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(99 - 1, 98 - 1), 0, mapRPG, 0);
		OP2Unit *internalUnit;
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;

		Unit1.DoSetLights(1);

		TethysGame::CreateUnit(ROS, mapRareOreSmelter, LOCATION(90 - 1, 109 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapRareOreSmelter, LOCATION(95 - 1, 109 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(Unit1, mapRareOreSmelter, LOCATION(90 - 1, 113 - 1), 0, mapNone, 0);
		TethysGame::CreateUnit(ROM, mapCommonOreMine, LOCATION(94 - 1, 112 - 1), 0, mapNone, 0);
		CreateTubeOrWallLine(91 - 1, 107 - 1, 103 - 1, 104 - 1, mapTube);
		CreateTubeOrWallLine(90 - 1, 104 - 1, 91 - 1, 106 - 1, mapTube);
		Player[0].SetRareOre(12000);

		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(91 - 1, 111 - 1), 0, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(ROM, ROS);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(92 - 1, 111 - 1), 0, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(ROM, ROS);


		TethysGame::CreateUnit(Unit1, mapSpaceport, LOCATION(90 - 1, 101 - 1), 0, mapNone, 0);
		Unit1.SetFactoryCargo(0, mapHabitatRing, mapNone);
		Unit1.SetFactoryCargo(1, mapStasisSystems, mapNone);
		Unit1.SetFactoryCargo(2, mapIonDriveModule, mapNone);
		Unit1.SetFactoryCargo(3, mapCommonMetalsCargo, mapNone);
		Unit1.SetFactoryCargo(4, mapRareMetalsCargo, mapNone);
		ExtPlayer[0].SetSatelliteCount(mapSolarSatellite, 3);
		ExtPlayer[0].SetSatelliteCount(mapEDWARDSatellite, 1);
		ExtPlayer[0].SetSatelliteCount(mapSkydock, 1);
		ExtPlayer[0].SetSatelliteCount(mapFuelingSystems, 1);
		
		LB.SetSpawnDelay(600);
		LB.SetDetonationDelay(100);
		//LB.SetSpawnDelay(500);
		//LB.SetDetonationDelay(2500);
		//LB.SetSpawnCount(TethysGame::NoPlayers() + 1);
		LB.SetSpawnCount(10);
		LB.SetConVecStats(1, 16, 24);
		LB.SetAdvancedLabStats(800);
		CreateTimeTrigger(1, 0, 4, "LB_UpdateCycle");

		// Debug ConVec
		LB.CreateDebugConVec(LOCATION(108 - 1, 86 - 1));
#endif

	// Victory/Defeat conditions
	SetupVictory();

	// The all-important playlist
	SongIds BoomBoomBoomBoom[] = { songEP62, songStatic01, songPlymth12, songStatic05, songPlymth11, songEden21, songEden22, songEP42, songEP51, songEP52, songEP63, songEP61, songEden22 };
	TethysGame::SetMusicPlayList(13, 0, BoomBoomBoomBoom);

	// Enable DIRT Repair
	CreateTimeTrigger(1, 0, 25, "DirtRepairProc");

	return 1;
}

Export void DisasterCreator_Callback()
{
	DC.RollRandom();
	//DC.CheckVolcanoes();
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

Export void FreeMorale()
{
	TethysGame::FreeMoraleLevel(-1);
}

void DoQuickTestOre()
{
	// Common Ore Mines
	TethysGame::CreateBeacon(mapMiningBeacon, 366, 239, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 288, 165, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 215, 162, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 149, 249, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 335, 175, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 166, 172, 0, 0, -1);

	TethysGame::CreateBeacon(mapMiningBeacon, 35 - 1, 170 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 52 - 1, 244 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 156 - 1, 125 - 1, 0, 0, -1);
	//TethysGame::CreateBeacon(mapMiningBeacon, 252-1, 127-1, 0,  0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 256 - 1, 70 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 338 - 1, 109 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 412 - 1, 213 - 1, 0, 0, -1);

	TethysGame::CreateBeacon(mapMiningBeacon, 460, 130, 0, 0, -1);

	TethysGame::CreateBeacon(mapMiningBeacon, 51 - 1, 207 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 82 - 1, 83 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 90 - 1, 183 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 102 - 1, 126 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 115 - 1, 44 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 119 - 1, 166 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 174 - 1, 113 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 202 - 1, 87 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 241 - 1, 37 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 295 - 1, 79 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 341 - 1, 128 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 371 - 1, 43 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 388 - 1, 181 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 402 - 1, 124 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 442 - 1, 63 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 443 - 1, 178 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 447 - 1, 224 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 503 - 1, 58 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 510 - 1, 201 - 1, 0, 1, -1);

	TethysGame::CreateBeacon(mapMiningBeacon, 24 - 1, 250 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 29 - 1, 17 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 85 - 1, 21 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 132 - 1, 16 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 217 - 1, 13 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 276 - 1, 18 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 338 - 1, 18 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 401 - 1, 29 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 475 - 1, 20 - 1, 0, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 486 - 1, 240 - 1, 0, 2, -1);

	// Rare Ore Mines
	TethysGame::CreateBeacon(mapMiningBeacon, 312 - 1, 203 - 1, 1, -1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 203 - 1, 200 - 1, 1, -1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 260 - 1, 245 - 1, 1, 1, -1);

	TethysGame::CreateBeacon(mapMiningBeacon, 22, 131, 1, 0, -1);

	TethysGame::CreateBeacon(mapMiningBeacon, 35 - 1, 174 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 50 - 1, 230 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 168 - 1, 127 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 245 - 1, 54 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 258 - 1, 127 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 352 - 1, 111 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 418 - 1, 213 - 1, 1, 1, -1);

	TethysGame::CreateBeacon(mapMiningBeacon, 16 - 1, 31 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 18 - 1, 234 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 35 - 1, 211 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 64 - 1, 73 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 76 - 1, 171 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 99 - 1, 8 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 117 - 1, 125 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 126 - 1, 151 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 134 - 1, 28 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 144 - 1, 207 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 160 - 1, 104 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 188 - 1, 73 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 230 - 1, 28 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 258 - 1, 163 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 262 - 1, 26 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 313 - 1, 73 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 347 - 1, 209 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 354 - 1, 8 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 360 - 1, 131 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 388 - 1, 28 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 389 - 1, 163 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 416 - 1, 124 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 420 - 1, 71 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 445 - 1, 169 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 491 - 1, 216 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 492 - 1, 8 - 1, 1, 2, -1);


	// Random Mines


	// Fumaroles
	TethysGame::CreateBeacon(mapFumarole, 377 - 1, 249 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 463 - 1, 225 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 100 - 1, 252 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 123 - 1, 247 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 6 - 1, 222 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 40 - 1, 107 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 384 - 1, 148 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 59 - 1, 151 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 63 - 1, 7 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 149 - 1, 30 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 5 - 1, 9 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 355 - 1, 39 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 239 - 1, 7 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 410 - 1, 95 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 314 - 1, 93 - 1, -1, -1, -1);

	// Magma Vents
	TethysGame::CreateBeacon(mapMagmaVent, 88 - 1, 150 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 413 - 1, 150 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 403 - 1, 247 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 381 - 1, 224 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 103 - 1, 226 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 4 - 1, 238 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 431 - 1, 149 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 495 - 1, 172 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 104 - 1, 26 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 246 - 1, 13 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 383 - 1, 12 - 1, -1, -1, -1);


}

void SetupVictory()
{
	Trigger Skydock,
		IonDriv,
		FusDriv,
		FuelSys,
		CommMod,
		HabRing,
		SnsPack,
		StasSys,
		OrbPack,
		PhnxMod,
		ComCarg,
		RarCarg,
		FodCarg,
		EvacMod,

		Defeat;

	// Evacuation Module
	EvacMod = CreateCountTrigger(1, 1, -1, mapEvacuationModule, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, EvacMod, "Evacuate 200 colonists to the starship.");

	// Food Cargo
	FodCarg = CreateCountTrigger(1, 0, -1, mapFoodCargo, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, FodCarg, "Evacuate 10000 units of food to the starship.");

	// Rare Metals Cargo
	RarCarg = CreateCountTrigger(1, 0, -1, mapRareMetalsCargo, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, RarCarg, "Evacuate 10000 units of Rare Metals to the starship.");

	// Common Metals Cargo
	ComCarg = CreateCountTrigger(1, 0, -1, mapCommonMetalsCargo, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, ComCarg, "Evacuate 10000 units of Common Metals to the starship.");

	// Phoenix Module
	PhnxMod = CreateCountTrigger(1, 0, -1, mapPhoenixModule, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, PhnxMod, "Launch the Phoenix Module.");

	// Orbital Package
	OrbPack = CreateCountTrigger(1, 0, -1, mapOrbitalPackage, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, OrbPack, "Launch the Orbital Package.");

	// Stasis Systems
	StasSys = CreateCountTrigger(1, 0, -1, mapStasisSystems, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, StasSys, "Launch the Stasis Systems.");

	// Sensor Package
	SnsPack = CreateCountTrigger(1, 0, -1, mapSensorPackage, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, SnsPack, "Launch the Sensor Package.");

	// Habitat Ring
	HabRing = CreateCountTrigger(1, 0, -1, mapHabitatRing, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, HabRing, "Launch the Habitat Ring.");

	// Command Module
	CommMod = CreateCountTrigger(1, 0, -1, mapCommandModule, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, CommMod, "Launch the Command Module.");

	// Fueling Systems
	FuelSys = CreateCountTrigger(1, 0, -1, mapFuelingSystems, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, FuelSys, "Launch the Fueling Systems.");

	// Fusion Drive
	FusDriv = CreateCountTrigger(1, 0, -1, mapFusionDriveModule, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, FusDriv, "Launch the Fusion Drive Module.");

	// Ion Drive
	IonDriv = CreateCountTrigger(1, 0, -1, mapIonDriveModule, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, IonDriv, "Launch the Ion Drive Module.");

	// Skydock
	Skydock = CreateCountTrigger(1, 0, -1, mapSkydock, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, Skydock, "Place the Skydock in orbit.");

	// Defeat
	Trigger NoCCs[5], NoConVecs[5];
	int ai = -1;
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		if (!Player[i].IsHuman() && ai < 0)
		{
			ai = i;
		}
	}

	switch (ai)
	{
	case 5:
		NoCCs[4] = CreateCountTrigger(1, 0, 4, mapCommandCenter, mapNone, 0, cmpLowerEqual, "None");
		NoConVecs[4] = CreateCountTrigger(1, 0, 4, mapConVec, mapCommandCenter, 0, cmpLowerEqual, "None");
	case 4:
		NoCCs[3] = CreateCountTrigger(1, 0, 3, mapCommandCenter, mapNone, 0, cmpLowerEqual, "None");
		NoConVecs[3] = CreateCountTrigger(1, 0, 3, mapConVec, mapCommandCenter, 0, cmpLowerEqual, "None");
	case 3:
		NoCCs[2] = CreateCountTrigger(1, 0, 2, mapCommandCenter, mapNone, 0, cmpLowerEqual, "None");
		NoConVecs[2] = CreateCountTrigger(1, 0, 2, mapConVec, mapCommandCenter, 0, cmpLowerEqual, "None");
	case 2:
		NoCCs[1] = CreateCountTrigger(1, 0, 1, mapCommandCenter, mapNone, 0, cmpLowerEqual, "None");
		NoConVecs[1] = CreateCountTrigger(1, 0, 1, mapConVec, mapCommandCenter, 0, cmpLowerEqual, "None");
	case 1:
		NoCCs[0] = CreateCountTrigger(1, 0, 0, mapCommandCenter, mapNone, 0, cmpLowerEqual, "None");
		NoConVecs[0] = CreateCountTrigger(1, 0, 0, mapConVec, mapCommandCenter, 0, cmpLowerEqual, "None");
		break;
	default:
		TethysGame::AddMessage(-1, -1, "Error determining # of players", -1, -1);
		break;
	}

	switch (ai)
	{
	case 5:
		Defeat = CreateSetTrigger(1, 0, 10, 10, "None", NoCCs[0], NoCCs[1], NoCCs[2], NoCCs[3], NoCCs[4],
			NoConVecs[0], NoConVecs[1], NoConVecs[2], NoConVecs[3], NoConVecs[4]);
		break;
	case 4:
		Defeat = CreateSetTrigger(1, 0, 8, 8, "None", NoCCs[0], NoCCs[1], NoCCs[2], NoCCs[3],
			NoConVecs[0], NoConVecs[1], NoConVecs[2], NoConVecs[3]);
		break;
	case 3:
		Defeat = CreateSetTrigger(1, 0, 6, 6, "None", NoCCs[0], NoCCs[1], NoCCs[2],
			NoConVecs[0], NoConVecs[1], NoConVecs[2]);
		break;
	case 2:
		Defeat = CreateSetTrigger(1, 0, 4, 4, "None", NoCCs[0], NoCCs[1],
			NoConVecs[0], NoConVecs[1]);
		break;
	case 1:
		Defeat = CreateSetTrigger(1, 0, 2, 2, "None", NoCCs[0],
			NoConVecs[0]);
		break;
	}

	CreateFailureCondition(1, 0, Defeat, "No human players with CCs or ConVecs loaded with CC kits.");

}

void __cdecl MissionEnd() {
	static auto& gameTermReasons = reinterpret_cast<GameTermReasons&>(Op2Mem<OP2Game*>(0x56EA98)->gameTermReasons);

	if (gConfigFile.GetInt("Game", "ShowMovies", 1) != 0) {
		switch (gameTermReasons) {
		case GameTermReasons::MissionAccomplished:
			gameTermReasons = GameTermReasons::AutoDemo;  // Prevent the game from playing another cutscene after ours in SP
		case GameTermReasons::VictoryIsSweet:
			PlayAvi("MPF.AVI", true, "MEBL.AVI", 5000);
			break;
		case GameTermReasons::MissionFailed:
			gameTermReasons = GameTermReasons::AutoDemo;  // Prevent the game from playing another cutscene after ours in SP
		case GameTermReasons::YouHaveBeenDefeated:
			PlayAvi("IP.AVI", true, "MPBL.AVI", 7420);
			break;
		default:
			break;
		}
	}
}

Export void DirtRepairProc()
{
	return DirtRepair(3, 1000);
}

Export void FirstDisasters()
{
	DC.EnableDisaster(disStorm);
	DC.EnableDisaster(disMeteor);
	
	DC.SetMinimumWait(3700);
	DC.SetDisasterTypeWeight(disStorm, 65);
	DC.SetDisasterTypeWeight(disMeteor, 35);
	DC.SetDisasterTypeWeight(disNone, 10);
	DC.SetDisasterPowerWeight(pwrLow, 100);
	DC.SetDisasterTargetWeight(trgRandom, 30);
	DC.SetDisasterTargetWeight(trgPlayer, 70);
	DC.SetCallbackTrigger("DisasterCreator_Callback", 200);
}

Export void SecondDisasters()
{
	DC.EnableDisaster(disQuake);
	DC.SetDisasterTypeWeight(disQuake, 18);
	DC.SetDisasterTypeWeight(disStorm, 59);
	DC.SetDisasterTypeWeight(disMeteor, 18);
	DC.SetDisasterTypeWeight(disNone, 5);
	DC.SetDisasterPowerWeight(pwrLow, 80);
	DC.SetDisasterPowerWeight(pwrMedium, 20);
	DC.SetDisasterTargetWeight(trgRandom, 20);
	DC.SetDisasterTargetWeight(trgPlayer, 80);
	DC.SetMinimumWait(3400);
}

Export void ThirdDisasters()
{
	DC.SetDisasterTypeWeight(disQuake, 30);
	DC.SetDisasterTypeWeight(disStorm, 50);
	DC.SetDisasterTypeWeight(disMeteor, 20);
	DC.SetDisasterTypeWeight(disNone, 0);
	DC.SetDisasterPowerWeight(pwrLow, 65);
	DC.SetDisasterPowerWeight(pwrMedium, 30);
	DC.SetDisasterPowerWeight(pwrHigh, 5);
	DC.SetIgnoreChance(2);
}

Export void FourthDisasters()
{
	DC.EnableDisaster(disVortex);
	DC.SetDisasterTypeWeight(disQuake, 30);
	DC.SetDisasterTypeWeight(disStorm, 40);
	DC.SetDisasterTypeWeight(disVortex, 10);
	DC.SetDisasterTypeWeight(disMeteor, 20);
	DC.SetDisasterPowerWeight(pwrLow, 55);
	DC.SetDisasterPowerWeight(pwrMedium, 35);
	DC.SetDisasterPowerWeight(pwrHigh, 10);
	DC.SetDisasterTargetWeight(trgRandom, 10);
	DC.SetDisasterTargetWeight(trgPlayer, 90);
	DC.SetMinimumWait(3100);
}
Export void FifthDisasters()
{
	DC.SetDisasterTypeWeight(disQuake, 30);
	DC.SetDisasterTypeWeight(disStorm, 30);
	DC.SetDisasterTypeWeight(disVortex, 20);
	DC.SetDisasterTypeWeight(disMeteor, 20);
	DC.SetDisasterPowerWeight(pwrLow, 45);
	DC.SetDisasterPowerWeight(pwrMedium, 40);
	DC.SetDisasterPowerWeight(pwrHigh, 15);
}

Export void SixthDisasters()
{
	DC.SetDisasterPowerWeight(pwrLow, 30);
	DC.SetDisasterPowerWeight(pwrMedium, 45);
	DC.SetDisasterPowerWeight(pwrHigh, 20);
	DC.SetDisasterPowerWeight(pwrApocalyptic, 5);
	DC.SetMinimumWait(3000);
}

Export void FinalDisasters()
{
	DC.SetDisasterPowerWeight(pwrLow, 0);
	DC.SetDisasterPowerWeight(pwrMedium, 40);
	DC.SetDisasterPowerWeight(pwrHigh, 35);
	DC.SetDisasterPowerWeight(pwrApocalyptic, 25);
	DC.SetMinimumWait(2900);
	DC.SetIgnoreChance(7);
}

Export void Doomsday()
{
	DC.SetDisasterTypeWeight(disQuake, 50);
	DC.SetDisasterTypeWeight(disStorm, 0);
	DC.SetDisasterTypeWeight(disVortex, 50);
	DC.SetDisasterTypeWeight(disMeteor, 0);
	DC.SetDisasterPowerWeight(pwrLow, 0);
	DC.SetDisasterPowerWeight(pwrMedium, 0);
	DC.SetDisasterPowerWeight(pwrHigh, 0);
	DC.SetDisasterPowerWeight(pwrApocalyptic, 100);
	DC.SetDisasterTargetWeight(trgRandom, 0);
	DC.SetDisasterTargetWeight(trgPlayer, 100);
	DC.SetMinimumWait(1900);
	DC.SetIgnoreChance(30);
}

Export void Labs1()
{
	LB.SetConVecStats(1, 16, 24);
	LB.SetAdvancedLabStats(800);
	LB.SetSpawnDelay(2200);
	LB.SetDetonationDelay(2200);
	LB.SetSpawnCount(TethysGame::NoPlayers() + 1);
	CreateTimeTrigger(1, 0, 4, "LB_UpdateCycle");
}

Export void Labs2()
{
	LB.SetSpawnDelay(2000);
	LB.SetDetonationDelay(2000); 
}

Export void Labs3()
{
	LB.SetSpawnDelay(1700);
	LB.SetDetonationDelay(1700);
	LB.SetSpawnCount(TethysGame::NoPlayers() + 2);
}

Export void Labs4()
{
	LB.SetSpawnDelay(1500);
	LB.SetDetonationDelay(1400);
	LB.SetMaxLabsPerConVec(8);
	LB.SetConVecStats(1, 24, 20);
	LB.SetAdvancedLabStats(600);
}

Export void Labs5()
{
	LB.SetSpawnDelay(1200);
	LB.SetDetonationDelay(1000);
	LB.SetSpawnCount(TethysGame::NoPlayers() + 4);
	LB.SetAdvancedLabStats(600);
}

Export void Labs6()
{
	LB.SetSpawnDelay(1100);
	LB.SetDetonationDelay(800);
	LB.SetMaxLabsPerConVec(10);
}

Export void Labs7()
{
	LB.SetSpawnDelay(900);
	LB.SetDetonationDelay(700);
	LB.SetSpawnCount(TethysGame::NoPlayers() + 8);
	LB.SetMaxLabsPerConVec(14);
}

Export void LabsFinal()
{
	LB.SetStructureBuildTime(mapMagmaWell, 200);
	LB.SetPayloadBuilding(mapMagmaWell);
	LB.SetSpawnDelay(200);
	LB.SetDetonationDelay(100);
	LB.SetMaxLabsPerConVec(18);
	LB.SetConVecStats(0, 32, 12);
}

Export void BlowIntroLabs()
{
	Unit x;
	
	LocationEnumerator P1Lab(LOCATION(268 - 1, 120 - 1));
	while (P1Lab.GetNext(x))
	{
		x.DoDeath();
	}

	LocationEnumerator P2Lab(LOCATION(263 - 1, 147 - 1));
	while (P2Lab.GetNext(x))
	{
		x.DoDeath();
	}

	LocationEnumerator P3Lab(LOCATION(267 - 1, 109 - 1));
	while (P3Lab.GetNext(x))
	{
		x.DoDeath();
	}
	
	LocationEnumerator P4Lab(LOCATION(237 - 1, 122 - 1));
	while (P4Lab.GetNext(x))
	{
		x.DoDeath();
	}

	LocationEnumerator P5Lab(LOCATION(220 - 1, 143 - 1));
	while (P5Lab.GetNext(x))
	{
		x.DoDeath();
	}
}

Export void NoFun()
{
	Unit Unit1;
	OP2Unit *internalUnit;

	internalUnit = &(*unitArray)[0];
	while (internalUnit->unitIndex != internalUnit->next->unitIndex)
	{
		internalUnit = internalUnit->next;
		Unit1.unitID = internalUnit->unitIndex;
		if (Unit1.GetType() == mapConVec && Unit1.GetCargo() == mapAtheistBuildingExplosion)
		{
			Unit1.SetCargo(mapNone, mapNone);
			return;
		}
	}
}
