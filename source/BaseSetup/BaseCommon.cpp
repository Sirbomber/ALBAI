#include "Bases.h"
#include "Globals.h"

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

void DoInitRes(int p)
{
	// Give the player a ton of people, who will all die because there aren't enough evacuation transports for them.
	
	Player[p].SetOre(3200);
	Player[p].SetFoodStored(12000);
	switch (Player[p].Difficulty())
	{
	case 0:
		// 20 kids, 30 workers, 25 scientists after colony destroyed (3 Evac Transports)
		Player[p].SetKids(37);
		Player[p].SetWorkers(50);
		Player[p].SetScientists(43);
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
		// 8 kids, 24 workers, 18 scientists after colony destroyed (2 Evac Transports)
		Player[p].SetKids(35);
		Player[p].SetWorkers(48);
		Player[p].SetScientists(47);
		Player[p].MarkResearchComplete(2703);
		Player[p].MarkResearchComplete(2704);
		Player[p].MarkResearchComplete(2707);
		Player[p].MarkResearchComplete(3304);
		break;
	case 2:
		// 12 kids, 21 workers, 17 scientists after colony destroyed (2 Evac Transports)
		Player[p].SetKids(35);
		Player[p].SetWorkers(45);
		Player[p].SetScientists(42);
		Player[p].MarkResearchComplete(3304);
		break;
	}
}

void DoInitVehicles(int p, int x, int y)
{
	Unit Unit1;
	map_id wpn = mapMicrowave;
	if (Player[p].IsEden())
	{
		wpn = mapLaser;
	}

	switch (TethysGame::InitialUnits())
	{
	case 12:
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(x + 2, y + 1), p, mapCommandCenter, 0);
		Unit1.DoSetLights(1);
	case 11:
		TethysGame::CreateUnit(Unit1, mapRoboMiner, LOCATION(x + 1, y + 1), p, mapNone, 0);
		Unit1.DoSetLights(1);
	case 10:
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(x, y + 1), p, mapNone, 0);
		Unit1.DoSetLights(1);
	case 9:
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(x - 1, y + 1), p, mapNone, 0);
		Unit1.DoSetLights(1);
	case 8:
		TethysGame::CreateUnit(Unit1, mapScout, LOCATION(x + 2, y), p, mapNone, 0);
		Unit1.DoSetLights(1);
	case 7:
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x + 1, y), p, wpn, 0);
		Unit1.DoSetLights(1);
	case 6:
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x, y), p, wpn, 0);
		Unit1.DoSetLights(1);
	case 5:
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x - 1, y), p, wpn, 0);
		Unit1.DoSetLights(1);
	case 4:
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x + 2, y - 1), p, mapStarflare, 0);
		Unit1.DoSetLights(1);
	case 3:
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(x + 1, y - 1), p, mapAgridome, 0);
		Unit1.DoSetLights(1);
	case 2:
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(x, y - 1), p, mapUniversity, 0);
		Unit1.DoSetLights(1);
	case 1:
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(x - 1, y - 1), p, mapNursery, 0);
		Unit1.DoSetLights(1);
	default:
		break;
	}
}