
#include "Smp/Services/IScheduler.h"
#include "Smp/Services/ITimeKeeper.h"
#include "GenericComponent.h"


namespace Smp2Simulator
{
namespace Core
{


/*
 *  EventScheduled Structure
 */

struct EventScheduled
{
    Smp::Services::EventId eventId;
    const Smp::IEntryPoint* entryPoint;
    Smp::Duration simulationTime = -1;
    Smp::Duration epochTime = -1;
    Smp::Duration missionTime = -1;
    Smp::Duration cycleTime;
    Smp::Duration count = 0;
    Smp::Duration times = 0;

    EventScheduled(Smp::Services::EventId eventId, const Smp::IEntryPoint* entryPoint, Smp::Duration simulationTime, Smp::Duration epochTime,
                   Smp::Duration missionTime, Smp::Duration cycleTime, Smp::Duration count)
    {
        this->eventId = eventId;
        this->entryPoint = entryPoint;
        this->simulationTime = simulationTime;
        this->epochTime = epochTime;
        this->missionTime = missionTime;
        this->cycleTime = cycleTime;
        this->count = count;
        this->times = 0;
    }
};


/*
 * Class Scheduler
 */

class Scheduler : public Smp::Services::IScheduler, public GenericComponent
{

public:
    // Constructor
    Scheduler(Smp::String8 name = "Scheduler", Smp::String8 description = "") : GenericComponent(name, description) { };

    // IScheduler methods
    void AddImmediateEvent(const Smp::IEntryPoint* entryPoint);
    Smp::Services::EventId AddSimulationTimeEvent(const Smp::IEntryPoint* entryPoint, Smp::Duration simulationTime, Smp::Duration cycleTime = 0, Smp::Int64 count = 0);
    Smp::Services::EventId AddMissionTimeEvent(const Smp::IEntryPoint* entryPoint, Smp::Duration missionTime, Smp::Duration cycleTime = 0, Smp::Int64 count = 0);
    Smp::Services::EventId AddEpochTimeEvent(const Smp::IEntryPoint* entryPoint, Smp::DateTime epochTime, Smp::Duration cycleTime = 0, Smp::Int64 count = 0);
    Smp::Services::EventId AddZuluTimeEvent(const Smp::IEntryPoint* entryPoint, Smp::DateTime zuluTime, Smp::Duration cycleTime = 0, Smp::Int64 count = 0);
    void SetEventSimulationTime(Smp::Services::EventId event, Smp::Duration simulationTime);
    void SetEventMissionTime(Smp::Services::EventId event, Smp::Duration missionTime);
    void SetEventEpochTime(Smp::Services::EventId event, Smp::DateTime epochTime);
    void SetEventZuluTime(Smp::Services::EventId event, Smp::DateTime zuluTime);
    void SetEventCycleTime(Smp::Services::EventId event, Smp::Duration cycleTime);
    void SetEventCount(Smp::Services::EventId event, Smp::Int64 count);
    void RemoveEvent(Smp::Services::EventId event);

    // Methods
    Smp::IEntryPoint* ExecuteEntryPoints();
    void SetTimeKeeper(Smp::Services::ITimeKeeper* timeKeeper);


protected:
    // Attributes
    Smp::Int64 countEventId = 0;
    std::vector<EventScheduled*> eventsScheduled;
    Smp::Services::ITimeKeeper* timeKeeper = nullptr;

    // Methods
    Smp::Int64 GetIndexEvent(Smp::Services::EventId eventId);
    EventScheduled* GetEventScheduled(Smp::Services::EventId eventId);

};

}
}
