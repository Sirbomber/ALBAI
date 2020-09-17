// Class definition file for lab-builder AI ConVecs

#pragma once

#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>

class LabBuilder;

class ConVec
{
public:
	ConVec(UnitEx id, LabBuilder *hostAI, bool forDebug = false);	// Call this after creating a new AI ConVec.  Setting the forDebug flag allows other players to own the ConVec, but the AI will still issue orders to it and treat labs built by it as its own.  The AI will ignore debug ConVecs if their lights are turned off.
	~ConVec();

	// Lab builder ConVec status update cycle - called every few ticks to give the ConVec new orders.
	void CheckStatus();

	UnitEx GetHandle() { return CV; }
	bool IsDebug() { return debug; }

	bool operator <(const ConVec& B) { return (this->CV.unitID < B.CV.unitID); }

private:
	LOCATION GetNextLabSpot(LOCATION searchFrom);

	LabBuilder *ai;		// Pointer to overseer class
	UnitEx CV;			// ConVec unit handle

	// Member variables related to Advanced Lab construction (and demolition)
	LOCATION deployAt;
	UnitEx currentLab;
	int labsBuilt;
	int lastDir;	// ConVecs should build in a straight line (30% chance they change direction)

	// Member variables related to adapting to failed build attempts.
	int numFailedAttempts;
	ActionType prevAct;
	CommandType prevCmd;
	int lastCmdTime,
		lastActTime;

	// Etc.
	bool debug;		// If true, don't remove from ConVec list even if not owned by AI player
};
