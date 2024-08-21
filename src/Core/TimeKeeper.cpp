
#include "TimeKeeper.h"

namespace Smp2Simulator
{
namespace Core
{

// Set simulation time
void TimeKeeper::SetSimulationTime(Smp::Duration simulationTime)
{
    this->simulationTime = simulationTime;
}

// Return simulation time
Smp::Duration TimeKeeper::GetSimulationTime()
{
    return this->simulationTime;
}

// Return Epoch time
// Epoch time is an absolute time with a fixed offset to simulation time
Smp::DateTime TimeKeeper::GetEpochTime()
{
    return this->simulationTime + this->offsetEpochTime;
}

// Return Mission time
// Mission time is a relative time with a fixed offset to epoch time
Smp::Duration TimeKeeper::GetMissionTime()
{
    return this->GetEpochTime() + this->offsetMissionTime;
}

// Return Zulu time
// Zulu time is a system dependent time and not related to simulation time
Smp::DateTime TimeKeeper::GetZuluTime()
{
    // NOT IMPLEMENTED
    return 0;
}

// Set Epoch time
void TimeKeeper::SetEpochTime(Smp::DateTime epochTime)
{
    this->offsetEpochTime = epochTime;
}

// Set Mission start
void TimeKeeper::SetMissionStart(Smp::DateTime missionStart)
{
    this->offsetMissionTime = missionStart;
}

// Set Mission time
void TimeKeeper::SetMissionTime(Smp::Duration missionTime)
{
    this->offsetMissionTime = missionTime;
}

}
}
