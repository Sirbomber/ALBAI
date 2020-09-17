# Advanced Lab Bomb AI for Outpost 2
Outpost 2 "AI" players have always been hard-coded and inseparably tied to the mission script they were written for.  People have been dreaming of a general-purpose AI that can be dropped into any mission with ease.  Now, we need dream no longer!  The wait is over!

Code for the AI can be found in include/LabBuilder and source/LabBuilder.
All other files are only needed to build the sample mission.

To use ALBAI in your own missions, all you need to do is define a global LabBuilder variable, call the required initialization methods, define any parameters you want, and add a call to the LabBuilder UpdateCycle in AIProc.
Initialization methods:
 SetPlayerNum(AI Player Number (int)) - Required.  Tells the AI which player number it controls.  Must be between 0 and 6 (inclusive).
 AnalyzeMap() - Required.
 
Update methods:
 UpdateCycle(Current Game Tick (int)) - Invokes AI logic.  Must be called every few cycles if you want the AI to actually do anything.  It's recommended you put this in AIProc.
 
Parameters:
 SetSpawnDelay(Game Ticks Between Spawns (int)) - Required.  Sets how long the AI should wait between spawning ConVecs.
 SetSpawnCount(ConVecs to Spawn (int)) - Required.  Sets how many ConVecs the AI should spawn.
 SetDetonationDelay(Game Ticks Between Detonations (int)) - Required.  Sets how long the AI should wait between detonating Advanced Labs.  It's recommended lab detonations should be able to keep up with the spawn rate.
 SetMaxLabsPerConVec(Maximum Buildable Labs (int)) - Optional.  Sets how many labs a ConVec can build before it self-destructs and destroys the labs it built.  Default is 6.
 
 