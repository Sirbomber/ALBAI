// Class definition file for lab-builder AI ConVecs

#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>

class LabBuilder;

class ConVec
{
public:
	ConVec(UnitEx id, LabBuilder *hostAI);
	~ConVec();

	void GetRandomLocation();
	void GetNearbyLabLocation();
	void CheckStatus();

	UnitEx CV;

private:
	void MoveToBuildPos();
	void BuildLab();

	LOCATION deployAt;
	int numFailedAttempts;
	UnitEx currentLab;
	LabBuilder *ai;
};
