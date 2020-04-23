#include "LabBuilder\LabBuilder.h"
#include "LabBuilder\LB_ConVec.h"

ConVec::ConVec(UnitEx id, LabBuilder *hostAI)
{
	CV = id;
	ai = hostAI;
	currentLab.unitID = 0;
	deployAt = CV.Location();
}

ConVec::~ConVec()
{
	//
}

void ConVec::CheckStatus()
{
	ActionType curAction = CV.GetCurAction();
	CommandType lastCommand = CV.GetLastCommand();
	// Building a lab
	if (curAction == moObjFroze)
	{
		// Update our lab pointer if we haven't already.
		if (currentLab.unitID == 0)
		{
			currentLab.unitID = GameMapEx::GetTileEx(LOCATION(CV.Location().x - 1, CV.Location().y - 1)).unitIndex;
		}
	}
	// Finished building a lab
	else if (curAction == moDone)
	{
		// Make sure we're pointing to an actual unit, that it's still alive, and that it's an advanced lab.
		if (currentLab.unitID != 0 && currentLab.IsLive() && currentLab.GetType() == mapAdvancedLab)
		{
			ai->AddLab(currentLab);

			// Regardless of the result of the last check, clear this ConVec's lab pointer, reload the ConVec, find a new location to build, and start moving.
			int attempts = 0,
				firstDir = TethysGame::GetRand(4);
			switch (firstDir)
			{
			case 0:
				deployAt = LOCATION(deployAt.x, deployAt.y - 4);
				break;
			case 1:
				deployAt = LOCATION(deployAt.x + 4, deployAt.y);
				break;
			case 2:
				deployAt = LOCATION(deployAt.x, deployAt.y + 4);
				break;
			case 3:
				deployAt = LOCATION(deployAt.x - 4, deployAt.y);
				break;
			}
			CV.SetCargo(mapAdvancedLab, mapNone);
			CV.DoBuild(mapAdvancedLab, deployAt);
			currentLab.unitID = 0;
		}
	}
	int breakpoint = 0;
}