
#include "Smp/Services/ITimeKeeper.h"
#include "GenericComponent.h"


namespace Smp2Simulator
{
namespace Core
{

class TimeKeeper : public Smp::Services::ITimeKeeper, public GenericComponent
{

public:
    // Constructor
    TimeKeeper(Smp::String8 name = "TimeKeeper", Smp::String8 description = "") : GenericComponent(name, description)
    {
        this->simulationTime = 0;
        this->offsetEpochTime = 0;
        this->offsetMissionTime = 0;
    };

    // ITimeKeeper methods
    void SetSimulationTime(Smp::Duration simulationTime);
    Smp::Duration GetSimulationTime();
    Smp::DateTime GetEpochTime();
    Smp::Duration GetMissionTime();
    Smp::DateTime GetZuluTime();
    void SetEpochTime(Smp::DateTime epochTime);
    void SetMissionStart(Smp::DateTime missionStart);
    void SetMissionTime(Smp::Duration missionTime);

protected:
    // Attributes
    Smp::Duration simulationTime;
    Smp::DateTime offsetEpochTime;
    Smp::DateTime offsetMissionTime;

};
}
}
