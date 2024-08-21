
#include "Scheduler.h"

namespace Smp2Simulator
{
namespace Core
{

// Execute all pending entry points according the simulation time
Smp::IEntryPoint* Scheduler::ExecuteEntryPoints()
{
    for (int i=0; i<eventsScheduled.size(); i++)
    {
        auto eventScheduled = eventsScheduled[i];

        if (eventScheduled->count == -1 || eventScheduled->times < eventScheduled->count)
        {
            // Get times according value of event scheduled for simulationTime, missionTime and epochTime
            Smp::Duration tkTime;
            Smp::Duration eventTime;
            if (eventScheduled->simulationTime != -1)
            {
                tkTime = this->timeKeeper->GetSimulationTime();
                eventTime = eventScheduled->simulationTime;
            }
            else if (eventScheduled->epochTime != -1)
            {
                tkTime = this->timeKeeper->GetEpochTime();
                eventTime = eventScheduled->epochTime;
            }
            else if (eventScheduled->epochTime != -1)
            {
                tkTime = this->timeKeeper->GetMissionTime();
                eventTime = eventScheduled->missionTime;
            }
            else
            {
                tkTime = -1;
                eventTime = -1;
            }

            // Calculate next time to execute the entry point
            Smp::Duration nextTime;
            if (eventScheduled->cycleTime >= 0)
                nextTime = (eventScheduled->times * eventScheduled->cycleTime) + eventTime;
            else
                nextTime = eventTime;

            // If the current time is equal or greater to the value obtained in previous step, execute the entry point
            if (tkTime >= nextTime)
            {
                eventScheduled->times += 1;
                eventScheduled->entryPoint->Execute();
            }
        }
    }

    return nullptr;
}

// Add immediate event
void Scheduler::AddImmediateEvent(const Smp::IEntryPoint* entryPoint)
{
    // Insert new event into the schedule list
    auto eventScheduled = new EventScheduled(this->countEventId, entryPoint, this->timeKeeper->GetSimulationTime(), -1, -1, -1, 1);
    this->eventsScheduled.push_back(eventScheduled);

    // Increase count of event id
    this->countEventId += 1;
}

// Add event relative to simulation time
Smp::Services::EventId Scheduler::AddSimulationTimeEvent(const Smp::IEntryPoint* entryPoint, Smp::Duration simulationTime, Smp::Duration cycleTime, Smp::Int64 count)
{
    // Insert new event into the schedule list
    auto time = (this->timeKeeper->GetSimulationTime() <= simulationTime) ? simulationTime : this->timeKeeper->GetSimulationTime();
    auto eventScheduled = new EventScheduled(this->countEventId, entryPoint, time, -1, -1, cycleTime, count);
    this->eventsScheduled.push_back(eventScheduled);

    // Increase count of event id
    this->countEventId += 1;

    // Return identifier of event created
    return eventScheduled->eventId;
}

// Add event relative to mission time
Smp::Services::EventId Scheduler::AddMissionTimeEvent(const Smp::IEntryPoint* entryPoint, Smp::Duration missionTime, Smp::Duration cycleTime, Smp::Int64 count)
{
    // Insert new event into the schedule list
    auto time = (this->timeKeeper->GetMissionTime() <= missionTime) ? missionTime : this->timeKeeper->GetMissionTime();
    auto eventScheduled = new EventScheduled(this->countEventId, entryPoint, -1, missionTime, -1, cycleTime, count);
    this->eventsScheduled.push_back(eventScheduled);

    // Increase count of event id
    this->countEventId += 1;

    // Return identifier of event created
    return eventScheduled->eventId;
}

// Add event relative to epoch time
Smp::Services::EventId Scheduler::AddEpochTimeEvent(const Smp::IEntryPoint* entryPoint, Smp::DateTime epochTime, Smp::Duration cycleTime, Smp::Int64 count)
{
    // Insert new event into the schedule list
    auto time = (this->timeKeeper->GetEpochTime() <= epochTime) ? epochTime : this->timeKeeper->GetEpochTime();
    auto eventScheduled = new EventScheduled(this->countEventId, entryPoint, -1, -1, epochTime, cycleTime, count);
    this->eventsScheduled.push_back(eventScheduled);

    // Increase count of event id
    this->countEventId += 1;

    // Return identifier of event created
    return eventScheduled->eventId;
}

// Add event relative to Zulu time
Smp::Services::EventId Scheduler::AddZuluTimeEvent(const Smp::IEntryPoint* entryPoint, Smp::DateTime zuluTime, Smp::Duration cycleTime, Smp::Int64 count)
{
    // NOT IMPLEMENTED
    return -1;
}

// Set event execution time using simulation time
void Scheduler::SetEventSimulationTime(Smp::Services::EventId event, Smp::Duration simulationTime)
{
    auto eventScheduled = this->GetEventScheduled(event);
    eventScheduled->simulationTime = simulationTime;
}

// Set event execution time using epoch time
void Scheduler::SetEventEpochTime(Smp::Services::EventId event, Smp::DateTime epochTime)
{
    auto eventScheduled = this->GetEventScheduled(event);
    eventScheduled->epochTime = epochTime;
}

// Set event execution time using mission time
void Scheduler::SetEventMissionTime(Smp::Services::EventId event, Smp::Duration missionTime)
{
    auto eventScheduled = this->GetEventScheduled(event);
    eventScheduled->missionTime = missionTime;
}

// Set event execution time using Zulu time
void Scheduler::SetEventZuluTime(Smp::Services::EventId event, Smp::DateTime zuluTime)
{
    // NOT IMPLEMENTED
}

// Set event cycle time
void Scheduler::SetEventCycleTime(Smp::Services::EventId event, Smp::Duration cycleTime)
{
    auto eventScheduled = this->GetEventScheduled(event);
    eventScheduled->cycleTime = cycleTime;
}

// Set event count
void Scheduler::SetEventCount(Smp::Services::EventId event, Smp::Int64 count)
{
    auto eventScheduled = this->GetEventScheduled(event);
    eventScheduled->times = count;
}

// Remove an event from the scheduler
void Scheduler::RemoveEvent(Smp::Services::EventId event)
{
    auto index = this->GetIndexEvent(event);
    if (index != -1)
    {
        this->eventsScheduled.erase(this->eventsScheduled.begin() + index);
    }
}

// Set the time keeper of the scheduler
void Scheduler::SetTimeKeeper(Smp::Services::ITimeKeeper* timeKeeper)
{
    this->timeKeeper = timeKeeper;
}

// Get the index of an event in the scheduled list
Smp::Int64 Scheduler::GetIndexEvent(Smp::Services::EventId event)
{
    for (int i=0; i<this->eventsScheduled.size(); i++)
    {
        auto eventScheduled = this->eventsScheduled.at(i);
        if (eventScheduled->eventId == event)
            return i;
    }
    return -1;
}

// Get the scheduled event from a event id
EventScheduled* Scheduler::GetEventScheduled(Smp::Services::EventId eventId)
{
    auto index = this->GetIndexEvent(eventId);
    return this->eventsScheduled.at(index);
}

}
}
