
#include "EventManager.h"


namespace Smp2Simulator
{
namespace Core
{

// Get event identifier
Smp::Services::EventId EventManager::GetEventId(Smp::String8 eventName)
{
    if (strcmp(eventName, Smp::Services::SMP_LeaveConnecting) == 0)
        return Smp::Services::SMP_LeaveConnectingId;
    else if (strcmp(eventName, Smp::Services::SMP_EnterInitialising) == 0)
        return Smp::Services::SMP_EnterInitialisingId;
    else if (strcmp(eventName, Smp::Services::SMP_LeaveInitialising) == 0)
        return Smp::Services::SMP_LeaveInitialisingId;
    else if (strcmp(eventName, Smp::Services::SMP_EnterStandby) == 0)
        return Smp::Services::SMP_EnterStandbyId;
    else if (strcmp(eventName, Smp::Services::SMP_LeaveStandby) == 0)
        return Smp::Services::SMP_LeaveStandbyId;
    else if (strcmp(eventName, Smp::Services::SMP_EnterExecuting) == 0)
        return Smp::Services::SMP_EnterExecutingId;
    else if (strcmp(eventName, Smp::Services::SMP_EnterStoring) == 0)
        return Smp::Services::SMP_EnterStoringId;
    else if (strcmp(eventName, Smp::Services::SMP_LeaveStoring) == 0)
        return Smp::Services::SMP_LeaveStoringId;
    else if (strcmp(eventName, Smp::Services::SMP_EnterRestoring) == 0)
        return Smp::Services::SMP_EnterRestoringId;
    else if (strcmp(eventName, Smp::Services::SMP_LeaveRestoring) == 0)
        return Smp::Services::SMP_LeaveRestoringId;
    else if (strcmp(eventName, Smp::Services::SMP_EnterExiting) == 0)
        return Smp::Services::SMP_EnterExitingId;
    else if (strcmp(eventName, Smp::Services::SMP_EnterAborting) == 0)
        return Smp::Services::SMP_EnterAbortingId;
    else if (strcmp(eventName, Smp::Services::SMP_EpochTimeChanged) == 0)
        return Smp::Services::SMP_EpochTimeChangedId;
    else if (strcmp(eventName, Smp::Services::SMP_MissionTimeChanged) == 0)
        return Smp::Services::SMP_MissionTimeChangedId;
    else
        return -1;
}

// Subscribe entry point
void EventManager::Subscribe(Smp::Services::EventId event, const Smp::IEntryPoint* entryPoint)
{
    auto eventSubscribed = new EventSubscribed();
    eventSubscribed->event = event;
    eventSubscribed->entryPoint = entryPoint;
    this->eventsSubscribed.push_back(eventSubscribed);
}

// Unsubscribe entry point
void EventManager::Unsubscribe(Smp::Services::EventId event, const Smp::IEntryPoint* entryPoint)
{
    for (int i=0; i<this->eventsSubscribed.size(); i++)
    {
        auto eventSubscribed = this->eventsSubscribed.at(i);
        if (eventSubscribed->event == event && eventSubscribed->entryPoint == entryPoint)
        {
            this->eventsSubscribed.erase(this->eventsSubscribed.begin() + i);
            return;
        }
    }
}

// Emit a global event
void EventManager::Emit(Smp::Services::EventId event)
{
    for (int i=0; i<this->eventsSubscribed.size(); i++)
    {
        auto eventSubscribed = this->eventsSubscribed.at(i);
        if (eventSubscribed->event == event)
        {
            eventSubscribed->entryPoint->Execute();
        }
    }
}

}
}
