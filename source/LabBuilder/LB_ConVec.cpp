#include "LabBuilder\LabBuilder.h"
#include "LabBuilder\LB_ConVec.h"

ConVec::ConVec(UnitEx id, LabBuilder *hostAI, bool forDebug)
{
	CV = id;
	ai = hostAI;
	currentLab.unitID = 0;
	deployAt = CV.Location();
	labsBuilt = 0;
	numFailedAttempts = 0;
	prevAct = moInvalid;
	prevCmd = ctInvalidCommand;
	lastCmdTime = 0;
	lastActTime = 0;
	debug = forDebug;
}

ConVec::~ConVec()
{
	//
}

void ConVec::CheckStatus()
{
	// Short circuit for "disabled" debug ConVecs
	if (debug && !CV.GetLights())
	{
		return;
	}

	ActionType curAction = CV.GetCurAction();
	CommandType curCommand = CV.GetLastCommand();

	// A "done" action just means the unit has finished its previous action, which could've been building a lab, moving, or recovering from EMP.
	// By looking at the ConVec's cargo, we can get a better idea of it's actual condition.
	if (curAction == moDone)
	{
		// If ConVec is empty, it means it successfully deployed a lab.
		if (CV.GetCargo() == mapNone)
		{
			// Re-enable invincibility
			OP2Unit *internalUnit = &(*unitArray)[CV.unitID];
			internalUnit->flags &= ~UNIT_CANBEDAMAGED;

			// Update our lab pointer if we haven't already.
			if (currentLab.unitID == 0)
			{
				Unit labCandidate;
				labCandidate.unitID = GameMapEx::GetTileEx(LOCATION(CV.Location().x - 1, CV.Location().y - 1)).unitIndex;

				// Make sure this is actually a live Advanced Lab owned by the AI player.
				if (labCandidate.unitID != 0 &&
					labCandidate.IsLive() &&
					(labCandidate.OwnerID() == CV.OwnerID() || debug) &&
					labCandidate.GetType() == mapAdvancedLab)
				{
					currentLab.unitID = labCandidate.unitID;
					ai->AddLab(currentLab);
				}
			}

			// Find a new location to build at.
			deployAt = GetNextLabSpot(deployAt);

			// If unable to find a spot for a new lab, self-destruct this ConVec and the last lab it built.
			if (deployAt.x == -1)
			{
				CV.DoSelfDestruct();
				currentLab.DoDeath();
			}
			else
			{
				// Reload the ConVec and issue the build order.
				CV.SetCargo(mapAdvancedLab, mapNone);
				CV.DoBuild(mapAdvancedLab, deployAt);

				// Automatically damage the recently-finished lab, destroying it if it would have 0 HP left.
				int labMaxHP = currentLab.GetUnitInfo().GetHitPoints(CV.OwnerID());
				currentLab.SetDamage(currentLab.GetDamage() + (labMaxHP * ((float)labsBuilt / ai->GetMaxLabsPerConVec())));
				if (currentLab.GetDamage() >= labMaxHP)
				{
					#ifdef _DEBUG
					TethysGame::AddMessage(currentLab, "Damage limit reached", -1, sndBeep5);
					#endif

					CV.DoSelfDestruct();
					currentLab.DoDeath();
				}
				labsBuilt++;

				// Clear the ConVec's lab pointer.
				currentLab.unitID = 0;

				// Reset the failed attempts counter.
				numFailedAttempts = 0;
			}
		}

		// Previous action completed, but we still have an advanced lab loaded.  Presumably the "action" completed was recovering from EMP or something.
		// We also check if the current command is a build order.  This fixes two edge cases that were causing false positives (ConVecs re-orienting after reaching the deploy spot, ConVecs still having the lab as cargo for one frame after construction begins).
		else if (curCommand != ctMoBuild)
		{
			// If build location is blocked, find a new one.
			if (!ai->CheckLabPlacement(deployAt))
			{
				#ifdef _DEBUG
				TethysGame::AddMessage(CV, "Lab deployment blocked.", -1, sndBeep5);
				#endif

				numFailedAttempts++;

				// Find a new location to build at.
				deployAt = GetNextLabSpot(CV.Location());

				// If unable to find a spot for a new lab, self-destruct this ConVec and the last lab it built.
				if (deployAt.x == -1)
				{
					CV.DoSelfDestruct();
					currentLab.DoDeath();
				}
			}
			// Resume course to the deploy location
			CV.DoBuild(mapAdvancedLab, deployAt);
		}
	}

	// Check if we should update the previous action/command/time.
	if (prevAct != curAction)
	{
		prevAct = curAction;
		lastActTime = TethysGame::Tick();
	}
	
	if (prevCmd != curCommand)
	{
		prevCmd = curCommand;
		lastCmdTime = TethysGame::Tick();
	}

	// Self destruct the ConVec and the last lab it built after an arbitrary number of failures.
	if (numFailedAttempts > 12)
	{
		CV.DoSelfDestruct();
		currentLab.DoDeath();
	}
}

LOCATION ConVec::GetNextLabSpot(LOCATION searchFrom)
{
	// Pick a random direction (0 = east, 1 = southeast, ... 7 = northeast)
	int dir = TethysGame::GetRand(8);
	int origDir = dir;
	int attempts = 0;
	bool keepGoing = true;
	LOCATION toTest;
	while (keepGoing)
	{
		// Check lab placement in the current direction
		switch (dir)
		{
		// East
		case 0:
			toTest = LOCATION(searchFrom.x + 4 + attempts, searchFrom.y);
			break;
		// Southeast
		case 1:
			toTest = LOCATION(searchFrom.x + 4 + attempts, searchFrom.y + 4 + attempts);
			break;
		// South
		case 2:
			toTest = LOCATION(searchFrom.x, searchFrom.y + 4 + attempts);
			break;
		// Southwest
		case 3:
			toTest = LOCATION(searchFrom.x - 4 - attempts, searchFrom.y + 4 + attempts);
			break;
		// West
		case 4:
			toTest = LOCATION(searchFrom.x - 4 - attempts, searchFrom.y);
			break;
		// Northwest
		case 5:
			toTest = LOCATION(searchFrom.x - 4 - attempts, searchFrom.y - 4 - attempts);
			break;
		// North
		case 6:
			toTest = LOCATION(searchFrom.x, searchFrom.y - 4 - attempts);
			break;
		// Northeast
		case 7:
			toTest = LOCATION(searchFrom.x + 4 + attempts, searchFrom.y - 4 - attempts);
			break;
		}

		if (ai->CheckLabPlacement(toTest))
		{
			return toTest;
		}

		// Update the direction to check next
		dir++;
		dir %= 8;
		if (dir == origDir)
		{
			if (attempts++ > 2)
			{
				keepGoing = false;
				toTest = LOCATION(-1, -1);
			}
		}
	}
	return toTest;
}
