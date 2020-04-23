#include "Bases.h"

void SetupBaseAI(int p)
{
	Unit x;
	Player[p].CenterViewOn(252+31, 180-1);

	map_id wpn = mapMicrowave;
	if (Player[p].IsEden())
	{
		wpn = mapLaser;
	}

	// Structures
	TethysGame::CreateUnit(x, mapCommandCenter, LOCATION(252+31,180-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStructureFactory, LOCATION(239+31,184-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapCommonOreSmelter, LOCATION(239+31,180-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(248+31,180-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAgridome, LOCATION(252+31,177-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(236+31,192-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(239+31,192-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapResidence, LOCATION(242+31,192-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapStandardLab, LOCATION(252+31,183-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapAdvancedLab, LOCATION(252+31,192-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapVehicleFactory, LOCATION(252+31,173-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(231+31,172-1), p, mapNone, 0);
	TethysGame::CreateUnit(x, mapTokamak, LOCATION(231+31,178-1), p, mapNone, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 239+31, 173-1, 0, 0, 0);
	TethysGame::CreateUnit(x, mapCommonOreMine, LOCATION(239+31,173-1), p, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(x, mapConVec, LOCATION(240+31, 186-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapConVec, LOCATION(243+31, 193-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(240+31, 176-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(241+31, 176-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapCargoTruck, LOCATION(243+31, 177-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapEarthworker, LOCATION(237+31, 189-1), p, mapNone, 4);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapRoboSurveyor, LOCATION(248+31, 185-1), p, mapNone, 5);
		x.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(242+31, 180-1, 246+31, 180-1, mapTube);
	CreateTubeOrWallLine(252+31, 185-1, 252+31, 190-1, mapTube);
	CreateTubeOrWallLine(239+31, 187-1, 239+31, 190-1, mapTube);

	// Walls
	CreateTubeOrWallLine(249+31, 189-1, 249+31, 195-1, mapWall);
	CreateTubeOrWallLine(255+31, 189-1, 255+31, 195-1, mapWall);
	CreateTubeOrWallLine(250+31, 195-1, 254+31, 195-1, mapWall);
	CreateTubeOrWallLine(250+31, 189-1, 251+31, 189-1, mapWall);
	CreateTubeOrWallLine(253+31, 189-1, 254+31, 189-1, mapWall);
	CreateTubeOrWallLine(228+31, 169-1, 233+31, 169-1, mapWall);
	CreateTubeOrWallLine(228+31, 170-1, 228+31, 173-1, mapWall);
	CreateTubeOrWallLine(228+31, 176-1, 228+31, 179-1, mapWall);

	// Initial resources
    Player[p].SetKids(41);
    Player[p].SetWorkers(37);
    Player[p].SetScientists(24);
    Player[p].SetOre(5300);
    Player[p].SetFoodStored(23400);

	// Initial tech
    Player[p].MarkResearchComplete(2701);
    Player[p].MarkResearchComplete(2702);
    Player[p].MarkResearchComplete(2703);
    Player[p].MarkResearchComplete(2704);
    Player[p].MarkResearchComplete(2705);
    Player[p].MarkResearchComplete(2707);
    Player[p].MarkResearchComplete(2708);
    Player[p].MarkResearchComplete(3401);        // Cybernetic Teleoperation
    Player[p].MarkResearchComplete(3406);        // Environmental Psychology
    Player[p].MarkResearchComplete(3303);        // Health Maintenance
    Player[p].MarkResearchComplete(3402);        // High-Temperature Superconductivity
    Player[p].MarkResearchComplete(3403);        // Hydroponic Growing Media
	if (Player[p].IsEden())
	{
		Player[p].MarkResearchComplete(3407);    // Large-Scale Optical Resonators
	}
	else
	{
		Player[p].MarkResearchComplete(3408);    // Focused Microwave Projection
	}
    Player[p].MarkResearchComplete(3405);        // Metallogeny
    Player[p].MarkResearchComplete(3304);        // Offspring Enhancement
    Player[p].MarkResearchComplete(3305);        // Research Training Programs
    Player[p].MarkResearchComplete(3201);        // Seismology
    Player[p].MarkResearchComplete(5309);        // Hypnopaedia
    Player[p].MarkResearchComplete(3851);        // Mobile Weapons Platform

	// Initial Vehicles
	TethysGame::CreateUnit(x, mapLynx, LOCATION(242+31, 179-1), p, wpn, 0);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapLynx, LOCATION(243+31, 179-1), p, wpn, 0);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapLynx, LOCATION(244+31, 179-1), p, wpn, 0);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapLynx, LOCATION(245+31, 179-1), p, wpn, 0);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapLynx, LOCATION(242+31, 180-1), p, wpn, 0);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapLynx, LOCATION(243+31, 180-1), p, wpn, 0);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapLynx, LOCATION(244+31, 180-1), p, wpn, 0);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapLynx, LOCATION(245+31, 180-1), p, wpn, 0);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapLynx, LOCATION(251+31, 187-1), p, wpn, 0);
		x.DoSetLights(1);
	TethysGame::CreateUnit(x, mapLynx, LOCATION(253+31, 187-1), p, wpn, 0);
		x.DoSetLights(1);
}